pub type Byte = u8;
pub type Bytes = [u8];

pub type BytePredicate = fn(Byte) -> bool;
pub type BytesPredicate = fn(&Bytes) -> bool;

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

macro_rules! bytes_matcher {
    ($($bytes: pat),*) => {{
        fn bytes_matcher(bytes: &Bytes) -> bool {
            match bytes {
                $($bytes => true,)*
                _ => false
            }
        }
        bytes_matcher
    }};
}

macro_rules! byte_matcher {
    ($($range: pat),*) => {{
        fn byte_matcher(byte: Byte) -> bool {
            match byte {
                $($range => true,)*
                _ => false
            }
        }
        byte_matcher
    }};
    
    ($byte: expr) => {{
        fn byte_matcher(byte: Byte) -> bool {
            $byte == byte
        }
        byte_matcher
    }};
    
    ($byte: expr, $($other_byte: expr),*) => {{
        fn byte_matcher(byte: Byte) -> bool {
            $byte == byte $(|| $other_byte == byte)*
        }
        byte_matcher
    }};
}
