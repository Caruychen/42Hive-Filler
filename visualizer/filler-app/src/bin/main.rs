use std::io::prelude::*;
use std::net::TcpListener;
use std::net::TcpStream;
use std::fs;
use filler::ThreadPool;
use filler::Filler;

fn main() {
	let listener = TcpListener::bind("127.0.0.1:7878").unwrap();
	let pool = ThreadPool::new(4);

	for stream in listener.incoming() {
		let stream = stream.unwrap();

		pool.execute(|| {
			handle_connection(stream);
		});
	}
}

fn handle_connection(mut stream: TcpStream) {
	let mut buffer = [0; 1024];
	stream.read(&mut buffer).unwrap();

	let get = b"GET / HTTP/1.1\r\n";
	let getjs = b"GET /js/index.js HTTP/1.1\r\n";
	let getcss = b"GET /filler.css HTTP/1.1\r\n";

	let (status_line, filename) = if buffer.starts_with(get) {
		("HTTP/1.1 200 OK", "index.html")
	} else if buffer.starts_with(getcss) {
		("HTTP/1.1 200 OK", "filler.css")
	} else if buffer.starts_with(getjs) {
/*
        Filler::run("./assets/filler_vm",
                    &mut ["-f", "assets/map02",
                        "-p1", "./assets/players/cchen.filler",
                        "-p2", "./assets/players/cchen.filler"]);
*/
		("HTTP/1.1 200 OK", "js/index.js")	
	} else {
		("HTTP/1.1 404 NOT FOUND", "404.html")
	};

	let contents = fs::read_to_string(filename).unwrap();
	
	let response = format!(
		"{}\r\nContent-Length: {}\r\n\r\n{}",
		status_line,
		contents.len(),
		contents
	);
	stream.write(response.as_bytes()).unwrap();
	stream.flush().unwrap();
}
