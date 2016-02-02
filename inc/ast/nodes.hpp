#pragma once

#include <string>
#include <vector>

namespace Ast {

class Node {
public:
  virtual void write(std::string &buf) const = 0;
  virtual const char* return_type() const {
    throw '?';
  }
};

class Fn: public Node {
public:
  Fn(Token id, Token param, std::vector<Node*> body):
    id{id}, param{param}, body{body} {};

  void write(std::string &buf) const {
    buf.append(body[body.size() - 1]->return_type());
    buf.push_back(' ');
    buf.append(id.value, id.len);
    buf.push_back('(');
    buf.append(param.value, param.len);
    buf.append("){");
    for (Node* p : body) {
      p->write(buf);
      buf.push_back(';');
    }
    buf.push_back('}');
  }

private:
  Token id;
  Token param;
  std::vector<Node*> body;
};

class Return: public Node {
public:
  Return(Node *expr): expr{expr} {}

  const char* return_type() const {
    return expr->return_type();
  }

  void write(std::string &buf) const {
    buf.append("return ");
    expr->write(buf);
    // buf.push_back(';');
  }

private:
  Node *expr;
};

class Sum: public Node {
public:
  Sum(Node *lhs, Node *rhs): lhs{lhs}, rhs{rhs} {}

  const char* return_type() const {
    return lhs->return_type();
  }

  void write(std::string &buf) const {
    lhs->write(buf);
    buf.append("+");
    rhs->write(buf);
  }
private:
  Node *lhs;
  Node *rhs;
};

class Value: public Node {
protected:
  Value(Token t): t{t} {}

  Token t;
};

class String: public Value {
public:
  String(Token t): Value{t} {}

  const char* return_type() const {
    return "str";
  }

  void write(std::string &buf) const {
    buf.push_back('"');
    buf.append(t.value, t.len);
    buf.push_back('"');
  }
};

class Decimal: public Value {
public:
  Decimal(Token t): Value{t} {}

  const char* return_type() const {
    return "decimal";
  }

  void write(std::string &buf) const {
    buf.append(t.value, t.len);
  }
};

class Real: public Value {
public:
  Real(Token t): Value{t} {}

  const char* return_type() const {
    return "real";
  }

  void write(std::string &buf) const {
    buf.append(t.value, t.len);
  }
};

}
