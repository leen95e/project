#include "parser.h"
#include <stdexcept>



Token Parser::expect(TokenType t, const std::string &what)
{
    if (!check(t)) {
        throw std::runtime_error("Expected " + what + " at line " + std::to_string(peek().line) +
                                 ", got '" + peek().text + "'");
    }
    return advance();
}

Program Parser::parseProgram()
{
    Program prog;
    while (!check(TokenType::End)) {
        prog.push_back(parseStatement());
    }
    return prog;
}

Assign Parser::parseStatement()
{
    Token identToken = expect(TokenType::Ident, "identifier");
    expect(TokenType::Assign, "'='");
    
    std::unique_ptr<Expr> value = parseExpr();
    
    expect(TokenType::Semicolon, "';'");
    
    // Assuming identToken.text contains the variable name string
    return Assign{identToken.text, std::move(value)};
}

std::unique_ptr<Expr> Parser::parseExpr()
{
    auto left = parseTerm();
    
    while (check(TokenType::Plus) || check(TokenType::Minus)) {
        Token opToken = advance();
        // Assuming opToken.text[0] gives the character '+' or '-'
        char op = opToken.text[0]; 
        
        auto right = parseTerm();
        left = std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));
    }
    
    return left;
}

std::unique_ptr<Expr> Parser::parseTerm()
{
    auto left = parseFactor();
    
    while (check(TokenType::Star) || check(TokenType::Slash)) {
        Token opToken = advance();
        char op = opToken.text[0];
        
        auto right = parseFactor();
        left = std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));
    }
    
    return left;
}

std::unique_ptr<Expr> Parser::parseFactor()
{
    if (check(TokenType::Number)) {
        Token numToken = advance();
        // Convert the string representation of the number to a long
        long val = std::stol(numToken.text); 
        return std::make_unique<NumberExpr>(val);
    } 
    else if (check(TokenType::Ident)) {
        Token identToken = advance();
        return std::make_unique<VarExpr>(identToken.text);
    } 
    else if (check(TokenType::LParen)) {
        advance(); // Consume '('
        auto expr = parseExpr();
        expect(TokenType::RParen, "')'"); // Must be closed
        return expr;
    }
    
    throw std::runtime_error("Parser Error: Unexpected token in factor. Expected Number, Identifier, or '('");
}
