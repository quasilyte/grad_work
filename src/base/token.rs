use base::byte::*;

// #FIXME: not working with tuple-like variants...
macro_rules! token_class {
    ($name: ident := $($variant: ident)*) => {
        #[derive(Debug)]
        pub enum $name {
            $($variant,)*
        }
    };
}

token_class!(Space := Whitespace Tab Newline);
token_class!(
    Operator :=
        Plus DoublePlus
        Minus DoubleMinus
        Eq DoubleEq
);
token_class!(Paren := Left Right);
token_class!(Square := Left Right);
token_class!(Curly := Left Right);

#[derive(Debug)]
pub enum Number {
    Decimal(i64),
    Real(f64),
}

#[derive(Debug)]
pub enum Word {
    Identifier(Vec<Byte>),
    Keyword(Vec<Byte>),
}

#[derive(Debug)]
pub enum Bracket {
    P(Paren),
    S(Square),
    C(Curly),
}

#[derive(Debug)]
pub enum Token {
    N(Number),
    W(Word),
    O(Operator),
    S(Space),
    B(Bracket),
}
