#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"
int NumofProc = 26;

int hashGen(char key) {
	if (key == 'A')
	{
		return 0;
	}
	if (key == 'B')
	{
		return 1;
	}
	if (key == 'C')
	{
		return 2;
	}
	if (key == 'D')
	{
		return 3;
	}
	if (key == 'E')
	{
		return 4;
	}
	if (key == 'F')
	{
		return 5;
	}
	if (key == 'G')
	{
		return 6;
	}
	if (key == 'H')
	{
		return 7;
	}
	if (key == 'I')
	{
		return 8;
	}
	if (key == 'J')
	{
		return 9;
	}
	if (key == 'K')
	{
		return 10;
	}
	if (key == 'L')
	{
		return 11;
	}
	if (key == 'M')
	{
		return 12;
	}
	if (key == 'N')
	{
		return 13;
	}
	if (key == 'O')
	{
		return 14;
	}
	if (key == 'P')
	{
		return 15;
	}
	if (key == 'Q')
	{
		return 16;
	}
	if (key == 'R')
	{
		return 17;
	}
	if (key == 'S')
	{
		return 18;
	}
	if (key == 'T')
	{
		return 19;
	}
	if (key == 'U')
	{
		return 20;
	}
	if (key == 'V')
	{
		return 21;
	}
	if (key == 'W')
	{
		return 22;
	}
	if (key == 'X')
	{
		return 23;
	}
	if (key == 'Y')
	{
		return 24;
	}
	if (key == 'Z')
	{
		return 25;
	}
}

int main( argc, argv )
int argc;
char **argv;
{


	// MPI STuff
	int Npes,myrank;
	int source, dest;
	char msg[10];
	char msg2[10];
	int tag = 0;
	MPI_Status status;
	MPI_Init( &argc, &argv );
	MPI_Comm_size(MPI_COMM_WORLD, &Npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	//
	

	char mybucket[100];
	FILE *B;
	B = fopen("Table2.txt","r");
	

	FILE *A;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
 
	A = fopen("Table1.txt", "r");
	
 	int bucket;
	
		if (myrank ==0)
		{
			while ((read = getline(&line, &len, A)) != -1) {
			//printf("%c \n", read);
			//printf("%c\n", line[0]);
			bucket = hashGen(line[0]);
			//printf("%d\n", bucket);
								

			sprintf(msg, "%c|%c\n", line[0], line[2]);
			dest = bucket;
			MPI_Send(msg, strlen(msg)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
			}	
		}else
		{
			MPI_Recv(msg2, 10, MPI_CHAR, 0, tag, MPI_COMM_WORLD,&status);
			printf("From rank %d =     %s\n",myrank, msg2);		
			//mybucket[strlen(mybucket)] = msg2;
		}

	
 	
	//mybucket[strlen(mybucket)] = msg2;

	/*if (myrank !=0)
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
	*/
	MPI_Finalize();
	free(line);
	fclose(A);
	









	// Hash But not actual hash yet
	
	


	
}



