#include "lexer.h"

std::vector<Token> tokenize(const std::string &source)
{
    std::vector<Token> result ;
    Token t;
    for (size_t i = 0; i < source.length(); i++)
    {
        
        if (source[i] != ' ')
        {
            if (source[i] == '('){
                t.type = TokenType::LParen;
                t.text = '(';
                result.push_back(t);
            }
            if (source[i] == ')'){
                t.type = TokenType::RParen;
                t.text = ')';
                result.push_back(t);
            }
            if (source[i] == '+'){
                t.type = TokenType::Plus;
                t.text = '+';
                result.push_back(t);
            }
            if (source[i] == '-'){
                t.type = TokenType::Minus;
                t.text = '-';
                result.push_back(t);
            }
            if (source[i] == '*'){
                t.type = TokenType::Star;
                t.text = '*';
                result.push_back(t);
            }
            if (source[i] == '/'){
                t.type = TokenType::Slash;
                t.text = '/';
                result.push_back(t);
            }
            if (source[i] == '='){
                t.type = TokenType::Assign;
                t.text = '=';
                result.push_back(t);
            }
            if (source[i] == ';'){
                t.type = TokenType::Semicolon;
                t.text = ';';
                result.push_back(t);
            }
            if (std::isalpha(source[i]) || source[i] == '_'){
                size_t start = i;
                while (i < source.size() &&
                    (std::isalnum(static_cast<unsigned char>(source[i])) || source[i] == '_')) {
                    i++;                              
                }
                t.type = TokenType::Ident;
                t.text = source.substr(start, i - start);
                result.push_back(t);
            }
            if (std::isdigit(static_cast<unsigned char>(source[i])) || source[i] == '-'){
                size_t start = i;
                while (i < source.size() && std::isdigit(static_cast<unsigned char>(source[i]))) {
                    i++;                              
                }
                t.type = TokenType::Ident;
                t.text = source.substr(start, i - start);
                result.push_back(t);
            }
        }
    }
    return result;
}