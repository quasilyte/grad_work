use base::byte::ByteStr;

pub trait Node {
    fn gen_code(&self) -> ByteStr;
}
