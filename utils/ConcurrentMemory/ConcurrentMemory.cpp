#include "ConcurrentMemory.h"


ConcurrentMemory::ConcurrentMemory(int number)
{
    this->threads_number = number;
    // this->execution_ended = false;
    // for (int i = 0; i < number; i++) {
    //     queues.push_back(queue<ParagraphPiece *>());
    // }


}

ConcurrentMemory::~ConcurrentMemory()
{
}

// add task to thread pool
void ConcurrentMemory::addTask(ParagraphPiece * p) {
    unique_lock<mutex> ul(m);
    taskPool.push(p);
    if (piecesNumber.find(p->getIdParagraph()) == piecesNumber.end())
    {
        piecesNumber[p->getIdParagraph()] = 0;
    } 
    piecesNumber[p->getIdParagraph()]++;

    ul.unlock();
    cv.notify_one();
}

// pop and get task from thread pool
ParagraphPiece * ConcurrentMemory::getTask() {
    unique_lock<mutex> ul(m);
    cv.wait(ul, [&] { return (taskPool.size() != 0); });
    ParagraphPiece * p = taskPool.front();
    taskPool.pop();
    return p;
}

/* after a task was processed, decrese paragraph batch number and add processed
      paragraph batch to map to collect later     */
void ConcurrentMemory::markCompletedTask(ParagraphPiece* p) {
    unique_lock<mutex> ul(m);
    int paragraph = p->getIdParagraph();
    if (paragraphPieces.find(paragraph) == paragraphPieces.end())
    {
        paragraphPieces[paragraph] = map<int, ParagraphPiece *>();
    }
    paragraphPieces[paragraph][p->getId()] = p;
    piecesNumber[paragraph]--;
}

// send task that will end the worker threads
void ConcurrentMemory::sendEndRequestToSecondartTasks() {
    for (int i = 0; i < threads_number; i++)
    {
        addTask(new ParagraphPiece(-1, -1, -1, ""));
    }
    unique_lock<mutex> ul(m);
    piecesNumber.erase(-1);
}

// get and remove the most recently finished paragraph indices
queue<int> ConcurrentMemory::getProcessedTasks() {
    unique_lock<mutex> ul(m);
    queue<int> finishedParagraphs;
    queue<int> toBeDeleted;
    for(std::map<int,int>::iterator iter = piecesNumber.begin(); iter != piecesNumber.end(); ++iter)
    {
        int k =  iter->first;
        int v = iter->second;
        if (v == 0) {
            finishedParagraphs.push(k);
            toBeDeleted.push(k);
        }
    }
    while(toBeDeleted.size() != 0) {
        piecesNumber.erase(toBeDeleted.front());
        toBeDeleted.pop(); 
    }
    return finishedParagraphs;
}

bool ConcurrentMemory::allTasksWereProcessed() {
    return (piecesNumber.size() == 0);
}


// void ConcurrentMemory::pushPieceToThread(int thread_id, ParagraphPiece * piece) {
//     this->queues[thread_id].push(piece);
// }

// ParagraphPiece * ConcurrentMemory::getNextPieceForThread(int thread_id) {
//     return this->queues[thread_id].front();
// }

// bool ConcurrentMemory::isThreadQueueEmpty(int thread_id) {
//     return this->queues[thread_id].empty();
// }

// void ConcurrentMemory::removePieceFromThread(int thread_id) {
//     this->queues[thread_id].pop();
// }

// int ConcurrentMemory::getNumberOfPiecesFromThread(int thread_id) {
//     return this->queues[thread_id].size();
// }

// void ConcurrentMemory::markProcessedPiecesAsReady(ParagraphPiece * p) {
//     paragraphInExecution[p->getId()] = p;
// }

// void ConcurrentMemory::clearMarkedProcessedPieces(){
//     paragraphInExecution.clear();
// }




