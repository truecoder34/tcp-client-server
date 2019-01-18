#pragma once
#include "stdafx.h"
#include <string>

class User
{
public:
	std::string userName;
	std::string userSurename;
	int trainId;
	int ticketClass;

	int buyTicket(int classOfTicket, int trainID);

	User(const std::string &str1, const std::string &str2, int trId,
		int tickClass);
	~User();
};