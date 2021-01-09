#include <iostream>
#include "utils/TextProcessor/TextProcessor.h"
#include "utils/ParagraphPiece/ParagraphPiece.h"
#include "utils/ParagraphTools/ParagraphTool.h"
#include "utils/ConcurrentMemory/ConcurrentMemory.h"

using namespace std;


int main(int argc, char** argv) {
    TextProcessor tp;
    ParagraphPiece * p1 = new ParagraphPiece(1, 1, 3, "Salut sunt Andy, toata lumea ma cunoaste bai bro !\n Si ce daca rad, si ce daca plang a ?");
    ParagraphPiece * p2 = new ParagraphPiece(1, 1, 2, "Hello sanky, montana mistere");
    ParagraphPiece * p3 = new ParagraphPiece(1, 1, 1, "Au innebunit salcamii !");
    ConcurrentMemory * cm = new ConcurrentMemory(3);
    cm->pushPieceToThread(1, p1);
    cm->pushPieceToThread(1, p2);
    cm->pushPieceToThread(2, p3);

    cout << cm->getNumberOfPiecesFromThread(0) << endl;
    cout << cm->getNumberOfPiecesFromThread(1) << endl;
    cout << cm->getNumberOfPiecesFromThread(2) << endl;
    cout << endl;

    cout << cm->getNextPieceForThread(1)->getLines() << endl; cm->removePieceFromThread(1);
    cout << cm->getNextPieceForThread(1)->getLines() << endl;
    cout << cm->getNextPieceForThread(2)->getLines() << endl;
    cout << endl;

    ParagraphPiece * test = cm->getNextPieceForThread(2);
    tp.processPiece(*test);
    cout << test->getLines() << endl;

    return 0;
}