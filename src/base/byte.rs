pub type Byte = u8;
pub type Bytes = [u8];

pub type BytePredicate = fn(Byte) -> bool;

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
