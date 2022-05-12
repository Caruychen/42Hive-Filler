use std::process::{Command, Stdio};

fn main() {
	let output = Command::new("./filler_vm")
		.args(["-f","map00","-p1","./cchen.filler","-p2","./carli.filler"])
		.stdout(Stdio::piped())
		.output()
		.unwrap();
	let result = String::from_utf8_lossy(&output.stdout);
	println!("{}", result);
}
