#pragma once
#include "ast.h"
#include "lexer.h"

class Parser {
public:
    explicit Parser(std::vector<Token> tokens) : tokens_(std::move(tokens)) {}
    Program parseProgram();                     // statement* End

private:
    Assign parseStatement();                    // Ident '=' expr ';'
    std::unique_ptr<Expr> parseExpr();          // term   (('+' | '-') term)*
    std::unique_ptr<Expr> parseTerm();          // factor (('*' | '/') factor)*
    std::unique_ptr<Expr> parseFactor();        // Number | Ident | '(' expr ')'

    // Helpers
    const Token& peek() const { return tokens_[pos_]; }        // look at the current token, don't move
    Token advance() { return tokens_[pos_++]; }                  // take the current token and move on
    bool check(TokenType t) const { return peek().type == t; }
    Token expect(TokenType t, const std::string& what);          // must be there, otherwise throw

    std::vector<Token> tokens_;
    size_t pos_ = 0;
};