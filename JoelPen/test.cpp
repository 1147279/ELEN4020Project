#include <iostream>
#include <fstream>
#include "mpi.h"
#include <string>
#include <bits/stdc++.h>
#include <vector>
using namespace std;


int main(int argc, char *argv[]) {


  int Npes, myrank, source, dest;
  int tag=0;
  int count = 0;
  int bufferSize=100;
  char sentMsg [100];
  char recvMsg [100];
  MPI_Status status;
  MPI_Init (&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &Npes);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  string tmp = "Hello World!";
  string rcv;

  if (myrank == 0) {

    strcpy(sentMsg, tmp.c_str());

    for (dest=1; dest<Npes; dest++){
      MPI_Send(sentMsg, bufferSize, MPI_CHAR, dest, tag, MPI_COMM_WORLD );
    }

    int endDest;
    char endMsg[] = "Done Reading!";

    for (int i=1 ; i < Npes ; i++) {
      endDest = i;
      MPI_Send(endMsg, bufferSize, MPI_CHAR, endDest, tag, MPI_COMM_WORLD );
    }
  }

  else{
    //vector<string> hashTable_A;

    while (recvMsg != string("Done Reading!")) {
			MPI_Recv(recvMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD,&status);
			rcv =  string(recvMsg);
			//hashTable_A.push_back(rcv);

			cout << "I am rank: "<< myrank <<" I've received: " << /*hashTable_A.at(count)*/ rcv <<" at count = "<< count <<endl;
			count++;

		}
    cout<<"Hello"<<endl;
		//cout<<"ENDDDDDDDDD!!!!"<<hashTable_A.size()<<endl;
	}

  MPI_Finalize();
  return 0;
}
/*
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d"
           " out of %d processors\n",
           processor_name, world_rank, world_size);

    // Finalize the MPI environment.
    MPI_Finalize();
}
*/
