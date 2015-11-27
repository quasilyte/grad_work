use env::Announce;
use base::{Byte, Bytes};

// #FIXME: need a better error reporting API

// #TODO: write helper macro which takes N expressions,
// builds an Announce and sends it as error

pub fn decimal_parse() -> ! {
    Announce::new("found malformed literal for Decimal")
        .send_as_error(1);
}

pub fn unexpected_token(bytes: &Bytes) -> ! {
    Announce::new("unexpected token met")
        .add_details(&format!("looking at `{}` bytes", String::from_utf8(bytes.to_owned()).unwrap()))
        .add_context("on tokenization")
        .send_as_error(2);
}

pub fn malformed_identifier(byte: Byte) -> ! {
    Announce::new("found invalid character sequence")
        .add_details(&format!("looking at `{}` byte", byte as char))
        .add_context("on tokenization; parsing identifier")
        .send_as_error(2);
}
