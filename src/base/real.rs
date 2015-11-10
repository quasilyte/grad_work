use cgen::stmt::pattern_match::Arm;
use base::byte::*;
use base::decimal::Decimal;

pub struct Real(pub f64);

impl Real {
    pub fn from_str(bytes: &Bytes) -> Self {
        let dot_pos = bytes.iter().position(|&byte| byte == b'.').unwrap();
        
        let integ_s = &bytes[..dot_pos];
        let fract_s = &bytes[1+dot_pos..];

        Real((Decimal::from_str(integ_s).0 as f64)
             + (Decimal::from_str(fract_s).0 as f64
                * (1.0 / (10_i64.pow(fract_s.len() as u32) as f64))))
    }
}

impl Arm for Real {
    fn is_simple(&self) -> bool { true }
} 
