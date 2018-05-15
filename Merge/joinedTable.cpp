#include "joinedTable.h"


joinedTable::joinedTable()
{
	_cityID = -1;
}




void joinedTable::addName(string name)
{
	_name = name;
}

void joinedTable::addStreetName(string street)
{
	_street = street;
}

void joinedTable::addCityID(int cityID)
{
	_cityID = cityID;
}

void joinedTable::addCityName(string city)
{
	_city = city;
}


void joinedTable::tableOutput()
{
	cout << _name << "  " << _street<< "  "<< _cityID << "  " << _city<<endl;
}
