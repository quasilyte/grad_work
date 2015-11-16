use cgen::ast::Node;
use base::byte::ByteStr;

pub struct UnaryAdd(Box<Node>);

impl UnaryAdd {
    pub fn new(arg: Box<Node>) -> Self {
        UnaryAdd(arg)
    }

    pub fn boxed(arg: Box<Node>) -> Box<Self> {
        Box::new(UnaryAdd(arg))
    }
}

impl Node for UnaryAdd {
    fn gen_code(&self) -> ByteStr {
        self.0.gen_code()
    }
}
