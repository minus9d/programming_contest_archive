use std::io;

fn main() {
    let mut ab = String::new();
    io::stdin().read_line(&mut ab).expect("error");
    let vec : Vec<_> = ab.split_whitespace().collect();
    let a: usize = vec[0].parse().unwrap();
    let b: usize = vec[1].parse().unwrap();

    let mut s = String::new();
    io::stdin().read_line(&mut s).expect("error");
    let s = s.trim();

    // convert usize to u32
    let s_len: usize = s.chars().count();
    if a + b + 1 != s_len || s.chars().nth(a).unwrap() != '-' {
        println!("No");
    }
    else {
        let s_a: String = s.chars().take(a).collect();
        let s_b: String = s.chars().skip(a + 1).collect();

        let a_is_number = s_a.parse::<u32>().is_ok();
        let b_is_number = s_b.parse::<u32>().is_ok();

        if a_is_number && b_is_number {
            println!("Yes");
        }
        else {
            println!("No");
        }
    }
}
