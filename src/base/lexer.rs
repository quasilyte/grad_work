use env::error;
use base::byte::*;
use base::token::*;
use base::token::Token::*;
use base::decimal::Decimal;

// #FIXME: should be configurable
fn is_keyword(word: &Bytes) -> bool {
    match word {
        b"for" => true,
        _ => false,
    }
}

pub struct Lexer<'a> {
    buf: &'a Bytes,
    max_pos: usize,
    pos: usize,
    delimiter_p: BytePredicate,
    identifier_p: BytePredicate,
}

macro_rules! take_bytes {
    ($this: ident, $body: block) => {{
        let start_pos = $this.pos;
        $body
        &$this.buf[start_pos .. $this.pos]
    }}
}

macro_rules! skip_while {
    ($this: ident, $cond: expr) => {
        while $cond {
            $this.pos += 1;
        }
    }
}

impl<'a> Lexer<'a> {
    fn has_next(&self) -> bool {
        self.pos < self.max_pos
    }
    
    fn byte(&self) -> Byte {
        self.buf[self.pos]
    }

    fn next_byte(&mut self) -> Byte {
        self.pos += 1;
        self.buf[self.pos - 1]
    }

    fn at(&self, b: Byte) -> bool {
        self.byte() == b
    }
}

impl<'a> Lexer<'a> {
    pub fn new(buf: &'a Bytes) -> Self {
        fn delimiter(c: Byte) -> bool {
            c == b' ' || c == b'\t' || c == b'\n' || c == b';'
        }

        fn identifier(c: Byte) -> bool {
            match c {
                b'a'...b'z' | b'A'...b'Z' => true,
                b'0'...b'9' => true,
                b'_' => true,
                _ => false
            }
        }
        
        Lexer {
            buf: buf,
            max_pos: buf.len() - 1,
            pos: 0,
            delimiter_p: delimiter,
            identifier_p: identifier 
        }
    }
    
    fn fetch_word(&mut self) -> Token {
        use base::token::Word::*;
        
        let bytes = take_bytes!(self, {
            while !(self.delimiter_p)(self.byte()) {
                match (self.identifier_p)(self.byte()) {
                    true => self.pos += 1,
                    _ => error::malformed_identifier(self.byte())
                }
            }
        });
                                        
        if is_keyword(bytes) {
            W(Keyword(bytes.to_owned()))
        } else {
            W(Identifier(bytes.to_owned()))
        }
    }

    fn fetch_number(&mut self) -> Token {
        let decimal = Decimal::from_str(take_bytes!(self, {
            skip_while!(self, self.byte().is_digit());
        }));
        
        if self.byte() == b'.' {
            self.pos += 1;
            
            N(Number::Real(decimal.to_real(take_bytes!(self, {
                skip_while!(self, self.byte().is_digit());
            })).0))
        } else {
            N(Number::Decimal(decimal.0))
        }
    }

    fn fetch_whitespace(&mut self) -> Token {
        skip_while!(self, self.at(b' '));
        S(Space::Whitespace)
    }
    
    fn fetch_operator(&mut self) -> Token {
        use base::token::Operator::*;

        let bytes = take_bytes!(self, {
            skip_while!(self, !(self.delimiter_p)(self.byte()));
        });
        
        match bytes {
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
        use base::token::Space::*;
        
        if self.has_next() {
            Some(match self.byte() {
                b'0'...b'9' => self.fetch_number(),
                b'a'...b'z' | b'A'...b'Z' => self.fetch_word(),
                b' ' => self.fetch_whitespace(),
                b'\t' => { self.pos += 1; S(Tab) },
                b'\n' => { self.pos += 1; S(Newline) },
                _ => self.fetch_operator(),
            })
        } else {
            None
        }
    }
}

pub trait LexerConfig {
    fn delimiter(&mut self, f: BytePredicate) -> &mut LexerConfig;
    fn identifier(&mut self, f: BytePredicate) -> &mut LexerConfig;
}

impl<'a> LexerConfig for Lexer<'a> {
    fn delimiter(&mut self, p: BytePredicate) -> &mut LexerConfig {
        self.delimiter_p = p;
        self
    }

    fn identifier(&mut self, p: BytePredicate) -> &mut LexerConfig {
        self.identifier_p = p;
        self
    }
}
