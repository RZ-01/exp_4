#include "token.h"
#include <unordered_map>

std::string Token::toString() const {
    static const std::unordered_map<TokenType, std::string> typeNames = {
        {TokenType::IF, "IF"},
        {TokenType::ELSE, "ELSE"},
        {TokenType::WHILE, "WHILE"},
        {TokenType::FOR, "FOR"},
        {TokenType::RETURN, "RETURN"},
        {TokenType::IDENTIFIER, "IDENTIFIER"},
        {TokenType::INTEGER, "INTEGER"},
        {TokenType::FLOAT, "FLOAT"},
        {TokenType::STRING, "STRING"},
        {TokenType::PLUS, "PLUS"},
        {TokenType::MINUS, "MINUS"},
        {TokenType::MULTIPLY, "MULTIPLY"},
        {TokenType::DIVIDE, "DIVIDE"},
        {TokenType::ASSIGN, "ASSIGN"},
        {TokenType::EQUAL, "EQUAL"},
        {TokenType::NOT_EQUAL, "NOT_EQUAL"},
        {TokenType::LESS, "LESS"},
        {TokenType::LESS_EQUAL, "LESS_EQUAL"},
        {TokenType::GREATER, "GREATER"},
        {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
        {TokenType::SEMICOLON, "SEMICOLON"},
        {TokenType::COMMA, "COMMA"},
        {TokenType::LEFT_PAREN, "LEFT_PAREN"},
        {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
        {TokenType::LEFT_BRACE, "LEFT_BRACE"},
        {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
        {TokenType::END_OF_FILE, "END_OF_FILE"},
        {TokenType::UNKNOWN, "UNKNOWN"}
    };
    
    std::string result = typeNames.at(type);
    
    if (hasValue()) {
        result += " Value: ";
        if (type == TokenType::INTEGER) {
            result += std::to_string(getValue<int>());
        } else if (type == TokenType::FLOAT) {
            result += std::to_string(getValue<double>());
        } else if (type == TokenType::IDENTIFIER || type == TokenType::STRING) {
            result += "'" + getValue<std::string>() + "'";
        }
    }
    
    return result;
}
