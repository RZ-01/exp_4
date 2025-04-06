#pragma once
#include "token.h"
#include <string>
#include <vector>
#include <unordered_map>

class Lexer {
public:
    explicit Lexer(const std::string& source);
    
    Token nextToken();

    // 查看下一个token
    Token peekToken();
    
    // 获取所有token
    std::vector<Token> tokenize();
    
private:
    std::string source;
    size_t position = 0;
    Token currentToken = Token(TokenType::UNKNOWN);
    bool hasReadToken = false;
    
    static const std::unordered_map<std::string, TokenType> keywords;
    
    char peek() const;
    char advance();
    bool match(char expected);
    void skipWhitespace();
    Token scanToken();
    
    Token identifier();
    Token number();
    Token string();
    
    static bool isAlpha(char c);
    static bool isDigit(char c);
    static bool isAlphaNumeric(char c);
    
    bool isAtEnd() const;
};
