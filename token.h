#pragma once
#include <string>
#include <variant>
#include <iostream>

enum class TokenType {
    // 关键字
    IF, ELSE, WHILE, FOR, RETURN,
    
    IDENTIFIER,  // 变量名、函数名
    INTEGER,     
    FLOAT,       
    STRING,     
    
    // 运算符
    PLUS,        
    MINUS,       
    MULTIPLY,   
    DIVIDE,      
    ASSIGN,      
    
    // 比较运算符
    EQUAL,       
    NOT_EQUAL,   
    LESS,        
    LESS_EQUAL,  
    GREATER,     
    GREATER_EQUAL, 
    
    // 分隔符
    SEMICOLON,   
    COMMA,       
    LEFT_PAREN,  // (
    RIGHT_PAREN, // )
    LEFT_BRACE,  
    RIGHT_BRACE, 
    
    END_OF_FILE,
    UNKNOWN
};

class Token {
public:
    using ValueType = std::variant<std::monostate, int, double, std::string>;
    
    Token(TokenType type) : type(type) {}
        
    Token(TokenType type, ValueType value) : type(type), value(std::move(value)) {}
        
    TokenType getType() const { 
        return type; 
    }
    
    template<typename T>
    T getValue() const {
        return std::get<T>(value);
    }
    
    bool hasValue() const {
        return !std::holds_alternative<std::monostate>(value);
    }
    
    std::string toString() const;
    
private:
    TokenType type;
    ValueType value;
};
