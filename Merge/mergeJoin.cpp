#include <omp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "customer.h"
#include "cities.h"
#include "joinedTable.h"
using namespace std;

void joinTable(vector<customer>& vec1, vector<cities>& vec2, vector<joinedTable>& vec3, int index);
int extractKey(string myStr);
string extractValue(string myStr);


int main (int argc, char *argv[]) 
{
	string name;
	string myStr;
	int cityID;
	
	vector<customer> customerList;
	customer person;
	//open file textA.txt
	ifstream dataFile;
	dataFile.open("Table1_1.txt");
	int listSize = customerList.size();
	bool isFound = false;
	int indexFound = 0;
	 
	while(dataFile >> myStr)
	{
		cityID = extractKey(myStr);
		name = extractValue(myStr);
		listSize = customerList.size();
		
		if(listSize == 0)
		{
			person.addName(name);
			person.addCityID(cityID);
			customerList.push_back(person);
			person.resetAttributes();
		}else
		{
			for(int i = 0; i < listSize && isFound == false; i++)
			{
				if(customerList.at(i).isFoundID(cityID) == true)
				{
					isFound = true;
					indexFound = i;
				}
			}
		}
		
		
		
		if(isFound == true && listSize >= 1)
		{
			customerList[indexFound].addName(name);
			isFound = false;
		}
		else if(isFound == false && listSize >= 1)
		{
			person.resetAttributes();
			person.addName(name);
			person.addCityID(cityID);	
			customerList.push_back(person);
			person.resetAttributes();
		}
	}
	
	dataFile.close();
	
	
	/*
	for(int i = 0; i <customerList.size(); i++)
		customerList.at(i).printCustomer();*/
	
	//customerList.at(0).printCustomer();
	
	
	//open textB.txt
	ifstream dataFile2;
	dataFile2.open("Table2_1.txt");
	
	cities city;
	vector<cities> cityList;
	listSize = cityList.size();
	
	
	while(dataFile2 >> myStr)
	{
		cityID = extractKey(myStr);
		name = extractValue(myStr);
		cout << name << "  " << cityID << endl;
		listSize = cityList.size();
		
		if(listSize == 0)
		{
			city.addCityName(name);
			city.addCityID(cityID);
			cityList.push_back(city);
			city.resetAttributes();
		}else
		{
			for(int i = 0; i < listSize && isFound == false; i++)
			{
				if(cityList.at(i).isFoundID(cityID) == true)
				{
					isFound = true;
					indexFound = i;
				}
			}
		}
		
		
		
		if(isFound == true && listSize >= 1)
		{
			cityList[indexFound].addCityName(name);
			isFound = false;
		}
		else if(isFound == false && listSize >= 1)
		{
			city.resetAttributes();
			city.addCityName(name);
			city.addCityID(cityID);	
			cityList.push_back(city);
			city.resetAttributes();
		}
		
		
		
	}
	
	dataFile2.close();
	/*
	for(int i = 0; i <cityList.size(); i++)
		cityList.at(i).printCity();*/
		
	for(int i = 0; i <cityList.size(); i++)
		cout << cityList.at(i).getID()<< "  "<< cityList.at(i).getNumOfElements() <<endl;
	cout << endl << endl << endl;
	for(int i = 0; i <customerList.size(); i++)
		cout << customerList.at(i).getID()<< "  "<< customerList.at(i).getNumOfElements() <<endl;
		
		
	vector <joinedTable> finalTable;
	int chunk = 10;
	
	int i = 0;
	int j = 0;
	int k = 0;
	listSize = customerList.size();
	
	
	#pragma omp parallel num_threads(8) shared(customerList, cityList, finalTable, listSize) private(i, j, k)
	{
		#pragma omp for schedule (dynamic, chunk)
		for(i = 0; i < listSize; i++)
		{
			joinTable(customerList, cityList, finalTable, i);		
		}
	}
	
	
	
	
	cout << "Size is "<< finalTable.size()<< endl;
	for(int k = 0; k < finalTable.size(); k++)
	{
		finalTable.at(k).tableOutput();
	}
}


void joinTable(vector<customer>& vec1, vector<cities>& vec2, vector<joinedTable>& vec3, int index)
{
	bool isFound = false;
	int indexFound = 0;
	int size1 = 0;
	int size2 = 0;
	int counter = 0;
	
	joinedTable temp;
	
	for(int i = 0; i < vec2.size(); i++)
	{
		if(vec1.at(index).getID() == vec2.at(i).getID())
		{
			isFound = true;
			indexFound = i;
			size1 = vec1.at(index).getNumOfElements();
			size2 = vec2.at(i).getNumOfElements();
		}
	}
	
	
	
	if(isFound == true)
	{
		for(int i = 0; i < size1; i++)
		{
			for(int j = 0; j < size2; j++)
			{
				temp.addName(vec1.at(index).getName().at(i));
				temp.addCityID(vec1.at(index).getID());
				temp.addCityName(vec2.at(indexFound).getCity().at(j));
				
				vec3.push_back(temp);
			}
		}
	}
	
	
}




int extractKey(string myStr)
{
	int indexFound = 0;
	int stringSize = myStr.size();
	
	for(int i = 0; i < stringSize; i++)
	{
		if(myStr.at(i) == '|')
			indexFound = i;
	}
	
	string name = "";
	
	for(int i = 0; i < stringSize; i++)
	{
		name += myStr.at(i);
	}
	
	
	string temp;
	
	for(int i = indexFound+1; i < stringSize; i++)
	{
		temp += myStr.at(i);
	}
	
	int ID = stoi(temp);
	return ID;
}






string extractValue(string myStr)
{
	int indexFound = 0;
	int stringSize = myStr.size();
	
	for(int i = 0; i < stringSize; i++)
	{
		if(myStr.at(i) == '|')
			indexFound = i;
	}
	
	string name = "";
	
	for(int i = 0; i < indexFound; i++)
	{
		name += myStr.at(i);
	}
	
	return name;
}

















