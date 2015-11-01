use cgen::stmt::pattern_match::Arm;

pub struct Decimal(pub i64);

#[derive(Debug)]
pub enum DecimalParseErr {
    BadInput,
    Overflow,
}

fn from_str(s: &[u8]) -> Result<Decimal, DecimalParseErr> {
    if 0 == s.len() {
        return Err(DecimalParseErr::BadInput);
    }

    let (is_positive, digits) = match s[0] {
        b'+' => (true, &s[1..]),
        b'-' => (false, &s[1..]),
        _ => (true, s)
    };

    // #TODO: handle len=19 case with `from_digits_checked`
    match digits.len() {
        0 => Err(DecimalParseErr::BadInput),
        1...18 => from_digits(digits, is_positive),
        _ => Err(DecimalParseErr::Overflow)
    }
}

fn from_digits(digits: &[u8], is_positive: bool)
               -> Result<Decimal, DecimalParseErr> {
    let mut result = 0_i64;
    
    for &digit in digits.iter() {
        match digit {
            b'0'...b'9' => {
                result *= 10;
                result += (digit - b'0') as i64;
            },
            _ => return Err(DecimalParseErr::BadInput)
        }
    }

    Ok(Decimal(if is_positive { result } else { -result }))
}

impl Decimal {
    pub fn from_str(s: &[u8]) -> Result<Decimal, DecimalParseErr> {
        from_str(s)
    }
}

impl Arm for Decimal {
    fn is_simple(&self) -> bool { false }
} 
