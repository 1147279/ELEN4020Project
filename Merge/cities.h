#ifndef CITIES_H
#define CITIES_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class cities
{
public:
	cities();
	bool isFoundID(int cityID);
	void addStreetName(string city);
	void addCityID(int cityID);
	void printCity();
	void resetAttributes();
	
	vector<string> getCity()
	{
		return _city;
	}
	
	int getNumOfElements()
	{
		return _city.size();
	}
	
	int getID()
	{
		return _cityID;
	}
	
private:
	vector<string> _city;
	int _cityID;
};


#endif
