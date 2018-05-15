#include "cities.h"


cities::cities()
{
	_cityID = -1;
}

bool cities::isFoundID(int cityID)
{
	if(_cityID == cityID)
		return true;
	else
		return false;
}




void cities::addStreetName(string city)
{
	_city.push_back(city);
}

void cities::addCityID(int cityID)
{
	_cityID = cityID;
}


void cities::printCity()
{
	int listSize = _city.size();
	
	
	for(int i = 0; i < listSize; i++)
	{
		cout << _city.at(i) << "  " << _cityID << "  "<< getNumOfElements() <<endl; 
	}
	
}


void cities::resetAttributes()
{
	_city.clear();
	_cityID = -1;
}

