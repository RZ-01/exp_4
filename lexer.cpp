#include "lexer.h"
#include <cctype>

const std::unordered_map<std::string, TokenType> Lexer::keywords = {
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE},
    {"for", TokenType::FOR},
    {"return", TokenType::RETURN}
};

Lexer::Lexer(const std::string& source) : source(source) {}

Token Lexer::nextToken() {
    if (hasReadToken) {
        hasReadToken = false;
        return currentToken;
    }
    
    skipWhitespace();
    if (isAtEnd()) {
        return Token(TokenType::END_OF_FILE);
    }
    
    return scanToken();
}

Token Lexer::peekToken() {
    if (!hasReadToken) {
        currentToken = nextToken();
        hasReadToken = true;
    }
    return currentToken;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (true) {
        Token token = nextToken();
        tokens.push_back(token);
        if (token.getType() == TokenType::END_OF_FILE) {
            break;
        }
    }
    return tokens;
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return source[position];
}

char Lexer::advance() {
    return source[position++];
}

bool Lexer::match(char expected) {
    if (isAtEnd() || source[position] != expected) {
        return false;
    }
    advance();
    return true;
}

void Lexer::skipWhitespace() {
    while (true) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                advance();
                break;
                
            case '/':
                if (position + 1 < source.size() && source[position + 1] == '/') {
                    // 单行注释
                    while (peek() != '\n' && !isAtEnd()) {
                        advance();
                    }
                } else if (position + 1 < source.size() && source[position + 1] == '*') {
                    // 多行注释
                    advance(); 
                    advance(); 
                    
                    while (!isAtEnd() && !(peek() == '*' && position + 1 < source.size() && source[position + 1] == '/')) 
                        advance();

                    if (!isAtEnd()) {
                        advance(); 
                        advance(); 
                    }
                } else 
                    return;
                break;
            default:
                return;
        }
    }
}

Token Lexer::scanToken() {
    char c = advance();
    
    if (isAlpha(c)) {
        return identifier();
    }
    
    if (isDigit(c)) {
        position--; // 回退一个字符
        return number();
    }
    
    switch (c) {
        case '(': return Token(TokenType::LEFT_PAREN);
        case ')': return Token(TokenType::RIGHT_PAREN);
        case '{': return Token(TokenType::LEFT_BRACE);
        case '}': return Token(TokenType::RIGHT_BRACE);
        case ',': return Token(TokenType::COMMA);
        case ';': return Token(TokenType::SEMICOLON);
        
        case '+': return Token(TokenType::PLUS);
        case '-': return Token(TokenType::MINUS);
        case '*': return Token(TokenType::MULTIPLY);
        case '/': return Token(TokenType::DIVIDE);
        
        case '=':
            return Token(match('=') ? TokenType::EQUAL : TokenType::ASSIGN);
        
        case '!':
            return Token(match('=') ? TokenType::NOT_EQUAL : TokenType::UNKNOWN);
        
        case '<':
            return Token(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        
        case '>':
            return Token(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        
        case '"': return string();
    }
    
    return Token(TokenType::UNKNOWN);
}

Token Lexer::identifier() {
    size_t start = position - 1;
    
    while (isAlphaNumeric(peek())) {
        advance();
    }
    
    std::string text = source.substr(start, position - start);
    
    auto it = keywords.find(text);
    TokenType type = (it != keywords.end()) ? it->second : TokenType::IDENTIFIER;
    
    return Token(type, text);
}

Token Lexer::number() {
    size_t start = position;
    bool isFloat = false;
    
    while (isDigit(peek())) {
        advance();
    }
    
    if (peek() == '.' && isDigit(source[position + 1])) {
        isFloat = true;
        advance(); 
        
        while (isDigit(peek())) {
            advance();
        }
    }
    
    std::string numStr = source.substr(start, position - start);
    
    if (isFloat) {
        double value = std::stod(numStr);
        return Token(TokenType::FLOAT, value);
    } else {
        int value = std::stoi(numStr);
        return Token(TokenType::INTEGER, value);
    }
}

Token Lexer::string() {
    std::string value;
    
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\\' && position + 1 < source.size()) {
            advance();
            switch (peek()) {
                case 'n': value += '\n'; break;
                case 't': value += '\t'; break;
                case 'r': value += '\r'; break;
                case '\\': value += '\\'; break;
                case '"': value += '"'; break;
                default: value += peek(); break;
            }
        } else {
            value += peek();
        }
        advance();
    }
    
    if (isAtEnd()) {
        return Token(TokenType::UNKNOWN); 
    }
    advance();
    
    return Token(TokenType::STRING, value);
}

bool Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

bool Lexer::isAtEnd() const {
    return position >= source.size();
}
