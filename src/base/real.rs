use cgen::stmt::pattern_match::Arm;
use base::byte::*;
use base::decimal::Decimal;

pub struct Real(pub f64);

impl Arm for Real {
    fn is_simple(&self) -> bool { true }
} 
