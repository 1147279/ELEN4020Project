#include "joinedTable.h"


joinedTable::joinedTable()
{
	_cityID = -1;
}




void joinedTable::addName(string name)
{
	_name = name;
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
	cout << _name << "  "<< _cityID << "  " << _city<<endl;
}
