#include "TextProcessor.h"

TextProcessor::TextProcessor()
{
}

TextProcessor::~TextProcessor()
{
}



ParagraphPiece TextProcessor::processAsHorror(ParagraphPiece p) {
    string lines = p.getLines();
    string processed_lines = "";
    string consonants = "QZWSXDCRFVTGBYHNJMKLPqzwsxdcrfvtgbyhnjmklp";


    for (char const &c: lines) {
        if (consonants.find(c) == string::npos)
        {
            processed_lines += c;
        } else {
            processed_lines += c;
            processed_lines += tolower(c);
        }
    }
    p.setLines(processed_lines);
    return p;
}

ParagraphPiece TextProcessor::processAsSF(ParagraphPiece p){
    return p;
}

ParagraphPiece TextProcessor::processAsFantasy(ParagraphPiece p){
    return p;  
}

ParagraphPiece TextProcessor::processAsComedy(ParagraphPiece p){
    return p;   
}

ParagraphPiece TextProcessor::processPiece(ParagraphPiece p) {
    switch (p.getGenre())
    {
    case GENRE_HORROR:
        return processAsHorror(p);
        break;

    case GENRE_SF:
        return processAsSF(p);
        break;

    case GENRE_COMEDY:
        return processAsComedy(p);
        break;

    case GENRE_FANTASY:
        return processAsFantasy(p);
        break;
    
    default:
        cout << "invalid genre" << endl;
        exit(1);
        break;
    }
}