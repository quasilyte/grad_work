use cgen::ast::Ast;

struct BinOp {
    lhs: Box<Ast>,
    rhs: Box<Ast>,
}

