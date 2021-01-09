#pragma once

#include <vector>
#include <queue>
#include "../ParagraphPiece/ParagraphPiece.h"

using namespace std;

class ConcurrentMemory
{
public:
    ConcurrentMemory(int);
    ~ConcurrentMemory();

    vector<queue<ParagraphPiece *>> queues;
    vector<bool> execution_ended;
    int threads_number;

    void pushPieceToThread(int, ParagraphPiece *);
    ParagraphPiece * getNextPieceForThread(int);
    bool isThreadQueueEmpty(int);
    void removePieceFromThread(int);
    int getNumberOfPiecesFromThread(int);
};
