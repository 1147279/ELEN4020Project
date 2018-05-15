#include <iostream>
#include <fstream>
#include "mpi.h"
#include <string>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

const char delimiter = '|';																					//Can be changed dependent on style of delimiter in database
//#include <functions.h>

//-------------------------- Generate Hash of Keys ---------------------------//
int hashGen(string& key) {
	int hashNumber=0;

	for(int i=0; i < key.size(); i++) {
		hashNumber += static_cast<int>(key[i]);
	}
	return hashNumber;
};
//____________________________________________________________________________//

//------------------------ Extract Key from KV-pair --------------------------//
string keyExtraction(const char& delimiter, string& kv_pair) {      //kv_pair in the form of 'Key delimiter Value'
  string key= kv_pair.substr(0, kv_pair.find(delimiter));     			//Key is from index position 0, up until delimiter's position.
  return key;
};
//____________________________________________________________________________//

//----------------------- Determining joined KV-pair -------------------------//
 string hashJoin(string& commonKey, string& kv_A, string& kv_B) {

	 //Extracting Value A from KV_A
	 int value_A_start = kv_A.find(delimiter) + 1;
	 int value_A_length = kv_A.length() - value_A_start;
	 string value_A = kv_A.substr(value_A_start, value_A_length);

	 //Extracting Value B from KV_B
	 int value_B_start = kv_B.find(delimiter) + 1;
	 int value_B_length = kv_B.length() - value_B_start;
	 string value_B = kv_B.substr(value_B_start, value_B_length);

	 string joined_kv = commonKey + delimiter + value_A + delimiter + value_B;
	 return joined_kv;
 };
//____________________________________________________________________________//

int main(int argc, char *argv[]){

  //------------------------ MPI Variable Declaration ------------------------//
  int Npes, myrank, source, dest;
  int tag=0;
	//int count = 0;
  int bufferSize=100;
  char sentMsg [100];
  char recvMsg [100];
  MPI_Status status;

  MPI_Init (&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &Npes);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	string tmp;
	vector<string> hashTable_A;
//____________________________________________________________________________//

//---------------------- Transfer Table A amongst Nodes ----------------------//

// Timing
	double startTime = MPI_Wtime();
	double stopTime ;
	double diffTime;


  if (myrank == 0) {                                          //Master process, reading in data from Table A and distributing to processes according to hash.
    ifstream input_A;
    input_A.open("Table1.txt", ifstream::in);

    string kv_pair;

    while (input_A >> kv_pair) {
      string key_A = keyExtraction(delimiter, kv_pair);       //Extracting the key from the key-value pair read in from Table A.
      dest = ( hashGen(key_A)%(Npes -1) )  + 1;               //Determining which slave process to pass the key-value pair to.

      strcpy(sentMsg, kv_pair.c_str());
      MPI_Send(sentMsg, bufferSize, MPI_CHAR, dest, tag, MPI_COMM_WORLD );
    }

		int endDest;																							//Informing slave processes that Table A has completed sending.
		char endMsg[] = "Done Reading!";

		for (int i=1 ; i < Npes ; i++) {
			endDest = i;
			MPI_Send(endMsg, bufferSize, MPI_CHAR, endDest, tag, MPI_COMM_WORLD );
		}
		input_A.close();
  }

	else {																											//Slave process, receiving process.
		MPI_Recv(recvMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD,&status);

		while (string (recvMsg) != string("Done Reading!")) {
			tmp =  string(recvMsg);
			hashTable_A.push_back(tmp);

			//count++;
			MPI_Recv(recvMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD,&status);
		}
	}
//____________________________________________________________________________//


//------------------------- Transfer Table B and Join ------------------------//
	if (myrank == 0) {                                          //Master process, reading in data from Table B and distributing to processes according to hash.
		ifstream input_B;
		input_B.open("Table2.txt", ifstream::in);

		string kv_pair_B, key_B;

		while (input_B >> kv_pair_B) {
			key_B = keyExtraction(delimiter, kv_pair_B);            //Extracting the key from the key-value pair read in from Table B.
			dest = ( hashGen(key_B)%(Npes -1) )  + 1;               //Determining which slave process to pass the key-value pair to.

			strcpy(sentMsg, kv_pair_B.c_str());
			MPI_Send(sentMsg, bufferSize, MPI_CHAR, dest, tag, MPI_COMM_WORLD );
		}

		int endDest;																							//Informing slave processes that Table B has completed being sent.
		char endMsg[] = "Done Reading B!";

		for (int i=1 ; i < Npes ; i++) {
			endDest = i;
			MPI_Send(endMsg, bufferSize, MPI_CHAR, endDest, tag, MPI_COMM_WORLD );
		}
		input_B.close();
	}

	else {																											//Comparing KV pair from B to KV pairs of A stored in vector
		MPI_Recv(recvMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD,&status);
		string key_A, key_B, join_kv;

		while (string(recvMsg) != string("Done Reading B!")) {
			tmp =  string(recvMsg);
			key_B= keyExtraction(delimiter, tmp);

			for (int i=0; i < hashTable_A.size(); i++) {
				key_A= keyExtraction(delimiter, hashTable_A.at(i));

				if (key_A == key_B) {
					join_kv = hashJoin(key_A, hashTable_A.at(i), tmp);
					strcpy(sentMsg, join_kv.c_str());
					MPI_Send(sentMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD );  //Sending back to master to write
				}
			}

			MPI_Recv(recvMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD,&status);
		}

		char endMsg[] = "Done Joining!";
		MPI_Send(endMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD );
	}
//____________________________________________________________________________//


//------------ Master node receiving joined  and writing to file -------------//
	if (myrank == 0){
		ofstream outFile("Table3.txt",ofstream::out);

		for (int i = 1 ; i< Npes ;i++){
			MPI_Recv(recvMsg, bufferSize, MPI_CHAR, i, tag, MPI_COMM_WORLD,&status);

			while (string(recvMsg) != string("Done Joining!")){
				outFile << string(recvMsg) << endl;
				MPI_Recv(recvMsg, bufferSize, MPI_CHAR, i, tag, MPI_COMM_WORLD,&status);
			}
		}
		outFile.close();

	}
	stopTime = MPI_Wtime();
	diffTime = stopTime - startTime;
	cout <<"Rank: "<< myrank<< "		" << diffTime << endl;
	MPI_Finalize();


  return 0;
}
