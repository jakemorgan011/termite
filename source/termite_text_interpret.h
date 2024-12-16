/*
  ==============================================================================

    termite_text_interpret.h
    Created: 22 Oct 2024 4:12:11pm
    Author:  Jake Morgan

  ==============================================================================
*/

#pragma once
#include "termite_header.h"
#include "termite_data_types.h"

namespace termite{
class text_interpret{
public:
    text_interpret();
    ~text_interpret();
    
    void grabString(termite::termite_String& str);
    void findFunc();
    bool isSin(std::unique_ptr<termite::termite_String>& inString);
    
    
private:
    char* data;
};
}
