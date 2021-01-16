#include "ParagraphPiece.h"

ParagraphPiece::ParagraphPiece(int id, int id_paragraph, int genre, string lines)
{
    this->id = id;
    this->id_paragraph = id_paragraph;
    this->genre = genre;
    this->lines = lines;
}

ParagraphPiece::ParagraphPiece() {}

ParagraphPiece::~ParagraphPiece()
{
}

int ParagraphPiece::getGenre() {
    return this->genre;
}

string ParagraphPiece::getLines() {
    return this->lines;
}

int ParagraphPiece::getId() {
    return this->id;
}

int ParagraphPiece::getIdParagraph() {
    return this->id_paragraph;
}


void ParagraphPiece::setGenre(int genre) {
    this->genre = genre;
}

void ParagraphPiece::setId(int id) {
    this->id = id;
}

void ParagraphPiece::setIdParagraph(int id_p) {
    this->id_paragraph = id_p;
}

void ParagraphPiece::setLines(string lines) {
    this->lines = lines;
}

