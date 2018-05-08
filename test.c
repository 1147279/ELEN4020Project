#include "mpi.h"
#include <stdio.h>
#include <string.h>
int main( argc, argv )
int argc;
char **argv;
{
	int Npes,myrank;
	int source, dest;
	char msg[100];
	char msg2[100];
	int tag = 0;
	MPI_Status status;
	MPI_Init( &argc, &argv );
	MPI_Comm_size(MPI_COMM_WORLD, &Npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	if (myrank !=0)
	{
		sprintf(msg, "Greetings from %d", myrank);
		dest = 0;
		MPI_Send(msg, strlen(msg)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	}else
	{
		for (source = 1; source < Npes ; source++)
		{
			MPI_Recv(msg2, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD,&status);
			printf("%s\n", msg2);		
		}	
	}

	MPI_Finalize();
	return 0;
}
