use base::token::Token;

pub trait Parser {
    fn parse(&self, token: Token); 
}
