use std::io;

fn main() {
    let mut n = String::new();
        io::stdin().read_line(&mut n)
	        .expect("failed to read line");

    let n: u32 = n.trim().parse().expect("error");

    println!("{}", 48 - n);
}
