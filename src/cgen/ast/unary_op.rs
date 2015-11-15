use cgen::ast::Node;
use base::byte::ByteStr;

pub struct UnaryPlus(Box<Node>);

impl UnaryPlus {
    pub fn new(arg: Box<Node>) -> Self {
        UnaryPlus(arg)
    }
}

impl Node for UnaryPlus {
    fn gen_code(&self) -> ByteStr {
        self.0.gen_code()
    }
}
