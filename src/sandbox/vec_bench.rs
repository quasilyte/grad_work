fn main() {
    let mut score: i64 = 0;
    let mut i = 1;

    while i < 50000 {
        let mut vecc = Vec::with_capacity(i);
        let mut veci = Vec::with_capacity(i);

        for n in 0..50 {
            vecc.push((n + 50) as u8);
            veci.push(n);
        }

        while 0 != vecc.len() && 0 != veci.len() {
            score += vecc.pop().unwrap() as i64;
            score += veci.pop().unwrap();
        }
        
        i += 1;
    }

    println!("{}", score);
}
