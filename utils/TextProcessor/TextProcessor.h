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

    void processPiece(ParagraphPiece &);
    void processAsHorror(ParagraphPiece &);
    void processAsSF(ParagraphPiece &);
    void processAsFantasy(ParagraphPiece &);
    void processAsComedy(ParagraphPiece &);
};


