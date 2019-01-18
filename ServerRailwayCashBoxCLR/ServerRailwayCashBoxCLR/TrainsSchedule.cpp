#include "stdafx.h"
#include "TrainsSchedule.h"
#include <string>
#include <iostream>
using namespace std;

// Конструктор класса
TrainsSchedule::TrainsSchedule(const std::string &point1,
	const std::string &point2,
	const std::string &date1,
	const std::string &date2,
	int Id, int fPlacesA, int fPlacesB, int fPlacesC, 
	int Cost1, int Cost2, int Cost3)
{
	pointOne = point1;
	pointTwo = point2;
	trainId = Id;
	freePlacesA = fPlacesA;
	freePlacesB = fPlacesB;
	freePlacesC = fPlacesC;
	CostA = Cost1;
	CostB = Cost2;
	CostC = Cost3;
	dateDepart = date1;
	dateArrival = date2;
}

/*string TrainsSchedule::getAllSchedule()
{

	return;
} */

string TrainsSchedule::getCurrentTrain(std::string &point1, std::string &point2)
{
	pointOne = point1;
	pointTwo = point2;

	return 0;
}

int TrainsSchedule::getInfoAboutFreePlaces(int ClassId)
{	
	if (ClassId == 1) 
	{
		freePlacesQuantity = freePlacesA;
	} 
	else if (ClassId == 2)
	{
		freePlacesQuantity = freePlacesB;
	}
	else if (ClassId == 3)
	{
		freePlacesQuantity = freePlacesC;
	}
	return freePlacesQuantity;
}

TrainsSchedule::~TrainsSchedule()
{
}