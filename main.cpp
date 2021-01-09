#include <iostream>
#include "utils/TextProcessor/TextProcessor.h"
#include "utils/ParagraphPiece/ParagraphPiece.h"
#include "utils/ParagraphTools/ParagraphTool.h"
#include "utils/ConcurrentMemory/ConcurrentMemory.h"

using namespace std;


int main(int argc, char** argv) {
    TextProcessor tp;
    ParagraphPiece * pp = new ParagraphPiece(1, 1, 3, "Salut sunt Andy, toata lumea ma cunoaste bai bro !\n Si ce daca rad, si ce daca plang a ?");
    ConcurrentMemory * cm = new ConcurrentMemory(3);
    cm->pushPieceToThread(1, pp);
    cm->pushPieceToThread(1, pp);
    cm->pushPieceToThread(2, pp);

    cout << cm->getNumberOfPiecesFromThread(0) << endl;
    cout << cm->getNumberOfPiecesFromThread(1) << endl;
    cout << cm->getNumberOfPiecesFromThread(2) << endl;

    cout << cm->getNextPieceForThread(1)->getLines();
    

    return 0;
}