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
pub enum Word<'a> {
    Identifier(&'a Bytes),
    Keyword(&'a Bytes),
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
pub enum Token<'a> {
    N(Number),
    W(Word<'a>),
    O(Operator),
    S(Space),
}
