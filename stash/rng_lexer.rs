#[derive(Debug, Clone)]
struct Rng(usize, usize);

#[derive(Debug, Clone)]
enum Token {
    Plus, Minus, Ident(Rng),
}

struct Lexer {
    buf: String,
    tokens: Vec<Token>,
    pos: usize,
}

impl Lexer {
    fn new() -> Self {
        Lexer {
            buf: "+ foo bar -".to_string(),
            tokens: vec![
                Token::Plus, 
                Token::Ident(Rng(2, 5)), 
                Token::Ident(Rng(6, 9)),
                Token::Minus
            ],
            pos: 0,
        }
    }
    
    fn next(&mut self) -> Token {
        self.pos += 1;
        self.tokens[self.pos - 1].clone()
    }
    
    fn has_more(&self) -> bool {
        self.pos != self.tokens.len()
    }
    
    fn fetch(&self, rng: Rng) -> &str {
        &self.buf[rng.0 .. rng.1]
    }
    
    fn rewind(&mut self) {
        self.pos = 0;
    }
} 

fn main() {
    let mut lexer = Lexer::new();
    let mut score = 0;

    for i in 0..500000 {
        while lexer.has_more() {
            let token = lexer.next();
            match token {
                Token::Ident(rng) => {
                    score += lexer.fetch(rng).len();
                    if let Token::Ident(rng) = lexer.next() {
                        score += lexer.fetch(rng).len();
                    }
                },
                Token::Minus => score -= 1,
                Token::Plus => score += 1,
            }
        }
        score += i;
        lexer.rewind();
    }
    
    println!("{}", score);
}
