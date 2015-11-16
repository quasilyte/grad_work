macro_rules! match_panic {
    ($($cond:pat => $action:expr),*) => {
        match m {
            $($cond => $action,)*
            got @ _ => panic!(
                "expected one of the: {:?}, got: {:?}",
                [ $(stringify!($cond),)* ],
                got
            ),
        }
    };
}
