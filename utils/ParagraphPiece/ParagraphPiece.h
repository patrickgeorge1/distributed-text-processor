#pragma once

#include <string>

using namespace std;

class ParagraphPiece
{
private:
    string lines;
    int genre;
    int id;
    int id_paragraph;

public:
    ParagraphPiece(int, int, int, string);
    ParagraphPiece();
    ~ParagraphPiece();

    int getGenre();
    string getLines();
    int getId();
    int getIdParagraph();

    void setGenre(int);
    void setId(int);
    void setIdParagraph(int);
    void setLines(string);
};
