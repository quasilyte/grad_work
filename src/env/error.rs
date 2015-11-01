use env::Announce;

pub fn decimal_parse() -> ! {
    Announce::new("found malformed literal for Decimal")
        .send_as_error(1);
}
