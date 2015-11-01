pub mod cgen;
pub mod base;
pub mod env;

use base::Decimal;
use cgen::stmt::pattern_match::Arm;

/*
fn match_pattern(arms: &[&Arm]) {
    match arms.iter().cloned().by_ref().find(Arm::is_simple) {
        Some(_) => println!("non-simple case"),
        None => println!("simple case")
    }
}
*/

fn main() {
    let decimal = Decimal::from_str(b"4758").unwrap();
    println!("{}", decimal.0);
}

