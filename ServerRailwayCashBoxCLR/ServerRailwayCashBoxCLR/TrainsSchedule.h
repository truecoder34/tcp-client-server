#pragma once
#include "stdafx.h"
#include <string>

class TrainsSchedule
{
public:
	int trainId;				// ID ������
	std::string pointOne;		// ��������� �����
	std::string pointTwo;		// �������� �����

	std::string dateDepart; 
	std::string dateArrival;

	int freePlacesA;			// ���������� ���� ������ A
	int freePlacesB;			// ���������� ���� ������ B
	int freePlacesC;			// ���������� ���� ������ C
	int freePlacesQuantity; 

	int CostA;					// ���� ������ ������ A
	int CostB;					// ���� ������ ������ B
	int CostC;					// ���� ������ ������ C

	// �������� ��� ����������
	//std::string getAllSchedule();

	// �������� ���������� ������� ��� 2� ���������� �������
	std::string getCurrentTrain(std::string &point1, std::string &point2);

	// �������� ���������� � ��������� ������� �� ������������� ������
	int getInfoAboutFreePlaces(int ClassId);


	// ����������� � ���������� ������
	TrainsSchedule(const std::string &str1,
				   const std::string &str2,
				   const std::string &date1,
				   const std::string &date2,
					int,int,int,int,int, int, int);
	~TrainsSchedule();


};
