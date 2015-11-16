use base::byte::*;
use base::decimal::Decimal;
use base::real::Real;

#[derive(Debug)]
pub enum Token {
    // Datum:
    Decimal(Decimal),
    Real(Real),
    Str(ByteStr),
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
    Comma,
    Asterisk, // #FIXME: is there any better name for "*"?
    Slash,
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
    LineComment(ByteStr), // #FIXME: should be configurable
    Ident(ByteStr),
}
