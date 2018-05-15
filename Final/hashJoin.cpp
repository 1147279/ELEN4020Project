#include <string>
#include <iostream>

using namespace std;
const char delimiter = '|';


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
void hashJoin(string& kv_A, string& kv_B) {

	string key_A= keyExtraction(delimiter, kv_A);
	string key_B= keyExtraction(delimiter, kv_B);

	if (key_A == key_B){

		int value_A_start = kv_A.find(delimiter) + 1;			 //Position of Value begins one position after delimiter
		int value_A_length = kv_A.length() - value_A_start;
		string value_A = kv_A.substr(value_A_start, value_A_length);

		int value_B_start = kv_B.find(delimiter) + 1;			 //Position of Value begins one position after delimiter
		int value_B_length = kv_B.length() - value_B_start;
		string value_B = kv_B.substr(value_B_start, value_B_length);

//mutex initiate
		//outFile << key_A << delimiter << value_A << delimiter << value_B<<endl;
//mutex final

		cout<< key_A << delimiter << value_A << delimiter << value_B<<endl;
	}
};

//-----------------------------------------------------------------------------------------------------------------------------------------

/*


//lscpu
if rank == 0
	//Distribute Table A, onto processes
	while (not end of file){
		hash all entries

		divide entries appropriately for each process.

		aggregate all entires on each process
	}

else{
	//pass one by one entries into Table B and check on each processes
	hashJoin(string& kv_pair_1, string& kv_pair_2 ){
		if is
	}


Step 1: Distribute Table A amongst slaves (hash), and store on local instance of a vector.
Step 2: Each element of Table B is hashed, and passed to appropriate slave.
Step 3: Slave is going to hash join, by writing to File 3 (mutex).
*/

int main (){
	string kv_1="843463|658AAA856";
	string kv_2="843463|87";
	string kv_3="1147279|95";
	string kv_4="1147279|85";
	string kv_5="1168101|Land is what he wants";
	string kv_6="1168101|100";

	string key1 = keyExtraction(delimiter, kv_1);
	cout<< hashGen(key1)<<endl;

	hashJoin(kv_1, kv_2);
	hashJoin(kv_3, kv_4);
	hashJoin(kv_5, kv_6);

	hashJoin(kv_1, kv_6);
	hashJoin(kv_3, kv_5);

}
	/*

	int value_1_start = kv_1.find(delimiter) + 1;			 //Position of Value begins one position
	int value_1_length = kv_1.length() - value_1_start; //
	string value_1 = kv_1.substr(value_1_start, value_1_length);

	cout<<value_1<<endl;
}
*/
