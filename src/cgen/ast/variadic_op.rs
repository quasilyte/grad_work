use cgen::ast::Node;
use base::byte::ByteStr;

struct VariadicOp {
    args: Vec<Box<Node>>
}

pub struct Plus(VariadicOp);

impl Plus {
    pub fn new(args: Vec<Box<Node>>) -> Self {
        Plus(VariadicOp {
            args: args
        })
    }
}

impl Node for Plus {
    fn gen_code(&self) -> ByteStr {
        let mut code = ByteStr::with_capacity(8 * self.0.args.len());
        let mut iter = self.0.args.iter();

        code.append(&iter.next().unwrap().gen_code());

        while let Some(arg) = iter.next() {
            code.push_byte(b'+');
            code.append(&arg.gen_code());
        }

        code
    }
}
