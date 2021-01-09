#pragma once

#include <iostream>
#include <algorithm> 
#include "../ParagraphPiece/ParagraphPiece.h"
#include "../Defines.h"

using namespace std;

class TextProcessor
{
private:
    /* data */
public:
    TextProcessor();
    ~TextProcessor();

    string processWordAsFantasy(string);
    string processWordAsSF(string);
    bool isValidWord(string);
    ParagraphPiece processPiece(ParagraphPiece);
    ParagraphPiece processAsHorror(ParagraphPiece);
    ParagraphPiece processAsSF(ParagraphPiece);
    ParagraphPiece processAsFantasy(ParagraphPiece);
    ParagraphPiece processAsComedy(ParagraphPiece);
};


