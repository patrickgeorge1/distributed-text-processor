#pragma once

#include <vector>
#include <queue>
#include <map>
#include <mutex>
#include <condition_variable>
#include "../ParagraphPiece/ParagraphPiece.h"
#include "../Defines.h"

using namespace std;

class ConcurrentMemory
{
public:
    ConcurrentMemory(int);
    ~ConcurrentMemory();

    int threads_number;
    mutex m;
    condition_variable cv;

    queue<ParagraphPiece *> taskPool;
    map<int, map<int, ParagraphPiece *>> paragraphPieces;
    map<int, int> piecesNumber;

    void addTask(ParagraphPiece *);
    ParagraphPiece * getTask();
    void markCompletedTask(ParagraphPiece *);
    void sendEndRequestToSecondartTasks();
    bool allTasksWereProcessed();
    queue<int> getProcessedTasks();

    // vector<queue<ParagraphPiece *>> queues;
    // bool execution_ended;
    // int threads_number;
    // map<int, ParagraphPiece *> paragraphInExecution;

    // void pushPieceToThread(int, ParagraphPiece *);
    // ParagraphPiece * getNextPieceForThread(int);
    // bool isThreadQueueEmpty(int);
    // void removePieceFromThread(int);
    // int getNumberOfPiecesFromThread(int);

    // void markProcessedPiecesAsReady(ParagraphPiece *);
    // void clearMarkedProcessedPieces();
};
