#include <stdio.h>		//for printf and scanf
#include <stdlib.h>
#include <string.h>
//#define _USE_C99_MATH
#include <stdbool.h>

int inputToASCII(char character) {
	int asciiNumber=(int) character;

	return asciiNumber;
};

int hashGen(char* key) {
	int hashNumber=0;

	for(int i=0; i<(int) strlen(key); i++) {
		hashNumber += inputToASCII(key[i]);
	}

	int modHashNumber=(hashNumber%7) +1; 												//Mod by 7, to get a number between 0 and 6; add 1, to get between 1 and 7 - this will dictate which numbers go to which processors.
	return modHashNumber;
};

bool isKeyEqual(char* key_1, char* key_2) {
	int ascii_key_1=hashGen(key_1);
	int ascii_key_2=hashGen(key_2);

	if(ascii_key_1 == ascii_key_2){
		printf("\nEQUAL:\n%s:%d\n%s:%d\n", key_1, ascii_key_1, key_2, ascii_key_2);
		//printf("strcmp says: %d\n", (int)strcmp(key_1, key_2));											//COMMENTS? Is strcmp all that is necessary?
		return true;
	}

	else{
		printf("\nNOT EQUAL:\n%s:%d\n%s:%d\n", key_1, ascii_key_1, key_2, ascii_key_2);
		//printf("strcmp says: %d\n", (int)strcmp(key_1, key_2));
		return false;
	}

};

int main( argc, argv )
int argc;
char **argv;
{
	/*char joel='j';
	printf("%d, %d\n", inputToASCII(joel), (int)'o');

	char Joel='J';
	printf("%d, %d\n", inputToASCII(Joel), (int)'O');

	int number= strcmp("jo","JO");
	printf("%d\n",number );
*/
	char bob[]="Yebo";
	char* bobPtr=bob;
	/*size_t size=strlen(bobPtr);
	printf("%d is the length of Yebo\n", (int)size);

	int bobASCII=hashGen(bobPtr);
	printf("%d is the size of Bob in ASCII\n", bobASCII); //399
*/
	char alpha[]="ABCDEFGHIJKLM";
	char* alphaPtr=alpha;
/*
	int alphaASCII=hashGen(alphaPtr);
	printf("%d is the size of alpha in ASCII", alphaASCII); //923
*/

char alpha2[]="ABCDEFGHIJKLM";
char* alphaPtr2=alpha2;

bool Result= isKeyEqual(bobPtr, alphaPtr);
bool Result2= isKeyEqual(alphaPtr,alphaPtr2);




	char Joel[]="JoeL";
	char* JoelPtr=Joel;

	char Joel2[]="Joel";
	char* JoelPtr2=Joel2;

	bool Result3= isKeyEqual(JoelPtr, JoelPtr2);


	char number1[]="123456";
	char* number1Ptr=number1;

	char number2[]="123456";
	char* number2Ptr=number2;

	bool Result4= isKeyEqual(number1Ptr, number2Ptr);


	char number3[]="123956";
	char* number3Ptr=number3;

	bool Result5= isKeyEqual(number1Ptr, number3Ptr);


	/*
	char* sentence;

	sentence=(char*) malloc (50);


	free(sentence);
*/

	return 0;
}
/*
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

	MPI_Finalize();
	free(line);
	fclose(A);
*/
