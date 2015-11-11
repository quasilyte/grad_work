use env::error;
use base::byte::*;
use base::token::*;
use base::token::Token::*;
use base::decimal::Decimal;

pub struct Lexer {
    delimiter_p: BytePredicate,
    identifier_p: BytePredicate,
    keyword_p: BytesPredicate,
}

impl Lexer {
    pub fn new(is_keyword: BytesPredicate) -> Self {
        let is_delimiter = byte_matcher!(b' ', b'\t', b'\n', b';');
        
        let is_identifier = byte_matcher!(
            b'a'...b'z', b'A'...b'Z', b'0'...b'9', b'_'
        );
        
        Lexer {
            delimiter_p: is_delimiter,
            identifier_p: is_identifier,
            keyword_p: is_keyword,
        }
    }    

    fn match_word(&self, bytes: &Bytes) -> Token {
        use base::token::Word::*;
        
        if (self.keyword_p)(bytes) {
            W(Keyword(bytes.to_owned()))
        } else {
            W(Identifier(bytes.to_owned()))
        }
    }
    
    fn match_operator(&self, bytes: &Bytes) -> Token {
        use base::token::Operator::*;
        
        match bytes {
            b"+" => O(Plus),
            b"++" => O(DoublePlus),
            b"-" => O(Minus),
            b"--" => O(DoubleMinus),
            b"=" => O(Eq),
            b"==" => O(DoubleEq),
            b"'" => O(Quote),
            b"`" => O(QuasiQuote),
            unit @ _ => error::unexpected_token(unit)
        }
    }

    pub fn set(&mut self) -> &mut LexerConfig {
        self
    }

    pub fn tokens<'a>(&'a self, input: &'a Bytes) -> LexerIter<'a> {
        LexerIter::new(self, input)
    }
}

pub struct LexerIter<'a> {
    lexer: &'a Lexer,
    buf: &'a Bytes,
    max_pos: usize,
    pos: usize,
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

impl<'a> LexerIter<'a> {
    fn new(lexer: &'a Lexer, input: &'a Bytes) -> Self {
        LexerIter {
            lexer: lexer,
            buf: input,
            max_pos: input.len() - 1,
            pos: 0,
        }
    }
    
    fn has_next(&self) -> bool {
        self.pos < self.max_pos
    }
    
    fn byte(&self) -> Byte {
        self.buf[self.pos]
    }

    fn back_peek(&self) -> Byte {
        self.buf[self.pos - 1]
    }

    fn next_byte(&mut self) -> Byte {
        self.pos += 1;
        self.back_peek()
    }

    fn at(&self, b: Byte) -> bool {
        self.byte() == b
    }

    fn fetch_operator(&mut self) -> Token {
        let bytes = take_bytes!(self, {
            skip_while!(self, !(self.lexer.delimiter_p)(self.byte()));
        });
        
        self.lexer.match_operator(bytes)
    }

    fn fetch_whitespace(&mut self) -> Token {
        skip_while!(self, self.at(b' '));
        S(Space::Whitespace)
    }

    fn fetch_str(&mut self) -> Token {
        self.pos += 1; // Pass over first `"`

        // #TODO: need more robust scanning
        let bytes = take_bytes!(self, {
            while !(self.byte() == b'"' && self.back_peek() != b'\\') {
                self.pos += 1;
            }
        });

        self.pos += 1; // Pass over enclosing `"`
        D(Data::S(bytes.to_owned()))
    }

    fn fetch_word(&mut self) -> Token {
        let bytes = take_bytes!(self, {
            while !(self.lexer.delimiter_p)(self.byte()) {
                if (self.lexer.identifier_p)(self.byte()) {
                    self.pos += 1;
                } else {
                    error::malformed_identifier(self.byte());
                }
            }
        });

        self.lexer.match_word(bytes)
    }

    fn fetch_number(&mut self) -> Token {
        let decimal = Decimal::from_str(take_bytes!(self, {
            skip_while!(self, self.byte().is_digit());
        }));
        
        if self.byte() == b'.' {
            self.pos += 1;
            
            D(Data::N(Num::Real(decimal.to_real(take_bytes!(self, {
                skip_while!(self, self.byte().is_digit());
            })).0)))
        } else {
            D(Data::N(Num::Decimal(decimal.0)))
        }
    }
}

impl<'a> Iterator for LexerIter<'a> {
    type Item = Token;
  
    fn next(&mut self) -> Option<Token> {
        macro_rules! emit {
            ($value: expr) => {{
                self.pos += 1;
                $value
            }};
        }

        // #TODO: check if typed tokens EVERYWHERE is a nice ided
        if self.has_next() {
            Some(match self.byte() {
                b'0'...b'9' => self.fetch_number(),
                b'a'...b'z' | b'A'...b'Z' => self.fetch_word(),
                b'"' => self.fetch_str(),
                b' ' => self.fetch_whitespace(),
                b'\n' => emit!(S(Space::Tab)),
                b'\t' => emit!(S(Space::Newline)),
                b'(' => emit!(B(Bracket::P(Paren::Left))),
                b')' => emit!(B(Bracket::P(Paren::Right))),
                b'[' => emit!(B(Bracket::S(Square::Left))),
                b']' => emit!(B(Bracket::S(Square::Right))),
                b'{' => emit!(B(Bracket::C(Curly::Left))),
                b'}' => emit!(B(Bracket::C(Curly::Right))),
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

impl LexerConfig for Lexer {
    fn delimiter(&mut self, p: BytePredicate) -> &mut LexerConfig {
        self.delimiter_p = p;
        self
    }

    fn identifier(&mut self, p: BytePredicate) -> &mut LexerConfig {
        self.identifier_p = p;
        self
    }
}
