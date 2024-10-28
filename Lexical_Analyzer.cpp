#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <cctype>
#include <unordered_set>

using namespace std;

enum TokenType {
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    LITERAL,
    SYMBOL
};

unordered_set<string> keywords = {"asm","auto", "break", "case","catch","char", "class", "const", "continue", "default", "delete",
                                  "do", "double", "else", "enum", "extern", "float","for", "friend", "goto", "if", "inline", "int", 
                                  "long", "new", "operator", "private", "protected", "public", "register","return", "short", "signed",
                                  "sizeof", "static", "struct","switch","template", "this", "throw", "try", "typedef", "union",
                                  "unsigned", "virtual", "void", "volatile", "while"};

unordered_set<string> operators = {"++", "--", "=", "+", "-", "*", "/", "%", ">", "<", "==", "!=", ">=", "<=", "&&", 
                                    "||", "!", "+=", "-=", "*=", "/=", "&", "|", "<<", ">>", "~", "^", "?:"};

unordered_set<string> symbols = {"[]", "()", "{}", ",", "#", "*", ".", ";"};

struct Token {
    string value;
    TokenType type;
};

void categorizeToken(const string& token, stack<Token>& symbolTable) {
    Token t;
    if (keywords.find(token) != keywords.end()) {
        t = {token, KEYWORD};
    } else if (isdigit(token[0])) {
        t = {token, LITERAL};
    } else if (symbols.find(token) != symbols.end()) {
        t = {token, SYMBOL};
    } else if (operators.find(token) != operators.end()) {
        t = {token, OPERATOR};
    } else if (isalpha(token[0]) || token[0] == '_') {
        t = {token, IDENTIFIER};
    }
    symbolTable.push(t);
}

void printTokens(stack<Token>& symbolTable) {
    vector<Token> tokenBuffer;
    while (!symbolTable.empty()) {
        tokenBuffer.push_back(symbolTable.top());
        symbolTable.pop();
    }

    
    for (auto tokenIterator = tokenBuffer.rbegin(); tokenIterator != tokenBuffer.rend(); ++tokenIterator) {
        switch (tokenIterator->type) {
            case KEYWORD:
                cout << "< " << tokenIterator->value << " : (Keyword) >   ";
                break;
            case IDENTIFIER:
                cout << "< " << tokenIterator->value << " : (Identifier) >   ";
                break;
            case OPERATOR:
                cout << "< " << tokenIterator->value << " : (Operator) >   ";
                break;
            case LITERAL:
                cout << "< " << tokenIterator->value << " : (Literal) >   ";
                break;
            case SYMBOL:
                cout << "< " << tokenIterator->value << " : (Symbol) >   ";
                break;
            default:
                break;
        }
    }
}

int main() {
    string input;

    cout << "Enter a statement: ";
    getline(cin, input);

    istringstream iss(input);
    string token;
    stack<Token> symbolTable;

    while (iss >> token) {
        
        if (token.back() == ';') {
            token.pop_back();
            categorizeToken(";", symbolTable);
        }
        categorizeToken(token, symbolTable);
    }
    
    cout << "---LEXICAL ANALYSIS---" << endl;
    printTokens(symbolTable);
    return 0;
}

