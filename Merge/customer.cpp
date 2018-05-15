#include "customer.h"


customer::customer()
{
	_cityID = -1;
}

bool customer::isFoundID(int cityID)
{
	if(_cityID == cityID)
		return true;
	else
		return false;
}



void customer::addName(string name)
{
	_name.push_back(name);
}


void customer::addCityID(int cityID)
{
	_cityID = cityID;
}


void customer::printCustomer()
{
	int listSize = _name.size();
	
	
	for(int i = 0; i < listSize; i++)
	{
		cout << _name.at(i) << "   "<< _cityID << "  "<< getNumOfElements() <<endl; 
	}
	
}


void customer::resetAttributes()
{
	_name.clear();
	_cityID = -1;
}



