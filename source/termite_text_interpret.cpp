/*
  ==============================================================================

    termite_text_interpret.cpp
    Created: 22 Oct 2024 4:12:11pm
    Author:  Jake Morgan

  ==============================================================================
*/

#include "termite_text_interpret.h"
using namespace termite;

text_interpret::text_interpret(){}
text_interpret::~text_interpret(){}

void text_interpret::grabString(termite::termite_String& str){
    data = str.returnCharacters();
}

void text_interpret::findFunc(){
    
}

bool text_interpret::isSin(std::unique_ptr<termite::termite_String>& inString){
    std::string test = inString->returnCharacters();
    if(test.compare("sin") == 0){return true;}
    else{return false;}
}

