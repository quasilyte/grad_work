use env::Announce;
use base::Bytes;

// #TODO: write helper macro which takes N expressions,
// builds an Announce and sends it as error

pub fn decimal_parse() -> ! {
    Announce::new("found malformed literal for Decimal")
        .send_as_error(1);
}

pub fn unexpected_token(unit: &Bytes) -> ! {
    Announce::new("unexpected token met")
        .add_details(&format!("looking at `{}`", String::from_utf8(unit.to_owned()).unwrap()))
        .send_as_error(2);
}
