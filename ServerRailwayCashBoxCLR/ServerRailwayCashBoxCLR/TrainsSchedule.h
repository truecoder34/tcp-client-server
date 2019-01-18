#pragma once
#include "stdafx.h"
#include <string>

class TrainsSchedule
{
public:
	int trainId;				// ID поезда
	std::string pointOne;		// Начальная точка
	std::string pointTwo;		// Конечная точка

	std::string dateDepart; 
	std::string dateArrival;

	int freePlacesA;			// Количество мест класса A
	int freePlacesB;			// Количество мест класса B
	int freePlacesC;			// Количество мест класса C
	int freePlacesQuantity; 

	int CostA;					// Цена билета класса A
	int CostB;					// Цена билета класса B
	int CostC;					// Цена билета класса C

	// Получить ВСЕ расписание
	//std::string getAllSchedule();

	// Получить расписание поездов для 2х конкретных станций
	std::string getCurrentTrain(std::string &point1, std::string &point2);

	// ПОлучить информацию о доступных билетах по определенному классу
	int getInfoAboutFreePlaces(int ClassId);


	// Конструктор и деструктор класса
	TrainsSchedule(const std::string &str1,
				   const std::string &str2,
				   const std::string &date1,
				   const std::string &date2,
					int,int,int,int,int, int, int);
	~TrainsSchedule();


};
