pub type Byte = u8;
pub type Bytes = [u8];

pub type BytePredicate = fn(Byte) -> bool;

// #TODO: maybe I need a new type rather than a typedef for `u8`?
pub trait ByteChar {
    fn is_digit(self) -> bool;
}

impl ByteChar for Byte {
    // #TODO: check whenever `if` and ascii number range check is more efficient
    fn is_digit(self) -> bool {
        match self {
            b'0'...b'9' => true,
            _ => false
        }
    }
}

// #FIXME: sometimes works not how intended
macro_rules! byte_predicate {
    ($($body: pat),*) => {{
        fn predicate(c: Byte) -> bool {
            match c {
                $($body => true,)*
                _ => false,
            }
        }
        predicate
    }};
    
    ($arg: ident, $body: expr) => {{
        fn predicate($arg: Byte) -> bool { $body }
        predicate
    }};
    
    ($arg: ident, $body: block) => {{
        fn predicate($arg: Byte) -> bool $body
        predicate
    }};
}
