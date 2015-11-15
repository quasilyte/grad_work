#[macro_use]
pub mod base;
pub mod cgen;
pub mod env;

// use base::{Lexer, Byte, Parser, Compiler, Token};
use base::{Lexer, LexerIter, Byte, Bytes, Token};
use base::{Decimal};
use cgen::ast::Node;
use cgen::ast::{Plus, UnaryPlus};

struct SchemeParser<'a> {
    tokens: LexerIter<'a>
}

/*
fn fn_call(name: Box<Node>, mut args: Vec<Box<Node>>) -> Box<Node> {
    match args.len() {
        1 => Box::new(UnaryPlus::new(args.pop().unwrap())),
        _ => Box::new(Plus::new(args))
    }
}
*/

impl<'a> SchemeParser<'a> {
    fn new(input: &'a Bytes) -> Self {
        let mut lexer = Lexer::new();    
        lexer.set()
            .delimiter(byte_matcher!(b' ', b'\t', b'\n'))
            .identifier(byte_matcher!(b'a'...b'z', b'A'...b'Z', b'0'...b'9', b'_'));
        
        SchemeParser {
            tokens: lexer.into_tokens(input)
        }
    }

    fn run(&mut self) {
        let mut program: Vec<Box<Node>> = Vec::new();
        
        while let Some(token) = self.tokens.next() {
            program.push(self.parse(token));
        }

        for node in program.iter() {
            println!("{:?}", node.gen_code());
        }
    }

    fn fn_call(&mut self) -> Box<Node> {
        macro_rules! collect_args {
            () => {{
                let mut args: Vec<Box<Node>> = Vec::with_capacity(2);

                loop {
                    match self.tokens.next().unwrap() {
                        Token::Whitespace => (),
                        Token::RightParen => break,
                        token @ _ => args.push(self.parse(token))
                    }
                }

                args
            }};
        }
        
        match self.tokens.next().unwrap() {
            // Token::Ident(name) => fn_call(name, collect_args!()),
            Token::Plus => {
                let mut args = collect_args!();
                match args.len() {
                    1 => Box::new(UnaryPlus::new(args.pop().unwrap())),
                    _ => Box::new(Plus::new(args))
                }
            },
            _ => panic!("unsupported operator met")
        }
    }
    
    fn parse(&mut self, token: Token) -> Box<Node> {
        // use base::Token::*;

        match token {
            Token::LeftParen => self.fn_call(),
            Token::Decimal(x) => Box::new(x),
            _ => panic!("unexpected {:?}", token)
        }
        
        /*
        match token {
            LeftParen => println!("lparen"),
            Ident(k) => println!("keyword! {:?}", k),
            Whitespace | Tab | Newline => (),
            LineComment(text) => println!("comment with text {:?}", text),
            _ => println!("{:?}", token)
        }
        */
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
    let input = b"(+ 1 2)(+ 4 5 5) ";
     
    SchemeParser::new(input).run();
}

