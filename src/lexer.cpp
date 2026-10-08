#include "lexer.h"
#include <cctype>
#include <stdexcept>
std::vector<Token> tokenize(const std::string &source)
{
    std::vector<Token> result ;
    Token t;
    int line = 1;
    size_t i = 0;
    while (i < source.size())
    {
        auto push = [&](TokenType type, const std::string& text) {
                    result.push_back({type, text, line});
                    };
        if (std::isspace(source[i])) { 
            if (source[i] == '\n') line++;
            i++; 
            continue;
        }
        if (std::isalpha(static_cast<unsigned char>(source[i])) || source[i] == '_'){
            size_t start = i;
            while (i < source.size() &&
                (std::isalnum(static_cast<unsigned char>(source[i])) || source[i] == '_')) {
                i++;                              
            }
            push(TokenType::Ident,source.substr(start, i - start) );
            continue;
        }
        if (std::isdigit(static_cast<unsigned char>(source[i]))){
            size_t start = i;
            while (i < source.size() && std::isdigit(static_cast<unsigned char>(source[i]))) {
                i++;                              
            }
            push(TokenType::Number, source.substr(start, i - start) );
            continue;
        }

        switch (source[i])
        {
        case '+':
            push(TokenType::Plus, "+"); 
            break;
        case '-':
            push(TokenType::Minus, "-");            
            break;
        case '*':
            push(TokenType::Star, "*");          
            break;
        case '/':
            push(TokenType::Slash, "/");          
            break;
        case '(':
            push(TokenType::LParen, "(");       
            break;
        case ')':
            push(TokenType::RParen, ")"); 
            break;
        case '=':
            push(TokenType::Assign, "="); 
            break;
        case ';':
            push(TokenType::Semicolon, ";"); 
            break;
        default:
            throw std::runtime_error(std::string("Unexpected character '") + source[i] +
                         "' at line " + std::to_string(line));
        }
        i++; 
    }
    t.type = TokenType::End;
    t.text = "";
    t.line = line;
    result.push_back(t);
    return result;
}