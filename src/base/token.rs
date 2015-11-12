use base::byte::*;
use base::decimal::Decimal;
use base::real::Real;

// #FIXME: how to capture, for example, a Space " \t\n" class?
#[derive(Debug)]
pub enum Token {
    // Datum:
    Decimal(Decimal),
    Real(Real),
    Str(ByteStr),
    // Word:
    Ident(ByteStr),
    Keyword(ByteStr),
    // Operators:
    Plus,
    DoublePlus,
    Minus,
    DoubleMinus,
    Eq,
    DoubleEq,
    Quote,
    QuasiQuote,
    Dot,
    // Space:
    Whitespace,
    Tab,
    Newline,
    // Bracket:
    LeftParen,
    RightParen,
    LeftSquare,
    RightSquare,
    LeftCurly,
    RightCurly,
    // Other:
    LineComment(ByteStr),
}
