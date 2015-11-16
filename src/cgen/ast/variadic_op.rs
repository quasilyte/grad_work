use cgen::ast::Node;
use base::byte::ByteStr;

macro_rules! gen_variadic_op {
    ($name: ident, $op: expr) => {
        pub struct $name(Vec<Box<Node>>);
        
        
        impl $name {
            pub fn new(args: Vec<Box<Node>>) -> Self {
                $name(args)
            }

            pub fn boxed(args: Vec<Box<Node>>) -> Box<Self> {
                Box::new($name(args))
            }
        }

        impl Node for $name {
            fn gen_code(&self) -> ByteStr {
                let mut code = ByteStr::with_capacity(8 * self.0.len());
                let mut iter = self.0.iter();

                code.append(&iter.next().unwrap().gen_code());

                while let Some(arg) = iter.next() {
                    code.push_bytes($op);
                    code.append(&arg.gen_code());
                }

                code
            }
        }
    };
}

macro_rules! gen_variadic_ops {
    ($($name: ident $op: expr);*) => {
        $(gen_variadic_op!($name, $op);)*
    };
}

gen_variadic_ops!(
    Add b"+";
    Sub b"-";
    Mul b"*";
    Div b"/"
);

