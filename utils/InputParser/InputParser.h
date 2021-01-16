#pragma once

#include <iostream>
#include <string>
#include "../ParagraphPiece/ParagraphPiece.h"
#include "../Defines.h"

using namespace std;

class InputParser
{
private:
    string filename;
    int genreType;

public:
    InputParser(string filename, int genreType);
    ~InputParser();

    static int getGenreByType(string);
    void parseInput();

    void send(ParagraphPiece p) {
        cout << "{ p" << p.getIdParagraph() << "b" << p.getId() << endl << p.getLines() << endl << "}" << endl;
        cout << endl << endl;
    }
};

