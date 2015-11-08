use base::byte::*;

pub struct Reader<'a> {
    buf: &'a Bytes,
    pub pos: usize
}

impl<'a> Reader<'a> {        
    fn at(&self, ch: Byte) -> bool {
        self.buf[self.pos] == ch
    }

    fn byte(&self) -> Byte {
        self.buf[self.pos]
    }

    //
    // Pub
    //
    
    pub fn new(buf: &'a Bytes) -> Self {
        Reader {
            buf: buf,
            pos: 0,
        }
    }

    pub fn next(&mut self) {
        self.pos += 1;
    }

    pub fn stab(&self, offset: usize) -> &Bytes {
        &self.buf[offset .. self.pos]
    }

    pub fn next_byte(&mut self) -> Byte {
        self.next();
        self.buf[self.pos - 1]
    }

    pub fn skip_while(&mut self, predicate: fn(Byte) -> bool) {
        while (predicate)(self.byte()) {
            self.next();
        }
    }

    pub fn skip_until(&mut self, predicate: fn(Byte) -> bool) {
        while !(predicate)(self.byte()) {
            self.next();
        }
    }
}

