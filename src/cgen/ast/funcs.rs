use cgen::ast::Node;
use base::byte::ByteStr;

pub struct Invocation {
    name: ByteStr,
    args: Vec<Box<Node>>
}

impl Invocation {
    pub fn new(name: ByteStr, args: Vec<Box<Node>>) -> Self {
        Invocation {
            name: name,
            args: args
        }
    }

    pub fn boxed(name: ByteStr, args: Vec<Box<Node>>) -> Box<Self> {
        Box::new(Invocation::new(name, args))
    }
}

impl Node for Invocation {
    fn gen_code(&self) -> ByteStr {
        let mut code = ByteStr::with_capacity(48);

        code.append(&self.name);
        code.push_byte(b'(');

        for arg in self.args.iter() {
            code.append(&arg.gen_code());
            code.push_byte(b',');
        }

        code.last_byte_set(b')');
        code
    }
}
