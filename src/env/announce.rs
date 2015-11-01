pub struct Announce<'a> {
    context: Option<&'a str>,
    message: &'a str,
    details: Option<&'a str>,
}

impl<'a> Announce<'a> {
    pub fn new(message: &'a str) -> Self {
        Announce {
            context: None,
            message: message,
            details: None,
        }
    }

    pub fn add_details(&mut self, details: &'a str) -> &mut Self {
        self.details = Some(details);
        self
    }

    pub fn add_context(&mut self, context: &'a str) -> &mut Self {
        self.context = Some(context);
        self
    }

    pub fn send(&self, code: i32) {
        println!("{} {}\n---------", self.class(code), code.abs());
        
        println!("[message] {}", self.message);

        if let Some(details) = self.details {
            println!("[details] {}", details);
        }

        if let Some(context) = self.context {
            println!("[context] {}", context);
        }

        println!("---------");
    }

    fn class(&self, code: i32) -> &'static str {
        if code < 0 { "|warning|" } else { " |error| " }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn announce_printing() {
        Announce::new("found malformed decimal value")
            .add_details("value was empty")
            .add_context("`program.c` line 20; tokenization phase")
            .send(-302);
    }
}
