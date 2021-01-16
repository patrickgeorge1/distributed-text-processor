#include <iostream>
#include <thread>
#include "utils/TextProcessor/TextProcessor.h"
#include "utils/ParagraphPiece/ParagraphPiece.h"
#include "utils/ParagraphTools/ParagraphTool.h"
#include "utils/ConcurrentMemory/ConcurrentMemory.h"
#include "utils/InputParser/InputParser.h"
#include "utils/Defines.h"
#include <unistd.h>
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define MASTER_NODE 0

using namespace std;

static ConcurrentMemory * cm;
static TextProcessor * tp = new TextProcessor();
static int P;
static string fileName;
static pthread_barrier_t masterBarrier;


void sendParagraphPieceToWoker(ParagraphPiece *p, int type) {
    int random_num = 10;
    MPI_Send(&random_num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    // TODO fix this
}

// worker - secondary
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

// worker - main
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


void masterParserDo(int type) {
    cout << type << endl;

    // read, send
    InputParser ip(fileName, type);
    int paragraphNo = ip.parseInput();

    // TODO while(paragraphNo > 0)  recv, assemble in map
    pthread_barrier_wait(&masterBarrier);

    if (type == GENRE_HORROR)
    {
        // TODO write to file
    }
}


// master node routine
void MASTER_JOB() {
    vector<thread> parsers;
    for (int i = 0; i < 4; i++)
    {
        parsers.push_back(thread(masterParserDo, i));
    }
    
    // start 4 threads, read, send, receive, write to file
    for (int i = 0; i < 4; i++)
    {
        parsers.at(i).join();
    }

    cout << " MASTER: The end." << endl;
}

// worker node routine
void WORKER_JOB(int type) {
    cout << " WORKER" << type << ": The end." << endl;
}

int main(int argc, char** argv) {  
    int provided;
    int  numtasks, rank;

    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    fileName = argv[1];
    P = atoi(argv[2]);

    // barrier init
	if (pthread_barrier_init (&masterBarrier, NULL, 4) != 0)
    {
        printf("\n barrier init failed\n");
        return 1;
    }

    if (rank == MASTER_NODE)
    {
        MASTER_JOB();
    } else {
        WORKER_JOB(rank % 4);
    }
    
    pthread_barrier_destroy(&masterBarrier);

    MPI_Finalize();
}