use std::fmt;
use cgen::ast::Node;

pub type Byte = u8;
pub type Bytes = [u8];

pub type BytePredicate = fn(Byte) -> bool;
pub type BytesPredicate = fn(&Bytes) -> bool;

pub struct ByteStr(Vec<Byte>);

impl ByteStr {
    pub fn with_capacity(cap: usize) -> Self {
        ByteStr(Vec::with_capacity(cap))
    }
    
    pub fn from_bytes(bytes: &Bytes) -> Self {
        ByteStr(bytes.to_owned())
    }

    pub fn push_bytes(&mut self, bytes: &Bytes) {
        self.0.extend(bytes.iter().cloned());
    }

    pub fn push_byte(&mut self, byte: Byte) {
        self.0.push(byte)
    }

    pub fn append(&mut self, other: &Self) {
        self.0.extend(other.0.iter().cloned());
    }
    
    fn to_string(&self) -> String {
        String::from_utf8(self.0.clone()).unwrap()
    }
}

impl fmt::Debug for ByteStr {
    fn fmt(&self, stream: &mut fmt::Formatter) -> fmt::Result {
        write!(stream, "`{}`", self.to_string())
    }
}

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

impl Node for ByteStr {
    fn gen_code(&self) -> ByteStr {
        // String::from_utf8(self.0.clone()).unwrap()
        ByteStr::from_bytes(b"455")
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

    ($($range: pat),*) => {{
        fn byte_matcher(byte: Byte) -> bool {
            match byte {
                $($range => true,)*
                _ => false
            }
        }
        byte_matcher
    }};
}
