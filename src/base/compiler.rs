use base::lexer::Lexer;
use base::parser::Parser;
use base::byte::Bytes;

pub struct Compiler<T> where T: Parser {
    lexer: Lexer,
    parser: T,
}

impl<T> Compiler<T> where T: Parser {
    pub fn new(lexer: Lexer, parser: T) -> Self {
        Compiler {
            lexer: lexer,
            parser: parser,
        }
    }

    pub fn run(&mut self, input: &Bytes) {
        let mut tokens = self.lexer.tokens(input);

        while let Some(token) = tokens.next() {
            self.parser.parse(token);
        }
    }
}
