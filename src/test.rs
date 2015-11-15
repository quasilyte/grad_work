#[macro_use]
pub mod base;
pub mod cgen;
pub mod env;

use cgen::Ast;
use base::{Lexer, Byte, Parser, Compiler, Token};

struct SchemeParser;

fn fn_call(parse_name: fn(&Parser, Token), parse_arg: fn(&Parser, Token))
           -> Box<Ast> {
    println!("{}", parse_name());
    let args: Vec<Box<Ast>> = Vec::new();
    while let Some(ast) = parse_arg(token.next()) {
        args.push(ast);
    }
}

impl Parser for SchemeParser {
    fn fn_name(&self, token: Token) -> Option<Box<Ast>> {
        match token {
            Token::Ident => Some(token),
            _ => panic("expected Ident, found {}", token)
        };
    }

    fn fn_arg(&self, token: Token) -> Option<Box<Ast>> {
        match token {
            Token::RightParen => None,
            _ => self.parse(token)
        }
    }
    
    fn parse(&self, token: Token) {
        use base::Token::*;
        
        match token {
            LeftParen => fn_call(self.fn_name, ),
            _ => println!("{:?}", token)
        };
        
        /*
        match token {
            LeftParen => println!("lparen"),
            Ident(k) => println!("keyword! {:?}", k),
            Whitespace | Tab | Newline => (),
            LineComment(text) => println!("comment with text {:?}", text),
            _ => println!("{:?}", token)
        }*/
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
    // let input = b"#comment\n(+ 10 20) ";
    let input = b"(+ 1 2) ";
     
    let mut lexer = Lexer::new();
    
    lexer.set()
        .delimiter(byte_matcher!(b' ', b'\t', b'\n'))
        .identifier(byte_matcher!(b'a'...b'z', b'A'...b'Z', b'0'...b'9', b'_'));

    Compiler::new(lexer, SchemeParser).run(input);
}

