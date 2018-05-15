#include <iostream>
#include <fstream>
#include "mpi.h"
#include <string>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

const char delimiter = '|';
//#include <functions.h>

//---------------------------------------------------------------------------------------------------------------------------------------
int hashGen(string& key) {
	int hashNumber=0;

	for(int i=0; i < key.size(); i++) {
		hashNumber += static_cast<int>(key[i]);
	}

	//int modHashNumber=(hashNumber%7) +1; 												//Mod by 7, to get a number between 0 and 6; add 1, to get between 1 and 7 - this will dictate which numbers go to which processors.
	return hashNumber;
};
//-----------------------------------------------------------------------------------------------------------------------------------------
string keyExtraction(const char& delimiter, string& kv_pair){       //kv_pair in the form of 'Key delimiter Value'

  string key= kv_pair.substr(0, kv_pair.find(delimiter));     //Key is from index position 0, up until delimiter's position.

  return key;
};
//-----------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------------------
 string hashJoin(string& commonKey, string& kv_A, string& kv_B) {

	 int value_A_start = kv_A.find(delimiter) + 1;			 //Position of Value begins one position after delimiter
	 int value_A_length = kv_A.length() - value_A_start;
	 string value_A = kv_A.substr(value_A_start, value_A_length);

	 int value_B_start = kv_B.find(delimiter) + 1;			 //Position of Value begins one position after delimiter
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
	int count = 0;
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
  if (myrank == 0) {                                          //Master process, reading in data from Table A and distributing to processes according to hash.

    ifstream input_A;
    input_A.open("Table1.txt", ifstream::in);

    string kv_pair;

    while (input_A >> kv_pair) {
      string key_A = keyExtraction(delimiter, kv_pair);      //Extracting the key from the key-value pair read in from Table 1.
      dest = ( hashGen(key_A)%(Npes -1) )  + 1;              //Determining which slave process to pass the key-value pair to.

      // cout << dest << endl;

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

	else{																												//Slave process, receiving process.
		MPI_Recv(recvMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD,&status);

		while (string (recvMsg) != string("Done Reading!")) {
			tmp =  string(recvMsg);
			hashTable_A.push_back(tmp);

			//cout << "I am rank: "<< myrank <<" I've received: " << hashTable_A.at(count) <<" at count = "<< count <<endl;
			count++;
			MPI_Recv(recvMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD,&status);
		}
	}
	/*for (int i = 0; i < hashTable_A.size() ; i++) {
			cout << "Final am rank: "<< myrank << hashTable_A.at(i)<< endl;
	}*/

	cout<< "Transfer of Table A complete." <<endl;
//____________________________________________________________________________//



//------------------------- Transfer Table B and Join ------------------------//
	/*MPI_File outFile;
	MPI_Offset offset=0;
	char buff[100];
	MPI_File_open(MPI_COMM_WORLD, "Table3.txt", MPI_MODE_RDWR | MPI_MODE_CREATE, MPI_INFO_NULL, &outFile);
	*/



	if (myrank == 0) {                                            //Master process, reading in data from Table B and distributing to processes according to hash.

		ifstream input_B;
		input_B.open("Table2.txt", ifstream::in);

		string kv_pair_B;
		string key_B;

		while (input_B >> kv_pair_B) {
			key_B = keyExtraction(delimiter, kv_pair_B);       //Extracting the key from the key-value pair read in from Table 1.
			dest = ( hashGen(key_B)%(Npes -1) )  + 1;                 //Determining which slave process to pass the key-value pair to.

			//cout << dest << endl;

			strcpy(sentMsg, kv_pair_B.c_str());
			MPI_Send(sentMsg, bufferSize, MPI_CHAR, dest, tag, MPI_COMM_WORLD );

			//cout <<"snt: " << sentMsg << endl;
		}

		int endDest;																								//Informing slave processes that Table B has completed sending.
		char endMsg[] = "Done Reading B!";

		for (int i=1 ; i < Npes ; i++) {
			endDest = i;
			MPI_Send(endMsg, bufferSize, MPI_CHAR, endDest, tag, MPI_COMM_WORLD );
			//cout << endMsg << "Node: "<< i<< endl;
		}
		input_B.close();
	}

	else{
		MPI_Recv(recvMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD,&status);
		cout<<"first one received: "<<recvMsg<<endl;
		count = 0;
		string key_A;
		string key_B;
		string join_kv;
		//MPI_File_open(MPI_COMM_WORLD, "Table3", MPI_MODE_RDWR | MPI_MODE_CREATE, MPI_INFO_NULL, &outFile);

		while (string(recvMsg) != string("Done Reading B!")) {
			//cout << "Done rec" << endl;
			tmp =  string(recvMsg);

			key_B= keyExtraction(delimiter, tmp);


			for (int i=0; i < hashTable_A.size(); i++) {
				key_A= keyExtraction(delimiter, hashTable_A.at(i));

				if (key_A == key_B) {
					join_kv = hashJoin(key_A, hashTable_A.at(i), tmp);

					//sending back to master to write
					strcpy(sentMsg, join_kv.c_str());
					MPI_Send(sentMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD );
				}

			}

			//cout << "I am rank: "<< myrank <<" I've received: " << hashTable_A.at(count) <<" at count = "<< count <<endl;

			MPI_Recv(recvMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD,&status);

		}
		char endMsg[] = "Done Joining!";
		MPI_Send(endMsg, bufferSize, MPI_CHAR, 0, tag, MPI_COMM_WORLD );
	}
	//MPI_File_close(&outFile);

	if (myrank == 0){

		ofstream outFile("Table3.txt",ofstream::out | ofstream::app);

		for (int i = 1 ; i< Npes ;i++){
			MPI_Recv(recvMsg, bufferSize, MPI_CHAR, i, tag, MPI_COMM_WORLD,&status);
			while (string(recvMsg) != string("Done Joining!")){
				outFile << string(recvMsg) << endl;
				MPI_Recv(recvMsg, bufferSize, MPI_CHAR, i, tag, MPI_COMM_WORLD,&status);
			}
		}
		outFile.close();
	}


	MPI_Finalize();

  return 0;
}
