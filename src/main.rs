pub mod cgen;
pub mod base;
pub mod env;

use base::Lexer;
use base::Decimal;
use base::Byte;

// use cgen::stmt::pattern_match::Arm;

fn main() {
    fn delimiter(c: Byte) -> bool {
        c == b' ' || c == b'\n' || c == b'\t'
    }

    // #TODO: lexer must ensure trailing delimiter char in the input,
    // because we do not want to make excessive checks at run time
    let input = b"xs\tfor + ++ 430 dg3ger  6.63 ";
    let mut lexer = Lexer::new(input);
    
    lexer.set()
        .delimiter(delimiter);

    for token in lexer {
        println!("{:?}", token);
    }
}

