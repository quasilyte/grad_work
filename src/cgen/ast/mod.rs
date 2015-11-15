pub trait Ast {
    fn gen_code(&self) -> String;
}

pub mod bin_op;
