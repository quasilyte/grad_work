use base::byte::*;
use base::reader::*;
use base::token::*;

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
            Token::W(Word::Keyword(word))
        } else {
            Token::W(Word::Identifier(word))
        }
    }

    fn fetch_number(&mut self) -> Token {
        let word = self.fetch_unit();
        Token::N(Number::Decimal(55))
    }

    // " "32 "\n"10 "\t"9
    fn fetch_whitespace(&mut self) -> Token {
        self.src.skip_while(is_whitespace);
        Token::S(Space::Whitespace)
    }

    fn fetch_operator(&mut self) -> Token {   
        match self.fetch_unit() {
            b"+" => Token::O(Operator::Plus),
            b"++" => Token::O(Operator::DoublePlus),
            b"-" => Token::O(Operator::Minus),
            b"--" => Token::O(Operator::DoubleMinus),
            b"=" => Token::O(Operator::Eq),
            b"==" => Token::O(Operator::DoubleEq),
            _ => panic!("unknown token met!")
        }
    }
    
    pub fn next(&mut self) -> Token {
        match self.src.next_byte() {
            b'a'...b'z' | b'A'...b'Z' => self.fetch_word(),
            b'0'...b'9' => self.fetch_number(),
            b' ' => self.fetch_whitespace(),
            b'\t' => Token::S(Space::Tab),
            b'\n' => Token::S(Space::Newline),
            _ => self.fetch_operator(),
        }
    }
}
