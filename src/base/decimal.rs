use cgen::stmt::pattern_match::Arm;
use env::error;
use base::byte::*;

pub struct Decimal(pub i64);

fn from_str(s: &Bytes) -> Decimal {
    if 0 == s.len() {
        error::decimal_parse();
    }

    let (is_positive, digits) = match s[0] {
        b'+' => (true, &s[1..]),
        b'-' => (false, &s[1..]),
        _ => (true, s)
    };

    // #TODO: handle len=19 case with `from_digits_checked`
    // #TODO: actually, we want to prefer long arithmetics over i64 restriction
    match digits.len() {
        0 => error::decimal_parse(),
        1...18 => from_digits(digits, is_positive),
        _ => error::decimal_parse()
    }
}

fn from_digits(digits: &Bytes, is_positive: bool) -> Decimal {
    let mut result = 0_i64;
    
    for &digit in digits.iter() {
        match digit {
            b'0'...b'9' => {
                result *= 10;
                result += (digit - b'0') as i64;
            },
            _ => error::decimal_parse()
        }
    }

    Decimal(if is_positive { result } else { -result })
}

impl Decimal {
    pub fn from_str(s: &Bytes) -> Self {
        from_str(s)
    }
}

impl Arm for Decimal {
    fn is_simple(&self) -> bool { false }
} 
