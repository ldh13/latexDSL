Expr :=
    Expr "+" Term
  | Expr "-" Term
  | Term

Term :=
    Term "\*" Factor
  | Term "/" Factor
  | Factor

Factor :=
    Unary "^" Factor
  | Unary

Unary :=
    "+" Unary
  | "-" Unary
  | Primary

Primary :=
    NUMBER
  | IDENTIFIER
  | "(" Expr ")"