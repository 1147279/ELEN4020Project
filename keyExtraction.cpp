#include <iostream>
#include <string>

using namespace std;

string keyExtraction(char& delimiter, string& kv_pair){       //kv_pair in the form of 'Key delimeter Value'

  string key= kv_pair.substr(0, kv_pair.find(delimiter));     //Key is from index position 0, up until delimeter's position.

  return key;
};

int main (){

  char delimeter='|';
  string key1="Darren|95";
  string key2="Joel|48";

  cout<<"Key1 is: "<<keyExtraction(delimeter, key1)<<endl;
  cout<<"Key2 is "<<keyExtraction(delimeter, key2)<<endl;


  string key3="1147279|95";
  string key4="843463u|48";

  cout<<"Key3 is: "<<keyExtraction(delimeter, key3)<<endl;
  cout<<"Key4 is "<<keyExtraction(delimeter, key4)<<endl;

  return 0;
}
