#pragma once
#include <string>
#include <vector>

enum class TokenType {
    Number,     // 42
    Ident,      // x, total
    Plus,       // +
    Minus,      // -
    Star,       // *
    Slash,      // /
    LParen,     // (
    RParen,     // )
    Assign,     // =
    Semicolon,  // ;
    End         // end of input
};

struct Token {
    TokenType type;
    std::string text;  // original text: "42", "x", "+"
    int line;          // for error messages
};

// Splits the source text into tokens. Throws std::runtime_error on an unknown character.
std::vector<Token> tokenize(const std::string& source);

inline const char* tokenTypeName(TokenType t) {
    switch (t) {
        case TokenType::Number:    return "Number";
        case TokenType::Ident:     return "Ident";
        case TokenType::Plus:      return "Plus";
        case TokenType::Minus:     return "Minus";
        case TokenType::Star:      return "Star";
        case TokenType::Slash:     return "Slash";
        case TokenType::LParen:    return "LParen";
        case TokenType::RParen:    return "RParen";
        case TokenType::Assign:    return "Assign";
        case TokenType::Semicolon: return "Semicolon";
        case TokenType::End:       return "End";
    }
    return "?";
}