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
        Quote QuasiQuote
);
token_class!(Paren := Left Right);
token_class!(Square := Left Right);
token_class!(Curly := Left Right);
token_class!(Quote := Single Double Quasi);

#[derive(Debug)]
pub enum Data {
    N(Num),
    S(ByteStr),
}

#[derive(Debug)]
pub enum Num {
    Decimal(i64),
    Real(f64),
}

#[derive(Debug)]
pub enum Word {
    Identifier(ByteStr),
    Keyword(ByteStr),
}

#[derive(Debug)]
pub enum Bracket {
    P(Paren),
    S(Square),
    C(Curly),
}

#[derive(Debug)]
pub enum Token {
    D(Data),
    W(Word),
    O(Operator),
    S(Space),
    B(Bracket),
}
