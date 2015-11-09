use base::byte::*;

#[derive(Debug)]
pub enum Space {
    Whitespace,
    Tab,
    Newline,
}

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
pub enum Operator {
    Plus,
    DoublePlus,
    Minus,
    DoubleMinus,
    Eq,
    DoubleEq,
}

#[derive(Debug)]
pub enum Token {
    N(Number),
    W(Word),
    O(Operator),
    S(Space),
}
