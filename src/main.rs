pub mod cgen;
pub mod base;
pub mod env;

use base::Lexer;
use base::Decimal;
use cgen::stmt::pattern_match::Arm;

fn main() {
    let input = b"xs\tfor + ++ 430 dg3ger  6.63 ";
    let mut lexer = Lexer::new(input);

    for i in 0..13 {
        println!("[{:2}] {:?}", i, lexer.next());
    }
}

