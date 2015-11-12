#[macro_use]
pub mod base;
pub mod cgen;
pub mod env;

use base::{Lexer, Byte, Bytes, Parser, Compiler, Token, Word, Bracket, Paren};

struct SchemeParser;

macro_rules! keyword {
    () => { Token::W(Word::Keyword(_)) };
    ($binding: ident) => { Token::W(Word::Keyword($binding)) };
}

macro_rules! space {
    () => { Token::S(_) };
    ($binding: ident) => { Token::S($binding) };
}

macro_rules! lparen { () => { Token::B(Bracket::P(Paren::Left)) }; }

impl Parser for SchemeParser {
    fn parse(&self, token: Token) {
        match token {
            lparen!() => println!("lparen"),
            keyword!(k) => println!("keyword! {:?}", k),
            space!() => (),
            _ => println!("{:?}", token)
        }
    }
}

// #TODO: maybe it is a good idea to define a keyword set
// inside a parser alongside with associated handlers?
// #TODO: can we get rid of `b` prefixes at least here?
fn main() {  
    // #TODO: lexer must ensure trailing delimiter char in the input,
    // because we do not want to make excessive checks at run time
    // let input = b"(define x (+ 10 20.4)) ";
    // let input = br##" (define str "string content!") "##;
    // let input = br##""s\"tr" "##;
    // let input = include_bytes!("../tmp/input.txt");
    let input = b"(+ 10 20) ";
     
    let mut lexer = Lexer::new(bytes_matcher!(
        b"define"
    ));
    
    lexer.set()
        .delimiter(byte_matcher!(b' ', b'\t', b'\n'))
        .identifier(byte_matcher!(b'a'...b'z', b'A'...b'Z', b'0'...b'9', b'_'));

    Compiler::new(lexer, SchemeParser).run(input);
}

