#ifndef JOINEDTABLE_H
#define JOINEDTABLE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class joinedTable
{
public:
	joinedTable();
	void addName(string name);
	void addStreetName(string street);
	void addCityID(int cityID);
	void addCityName(string city);
	void tableOutput();
	string getName()
	{
		return _name;
	}
	
	string getStreet()
	{
		return _street;
	}
	
	int getID()
	{
		return _cityID;
	}
	
private:
	string _name;
	string _street;
	string _city;
	int _cityID;
};

#endif
