/*
use base::byte::BytePredicate;
use base::Lexer;

pub trait LexerConfig {
    fn delimiter(&mut self, f: BytePredicate) -> &mut LexerConfig;
}

impl<'a> LexerConfig for Lexer<'a> {
    fn delimiter(&mut self, f: BytePredicate) -> &mut LexerConfig {
        self.delimiter_p = f;
        self
    }
}
*/
