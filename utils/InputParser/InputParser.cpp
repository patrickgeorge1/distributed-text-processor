#include <fstream>
#include "InputParser.h"

InputParser::InputParser(string fn, int type)
{
    this->filename = fn;
    this->genreType = type;
}

InputParser::~InputParser()
{
}


int InputParser::getGenreByType(string type) {
    if (type == GENRE_TYPE_HORROR) return GENRE_HORROR;
    if (type == GENRE_TYPE_SF) return GENRE_SF;
    if (type == GENRE_TYPE_COMEDY) return GENRE_COMEDY;
    if (type == GENRE_TYPE_FANTASY) return GENRE_FANTASY;
    return GENRE_NOT_FOUND;
}

int InputParser::parseInput() {
    ifstream File(this->filename);
    string line;

    int paragraph_no = 0;
    int paragraph_piece_n0 = 0;
    int genre = GENRE_UNDIFINED;
    string lines = "";
    int counter = 1;
    bool isOkToRead = true;

    ParagraphPiece p;

    while (getline(File, line)) {
        // new paragraph, check if his type is matching
        if (genre == GENRE_UNDIFINED && isOkToRead)
        {
            genre = getGenreByType(line);
            isOkToRead = (genre == this->genreType) ? true : false;
        } else {
            // same paragraph \n
            if (line != "") {
                if (isOkToRead)
                {
                    // append line to current piece
                    if (counter <= 20)
                    {
                        lines += line;
                        lines += "\n";
                        counter++;
                    } 
                    // start new piece
                    else  {
                        p = ParagraphPiece(paragraph_piece_n0, paragraph_no, genre, lines);
                        // TODO send() paragraph complete piece
                        send(p);

                        paragraph_piece_n0++;
                        lines = "";
                        counter = 1;
                    }
                }
            }
            // new paragraph
            else {
                if (lines != "") {
                    p = ParagraphPiece(paragraph_piece_n0, paragraph_no, genre, lines);
                    // TODO send() paragraph incomplete piece
                    send(p);
                }
                genre = GENRE_UNDIFINED;
                paragraph_piece_n0 = 0;
                paragraph_no++;
                lines = "";
                counter = 1;
                isOkToRead = true;
            }
        }
    }

    if (lines != "") {
        p = ParagraphPiece(paragraph_piece_n0, paragraph_no, genre, lines);
        // TODO send() paragraph remaining incomplete piece
        send(p);
    }

    File.close();
    return paragraph_no;
}

