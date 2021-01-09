#include "ConcurrentMemory.h"


ConcurrentMemory::ConcurrentMemory(int number)
{
    this->threads_number = number;
    for (int i = 0; i < number; i++) {
        queues.push_back(queue<ParagraphPiece *>());
        execution_ended.push_back(false);
    }

}

ConcurrentMemory::~ConcurrentMemory()
{
}

void ConcurrentMemory::pushPieceToThread(int thread_id, ParagraphPiece * piece) {
    this->queues[thread_id].push(piece);
}

ParagraphPiece * ConcurrentMemory::getNextPieceForThread(int thread_id) {
    return this->queues[thread_id].front();
}

bool ConcurrentMemory::isThreadQueueEmpty(int thread_id) {
    return this->queues[thread_id].empty();
}

void ConcurrentMemory::removePieceFromThread(int thread_id) {
    this->queues[thread_id].pop();
}

int ConcurrentMemory::getNumberOfPiecesFromThread(int thread_id) {
    return this->queues[thread_id].size();
}




