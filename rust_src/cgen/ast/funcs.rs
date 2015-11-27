use cgen::ast::Node;
use base::byte::ByteStr;

// #TODO: could be used in more places..
macro_rules! add_ctors {
    ($name:ident, $([$param:ident, $t:ty]),*) => {
        impl $name {
            pub fn new($($param: $t,)*) -> Self {
                $name {
                    $($param: $param,)*
                }
            }

            pub fn boxed($($param: $t,)*) -> Box<Self> {
                Box::new($name::new($($param,)*))
            }
        }
    };
}

pub struct Invocation {
    name: ByteStr,
    args: Vec<Box<Node>>
}
add_ctors!(Invocation, [name, ByteStr], [args, Vec<Box<Node>>]);

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

pub struct VarDeclaration {
    lvalue: ByteStr,
    rvalue: Box<Node>,
}
add_ctors!(VarDeclaration, [lvalue, ByteStr], [rvalue, Box<Node>]);

impl Node for VarDeclaration {
    fn gen_code(&self) -> ByteStr {
        let mut code = ByteStr::with_capacity(64);
        
        code.push_bytes(b"Box ");
        code.append(&self.lvalue);
        
        code.push_byte(b'=');
        
        code.append(&self.rvalue.gen_code());
        code.push_byte(b';');

        code
    }
}
