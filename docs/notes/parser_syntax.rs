Ident(var) Equals assign[rhs] => Expr {
    span: span!(),
    node: Expr_::Assign(var, Box::new(rhs)),
}

Ident(lhs) Eq Expr(rhs) => assign(lhs, rhs);
bin_op!(assign := Ident Eq Expr);

Ident(object) Dot Ident(method) => invoke_method;

    
