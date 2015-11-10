#[macro_use]
pub mod base;
pub mod cgen;
pub mod env;

use base::{Lexer, Decimal, Byte, Bytes};

// #TODO: maybe it is a good idea to define a keyword set
// inside a parser alongside with associated handlers?
// #TODO: can we get rid of `b` prefixes at least here?
fn main() {  
    // #TODO: lexer must ensure trailing delimiter char in the input,
    // because we do not want to make excessive checks at run time
    let input = b"xs\tfor + ++ 430 dg3ger  6.63 ";
    
    let mut lexer = Lexer::new(input, bytes_matcher!(
        b"if",
        b"else",
        b"for",
        b"loop",
        b"while"
    ));
    
    lexer.set()
        .delimiter(byte_matcher!(b' ', b'\t', b'\n'))
        .identifier(byte_matcher!(b'a'...b'z', b'A'...b'Z', b'0'...b'9', b'_'));

    for token in lexer {
        println!("{:?}", token);
    }
}

