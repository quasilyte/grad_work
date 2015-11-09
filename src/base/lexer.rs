use env::error;
use base::byte::*;
use base::reader::*;
use base::token::*;
use base::token::Token::*;

// use base::lexer_config::LexerConfig;

fn is_whitespace(b: Byte) -> bool {
    b == b' '
}

// #FIXME: should be configurable
fn is_keyword(word: &Bytes) -> bool {
    match word {
        b"for" => true,
        _ => false,
    }
}

pub struct Lexer<'a> {
    src: Reader<'a>,
    delimiter_p: BytePredicate,
}

impl<'a> Lexer<'a> {
    pub fn new(buf: &'a Bytes) -> Self {
        Lexer {
            src: Reader::new(buf),
            delimiter_p: byte_predicate!(
                c, c == b' ' || c == b'\t' || c == b'\n' || c == b';'
            )
        }
    }

    fn skip_to_delimiter(&mut self) {
        self.src.skip_until(self.delimiter_p);
    }

    fn fetch_unit(&mut self) -> &Bytes {
        let offset = self.src.pos - 1;
        self.skip_to_delimiter();
        self.src.stab(offset)
    }

    fn fetch_word(&mut self) -> Token {
        let word = self.fetch_unit();
        // print!("`{}` ", String::from_utf8(word.to_owned()).unwrap());
        if is_keyword(word) {
            W(Word::Keyword(word.to_owned()))
        } else {
            W(Word::Identifier(word.to_owned()))
        }
    }

    fn fetch_number(&mut self) -> Token {
        let word = self.fetch_unit();
        N(Number::Decimal(55))
    }

    fn fetch_whitespace(&mut self) -> Token {
        self.src.skip_while(is_whitespace);
        S(Space::Whitespace)
    }
    
    fn fetch_operator(&mut self) -> Token {
        use base::token::Operator::*;
        match self.fetch_unit() {
            b"+" => O(Plus),
            b"++" => O(DoublePlus),
            b"-" => O(Minus),
            b"--" => O(DoubleMinus),
            b"=" => O(Eq),
            b"==" => O(DoubleEq),
            unit @ _ => error::unexpected_token(unit)
        }
    }

    pub fn set(&mut self) -> &mut LexerConfig {
        self
    }
}

impl<'a> Iterator for Lexer<'a> {
    type Item = Token;
  
    fn next(&mut self) -> Option<Token> {
        if self.src.has_more() {
            Some(match self.src.next_byte() {
                b'0'...b'9' => self.fetch_number(),
                b'a'...b'z' | b'A'...b'Z' => self.fetch_word(),
                b' ' => self.fetch_whitespace(),
                b'\t' => S(Space::Tab),
                b'\n' => S(Space::Newline),
                _ => self.fetch_operator(),
            })
        } else {
            None
        }
    }
}

pub trait LexerConfig {
    fn delimiter(&mut self, f: BytePredicate) -> &mut LexerConfig;
}

impl<'a> LexerConfig for Lexer<'a> {
    fn delimiter(&mut self, f: BytePredicate) -> &mut LexerConfig {
        self.delimiter_p = f;
        self
    }
}
