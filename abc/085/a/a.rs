use std::io;
 
fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).expect("failed to read line");
 
    println!("2018{}", &s[4..])
}
