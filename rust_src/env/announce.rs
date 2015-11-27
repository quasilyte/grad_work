use std::process;

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

    fn print_header(&self, class: &str, code: i32) {
        assert!(code > 0);
        println!("{} {}\n---------", class, code);
    }

    pub fn send_as_warning(&self, code: i32) {
        self.print_header("|warning|", code);
        self.send();
    }

    pub fn send_as_error(&self, code: i32) -> ! {
        self.print_header("| error |", code);
        self.send();
        process::exit(0);
    }

    pub fn send(&self) {
        println!("[message] {}", self.message);
        
        if let Some(details) = self.details {
            println!("[details] {}", details);
        }
        if let Some(context) = self.context {
            println!("[context] {}", context);
        }

        println!("---------");
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
