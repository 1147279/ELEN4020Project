#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class customer
{
public:
	customer();
	bool isFoundID(int cityID);
	void addName(string name);
	void addStreetName(string street);
	void addCityID(int cityID);
	void printCustomer();
	void resetAttributes();
	
	vector<string> getName()
	{
		return _name;
	}
	
	vector<string> getStreet()
	{
		return _street;
	}
	
	int getNumOfElements()
	{
		return _name.size();
	}
	
	int getID()
	{
		return _cityID;
	}
	
private:
	vector<string> _name;
	vector<string> _street;
	int _cityID;
};

#endif
