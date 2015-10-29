pub mod cgen;
pub mod base;

use base::Decimal;
use cgen::stmt::pattern_match::Arm;

// fn match_pattern(input: Expr, arms: &[Arm]) {
fn match_pattern(arms: &[&Arm]) {
    match arms.iter().find(|&arm| { println!("?"); !arm.is_simple() }) {
        Some(_) => println!("non-simple case"),
        None => println!("simple case")
    }
}

fn main() {
    let arms: &[&Arm] = &[
        &Decimal ( 40 ),
        &Decimal ( 70 ),
    ];
    match_pattern(arms);
    let dec = Decimal(40);
    println!("{}", dec.0);
}
