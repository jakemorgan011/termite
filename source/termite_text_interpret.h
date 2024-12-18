/*
  ==============================================================================

    termite_text_interpret.h
    Created: 22 Oct 2024 4:12:11pm
    Author:  Jake Morgan

  ==============================================================================
*/

#pragma once
#include "termite_data_types.h"
#include "JuceHeader.h"

namespace termite{
class text_interpret{
public:
    text_interpret();
    ~text_interpret();
    
    void grabString(termite::termite_String& str);
    bool isSin(std::unique_ptr<termite::termite_String>& inString);
    
    
private:
    char* data;
};

// a vector of control boxxes that have the ability to add strings over and over.
struct parse_node {
    std::string value;
    std::vector<std::shared_ptr<parse_node>> children;
    
    explicit parse_node(const std::string& val) : value(val){}
};

class lexer{
public:
    explicit lexer(const std::string& input) : input(input), pos(0) {
        tokenize();
    }
    std::string getNextToken(){
        if (current_token_index < tokens.size()){
            return tokens[current_token_index++];
        }
        return "";
    }
    
    std::string peek() const {
        if (current_token_index < tokens.size()) {
            return tokens[current_token_index];
        }
        return "";
    }
private:
    std::string input;
    size_t pos;
    std::vector<std::string> tokens;
    size_t current_token_index = 0;
    
    // essentially this adds to the vector of strings when a space is detected and creates a new "token"  or word or character etc.
    // push_back is very similar to .push() in js
    void tokenize(){
        // why unsigned type here ???
        // works but just wondering why i should do this.
        size_t start = 0;
        while (pos < input.size()){
            if(isspace(input[pos])){
                if(input[pos] == '\n'){
                    if (start < pos) tokens.push_back(input.substr(start, pos - start));
                    tokens.push_back("\n");
                    start = ++pos;
                }else{
                    if (start < pos) tokens.push_back(input.substr(start, pos - start));
                    start = ++pos;
                }
            }else {
                pos++;
            }
        }
        if(start < pos) tokens.push_back(input.substr(start, pos - start));
    }
};

class parser {
public:
    explicit parser(lexer& lexer) : lexer(lexer) {}
    std::shared_ptr<parse_node> parse(){
        return parse_text();
    }
private:
    lexer& lexer;
    
    std::shared_ptr<parse_node> parse_text(){
        auto textNode = std::make_shared<parse_node>("text");
        textNode->children.push_back(parseOscillator());
        textNode->children.push_back(parseSymbol());
        textNode->children.push_back(parseVar());
        return textNode;
    }
    
    // oscillator
    std::shared_ptr<parse_node> parseOscillator(){
        std::string token = lexer.getNextToken();
        // here is where you have to change it from a bunch of cases to a giant library of all the oscillators.
        if(token == "sin"){
            return std::make_shared<parse_node>(token);
        }else {
            return std::make_shared<parse_node>("nope");
        }
    }
    
    std::shared_ptr<parse_node> parseSymbol(){
        std::string token = lexer.getNextToken();
        // this will remain this way forever most likely.
        if(token == "+" || token == "-" || token == "=" || token == "*" || token == "/" || token == "%"){
            return std::make_shared<parse_node>(token);
        }else{
            return std::make_shared<parse_node>("nope");
        }
    }
    
    std::shared_ptr<parse_node> parseVar(){
        std::string token = lexer.getNextToken();
        if(token == "var"){
            return std::make_shared<parse_node>(token);
        }else {
            return std::make_shared<parse_node>("nope");
        }
    }
    
};

// testing ====
// TODO: these two functions are the only things not working at the moment.
//void printParseTree(const std::shared_ptr<parse_node>& test, int depth = 0){
//    std::cout<< std::string(depth * 2, ' ') << test->value << "\n";
//    for (auto& child : test->children){
//        printParseTree(child, depth + 1);
//    }
//}
//
//void parseTest(termite::termite_String& input){
//    try{
//        std::string test = input.returnCharacters();
//        lexer lexer(test);
//        parser parser(lexer);
//        
//        auto parseTree = parser.parse();
//        std::cout << "parsed text \n";
//        printParseTree(parseTree);
//    }catch (const std::exception& e){
//        std::cerr << "error" << e.what() << "\n";
//    }
//}
} // namespace end
