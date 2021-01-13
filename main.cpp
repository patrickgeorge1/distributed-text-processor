#include <iostream>
#include <thread>
#include "utils/TextProcessor/TextProcessor.h"
#include "utils/ParagraphPiece/ParagraphPiece.h"
#include "utils/ParagraphTools/ParagraphTool.h"
#include "utils/ConcurrentMemory/ConcurrentMemory.h"
#include "utils/Defines.h"
#include <unistd.h>


using namespace std;

static ConcurrentMemory * cm;
static TextProcessor * tp = new TextProcessor();

void wokerDo(int id) {

    while (true)
    {
        ParagraphPiece * p = cm->getTask();
        if (p->getGenre() == GENRE_STOP) break;

        // worker job
        tp->processPiece(*p);
        cm->markCompletedTask(p);
    }
    pthread_exit(NULL);
}


void mainDo(int id) {
    for (int i = 0; i < 100; i++)
    {
        string ceva = "task" + to_string(i);
        ParagraphPiece* p = new ParagraphPiece(i, 1, i % 3, ceva);
        cm->addTask(p);
    }
    cm->sendEndRequestToSecondartTasks();
    sleep(3);

    cm->getProcessedTasks();
    pthread_exit(NULL);
}


int main(int argc, char** argv) {  
    cm = new ConcurrentMemory(3);
    
    thread main(mainDo, 0);
    thread worker1(wokerDo, 1);
    thread worker2(wokerDo, 2);
    thread worker3(wokerDo, 3);

    main.join();
    worker1.join();
    worker2.join();
    worker3.join();

    cout << "The end." << endl;
    return 0;
}