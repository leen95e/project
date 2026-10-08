#pragma once
#include <memory>
#include <string>
#include <vector>

// Base class for every expression node in the tree.
struct Expr {
    virtual ~Expr() = default;                  // deleting through Expr* must reach the derived destructor
    virtual std::string toString() const = 0;   // fully parenthesized, for debugging
};

// A number: 3
struct NumberExpr : Expr {
    long value;
    explicit NumberExpr(long v) : value(v) {}
    std::string toString() const override { return std::to_string(value); }
};

// A variable: x
struct VarExpr : Expr {
    std::string name;
    explicit VarExpr(std::string n) : name(std::move(n)) {}
    std::string toString() const override { return name; }
};

// A binary operation: left op right
struct BinaryExpr : Expr {
    char op;                                    // '+', '-', '*', '/'
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    BinaryExpr(char o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(o), left(std::move(l)), right(std::move(r)) {}
    std::string toString() const override {
        return "(" + left->toString() + " " + op + " " + right->toString() + ")";
    }
};

// One statement: name = value;
struct Assign {
    std::string name;
    std::unique_ptr<Expr> value;
};

using Program = std::vector<Assign>;