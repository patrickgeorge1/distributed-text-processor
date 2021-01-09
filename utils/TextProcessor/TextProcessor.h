#pragma once

#include <iostream>
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

    ParagraphPiece processPiece(ParagraphPiece);
    ParagraphPiece processAsHorror(ParagraphPiece);
    ParagraphPiece processAsSF(ParagraphPiece);
    ParagraphPiece processAsFantasy(ParagraphPiece);
    ParagraphPiece processAsComedy(ParagraphPiece);
};


