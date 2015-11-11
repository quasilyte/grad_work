use cgen::stmt::pattern_match::Arm;

pub struct Real(pub f64);

impl Arm for Real {
    fn is_simple(&self) -> bool { true }
} 
