use cgen::stmt::pattern_match::Arm;
use cgen::ast::Node;
use base::byte::ByteStr;

#[derive(Debug)]
pub struct Real(pub f64);

impl Arm for Real {
    fn is_simple(&self) -> bool { true }
} 

impl Node for Real {
    fn gen_code(&self) -> ByteStr {
        // #FIXME: coulde be better written by hand
        ByteStr::from_bytes(self.0.to_string().as_bytes())
    }
}
