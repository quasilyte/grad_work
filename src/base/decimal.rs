use cgen::stmt::pattern_match::Arm;

pub struct Decimal(pub i64);

impl Arm for Decimal {
    fn is_simple(&self) -> bool { false }
} 


