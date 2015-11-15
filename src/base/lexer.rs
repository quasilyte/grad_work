use env::error;
use base::byte::*;
use base::decimal::Decimal;
use base::token::Token;
use base::real::Real;

pub struct Lexer {
    delimiter_p: BytePredicate,
    identifier_p: BytePredicate,
}

impl Lexer {
    pub fn new() -> Self {
        let is_delimiter = byte_matcher!(b' ', b'\t', b'\n', b';');
        
        let is_identifier = byte_matcher!(
            b'a'...b'z', b'A'...b'Z', b'0'...b'9', b'_'
        );
        
        Lexer {
            delimiter_p: is_delimiter,
            identifier_p: is_identifier,
        }
    }    

    fn make_str(&self, bytes: &Bytes) -> Token {
        Token::Str(ByteStr::from_bytes(bytes))
    }

    fn make_real(&self, real: Real) -> Token {
        Token::Real(real)
    }

    fn make_decimal(&self, decimal: Decimal) -> Token {
        Token::Decimal(decimal)
    }

    fn make_ident(&self, bytes: &Bytes) -> Token {
        Token::Ident(ByteStr::from_bytes(bytes))
    }
    
    fn match_operator(&self, bytes: &Bytes) -> Token {
        use base::token::Token::*;

        // #TODO: test if this is efficient for long lists of strings
        // against other approaches
        // #TODO: maybe it is a good idea to match single char strings
        // by a separate match
        match bytes {
            b"+" => Plus,
            b"++" => DoublePlus,
            b"-" => Minus,
            b"--" => DoubleMinus,
            b"=" => Eq,
            b"==" => DoubleEq,
            b"'" => Quote,
            b"`" => QuasiQuote,
            b"." => Dot,
            b"," => Comma,
            b"*" => Mul,
            b"/" => Div,
            unit @ _ => error::unexpected_token(unit)
        }
    }

    pub fn set(&mut self) -> &mut LexerConfig {
        self
    }

    pub fn into_tokens<'a>(self, input: &'a Bytes) -> LexerIter<'a> {
        LexerIter::new(self, input)
    }
}

pub struct LexerIter<'a> {
    lexer: Lexer,
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
    fn new(lexer: Lexer, input: &'a Bytes) -> Self {
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

    fn at(&self, byte: Byte) -> bool {
        self.byte() == byte
    }
    
    fn byte(&self) -> Byte {
        self.buf[self.pos]
    }

    fn back_peek(&self) -> Byte {
        self.buf[self.pos - 1]
    }

    fn fetch_operator(&mut self) -> Token {
        let bytes = take_bytes!(self, {
            skip_while!(self, !(self.lexer.delimiter_p)(self.byte()));
        });
        
        self.lexer.match_operator(bytes)
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
        self.lexer.make_str(bytes)
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

        self.lexer.make_ident(bytes)
    }

    fn fetch_number(&mut self) -> Token {
        let decimal = Decimal::from_str(take_bytes!(self, {
            skip_while!(self, self.byte().is_digit());
        }));
        
        if self.byte() == b'.' {
            self.pos += 1;

            let real = decimal.to_real(take_bytes!(self, {
                skip_while!(self, self.byte().is_digit());
            }));

            self.lexer.make_real(real)            
        } else {
            self.lexer.make_decimal(decimal)
        }
    }

    fn fetch_comment(&mut self) -> Token {
        // #TODO: collect annotations into token?
        // #FIXME: need unexpected EOF protection
        let bytes = take_bytes!(self, {
            skip_while!(self, !self.at(b'\n'));
        });

        Token::LineComment(ByteStr::from_bytes(bytes))
    }
}

impl<'a> Iterator for LexerIter<'a> {
    type Item = Token;
  
    fn next(&mut self) -> Option<Token> {
        macro_rules! emit {
            ($value: ident) => {{
                self.pos += 1;
                Token::$value
            }};
        }

        // #TODO: check if typed tokens EVERYWHERE is a nice idea
        if self.has_next() {
            Some(match self.byte() {
                b'0'...b'9' => self.fetch_number(),
                b'a'...b'z' | b'A'...b'Z' => self.fetch_word(),
                b'#' => self.fetch_comment(),
                b'"' => self.fetch_str(), 
                b' ' => emit!(Whitespace),
                b'\n' => emit!(Newline),
                b'\t' => emit!(Tab),
                b'(' => emit!(LeftParen),
                b')' => emit!(RightParen),
                b'[' => emit!(LeftSquare),
                b']' => emit!(RightSquare),
                b'{' => emit!(LeftCurly),
                b'}' => emit!(RightCurly),
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
