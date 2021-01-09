#include <iostream>
#include "utils/TextProcessor/TextProcessor.h"
#include "utils/ParagraphPiece/ParagraphPiece.h"

using namespace std;


int main(int argc, char** argv) {
    TextProcessor tp;
    ParagraphPiece pp(1, 1, 2, "Saalut sunt Andy, toata lumea ma cunoaste bai bro !\n Si ce daca rad, si ce daca plang a ?");
    pp = tp.processPiece(pp);
    cout << pp.getLines() << endl;

    return 0;
}