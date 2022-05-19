use std::thread;
use std::sync::mpsc;
use std::sync::Arc;
use std::sync::Mutex;
use std::process::{Command, Stdio};
use json;

enum Message {
    NewJob(Job),
    Terminate
}

pub struct ThreadPool {
	workers: Vec<Worker>,
	sender: mpsc::Sender<Message>
}

type Job = Box<dyn FnOnce() + Send + 'static>;

impl ThreadPool {
	/// Create a new ThreadPool.
	///
	/// The size is the number of threads in the pool.
	///
	/// # Panics
	///
	/// The `new` function will panic if the size is zero.
	pub fn new(size: usize) -> ThreadPool {
		assert!(size > 0);
		
		let (sender, receiver) = mpsc::channel();
		let receiver = Arc::new(Mutex::new(receiver));

		let mut workers = Vec::with_capacity(size);
		
		for id in 0..size {
			workers.push(Worker::new(id, Arc::clone(&receiver)));
		}
		ThreadPool { workers, sender }
	}
	
	pub fn execute<F>(&self, f: F)
	where
		F: FnOnce() + Send + 'static, {

		let job = Box::new(f);

		self.sender.send(Message::NewJob(job)).unwrap();
	}
}

struct Worker {
	id: usize,
	thread: Option<thread::JoinHandle<()>>
}

impl Worker {
	fn new(id: usize, receiver: Arc<Mutex<mpsc::Receiver<Message>>>) -> Worker {
		let thread = thread::spawn(move || loop {
			let message = receiver.lock().unwrap().recv().unwrap();

            match message {
                Message::NewJob(job) => {
                    println!("Worker {} got a job; executing.", id);

                    job();
                }
                Message::Terminate => {
                    println!("Worker {} was told to terminate.", id);

                    break;
                }
            }
		});

		Worker {
            id,
            thread: Some(thread)
        }
	}
}

impl Drop for ThreadPool {
    fn drop(&mut self) {
        println!("Sending terminate mesage to all workers.");

        for _ in &self.workers {
            self.sender.send(Message::Terminate).unwrap();
        }

        println!("Shutting down all workers.");

        for worker in &mut self.workers {
            println!("Shutting down worker {}", worker.id);
            if let Some(thread) = worker.thread.take() {
                thread.join().unwrap();
            }
        }
    }
}

pub struct Filler {
    pub replay: String
}

impl Filler {
    fn call_cmd(filler: &str, args: &mut [&str]) -> String {
        let output = Command::new(filler)
            .args(args)
            .stdout(Stdio::piped())
            .output()
            .unwrap();
        let stdout = String::from_utf8(output.stdout).unwrap();
        stdout
    }

    pub fn run(filler: &str, args: &mut [&str]) -> Filler {
        let stdout = Filler::call_cmd(filler, args);
        let mut data = vec![];
        let mut index = 0;
        let mut is_begun = false;
        for line in stdout.split("\n") {
            let is_mapln = line.chars().count() > 3 && (&line[..3]).parse::<f64>().is_ok();
            if line.starts_with("Plateau") {
                data.push(vec![]);
                index += 1;
                is_begun = true;
            }
            else if is_begun && is_mapln {
                data[index - 1].push(&line[4..]);
            }
        }
	let mut replay = json::stringify(data);

	Filler { replay }
    }
}
