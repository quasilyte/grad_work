#[macro_use]
pub mod utils;
#[macro_use]
pub mod base;
pub mod cgen;
pub mod env;

// use base::{Lexer, Byte, Parser, Compiler, Token};
use base::{Lexer, LexerIter, Byte, Bytes, Token};
use base::{Decimal};
use cgen::ast::Node;
use cgen::ast::{Add, Mul, Div, UnaryAdd};

macro_rules! parser_extend {
    ($parser:ident with collect_args) => {
        impl<'a> $parser<'a> {
            fn collect_args(&mut self) -> Vec<Box<Node>> {
                let mut args: Vec<Box<Node>> = Vec::with_capacity(2);

                loop {
                    match self.tokens.next().unwrap() {
                        Token::Whitespace => (),
                        Token::RightParen => break,
                        token @ _ => args.push(self.parse(token))
                    }
                }

                args
            }
        }
    };
}

struct SchemeParser<'a> {
    tokens: LexerIter<'a>
}

parser_extend!(SchemeParser with collect_args);
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

    fn parse_expression(&mut self) -> Box<Node> {
        use base::token::Token::*;
        
        match self.tokens.next().unwrap() {
            Plus => {
                // #FIXME: maybe there is a need for some kind of `bag`
                // which stores collected args inside?
                // With it: match self.collect_args().len(); and then use
                // self.collected_args in arms
                let mut args = self.collect_args();
                match args.len() {
                    1 => UnaryAdd::boxed(args.pop().unwrap()),
                    _ => Add::boxed(args)
                }
            },
            Asterisk => Mul::boxed(self.collect_args()),
            Slash => Div::boxed(self.collect_args()),
            /*
            Ident(name) => match name {
                // keyword
                // user func
            },
            */
            _ => panic!("unexpected operator found")
        }
    }

    fn parse(&mut self, token: Token) -> Box<Node> {
        match token {
            Token::LeftParen => self.parse_expression(),
            Token::Decimal(x) => Box!(x),
            _ => panic!("unexpected {:?}", token)
        }
    }
}

// #TODO: maybe it is a good idea to define a keyword set
// inside a parser alongside with associated handlers?
// #TODO: can we get rid of `b` prefixes at least here?
fn main() {  
    // #TODO: lexer must ensure trailing delimiter char in the input,
    // because we do not want to make excessive checks at run time
    // let input = include_bytes!("../tmp/input.txt");
    let input = b"(define x 10) ";
     
    SchemeParser::new(input).run();
}

