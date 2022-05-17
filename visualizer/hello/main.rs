use std::process::{Command, Stdio};

fn main() {
    let output = Command::new("./filler_vm")
        .args(["-f", "map00", "-p1", "./cchen.filler", "-p2", "./carli.filler"])
        .stdout(Stdio::piped())
        .output()
        .unwrap();
    let stdout = String::from_utf8(output.stdout).unwrap();
    for line in stdout.split("\n") {
        if line.starts_with("Plateau") {println!("{}", line)}
    }
}
