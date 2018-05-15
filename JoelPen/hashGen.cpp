#include <iostream>
#include <string>

using namespace std;

int hashGen(string& key) {
	int hashNumber=0;

	for(int i=0; i < key.size(); i++) {
		hashNumber += static_cast<int>(key[i]);
	}

	//int modHashNumber=(hashNumber%7) +1; 												//Mod by 7, to get a number between 0 and 6; add 1, to get between 1 and 7 - this will dictate which numbers go to which processors.
	return hashNumber;
};



int main (){

  string bob="Yebo";
  cout<<"bob has a HASH value of: "<<hashGen(bob)<<endl;

  string alpha="ABCDEFGHIJKLM";
  cout<<"alpha has a HASH value of: "<<hashGen(alpha)<<endl;

  string numbers="0123456789";
  cout<<"numbers has a HASH value of: "<<hashGen(numbers)<<endl;

  return 0;
}
