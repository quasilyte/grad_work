use cgen::stmt::pattern_match::Arm;
use cgen::ast::Ast;

#[derive(Debug)]
pub struct Real(pub f64);

impl Arm for Real {
    fn is_simple(&self) -> bool { true }
} 

impl Ast for Real {
    fn gen_code(&self) -> String {
        self.0.to_string()
    }
}
