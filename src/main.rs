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
    
    let input = b"xs\tfor + ++ 430 dg3ger  6.63 ";
    let mut lexer = Lexer::new(input);
    
    lexer.configure()
        .delimiter(delimiter);

    // #TODO: implement iterator for lexer
    let mut i = 0;
    while !lexer.eof() {
        println!("[{:2}] {:?}", i, lexer.next());
        i += 1;
    }
    
    /*
    for i in 0..13 {
        println!("[{:2}] {:?}", i, lexer.next());
    }
    */
}

