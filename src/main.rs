use std::io::{BufRead, BufReader};
use std::process::{Command, Stdio};
use std::thread;

fn main() {
    let mut child = Command::new("wine")
        .current_dir("/mnt/applications/SteamLibrary/steamapps/common/Far Cry 2/bin")
        .arg("FC2ServerLauncher.exe")
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .spawn()
        .unwrap();

    let out = BufReader::new(child.stdout.take().unwrap());
    let err = BufReader::new(child.stderr.take().unwrap());

    let thread = thread::spawn(move || {
        err.lines().for_each(|line|
            println!("err: {}", line.unwrap())
        );
    });

    out.lines().for_each(|line|
        println!("out: {}", line.unwrap())
    );

    thread.join().unwrap();

    let status = child.wait().unwrap();
    println!("{}", status);
}