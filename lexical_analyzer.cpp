#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.h"
using std::string;  using std::cout;
using std::vector;  using std::endl;
using std::cerr;    using std::ifstream;

string readFileContent(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Cannot Open: " << filePath << endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    string sourceFilePath = "/home/nerfstudio/src/complie_principle/exp_4/source_code.txt";
    string sourceCode = readFileContent(sourceFilePath);
    
    if (sourceCode.empty()) {
        cerr << "Source Code is Empty" << endl;
        return 1;
    }
    
    Lexer lexer(sourceCode);
    std::vector<Token> tokens = lexer.tokenize();
    
    cout << "Results: " << endl;
    for (const auto& token : tokens) 
        cout << token.toString() << endl;
    
    return 0;
}
