#include "stdafx.h"
#include "User.h"
#include <string>
#include <iostream>
using namespace std;

User::User(const std::string &str1, const std::string &str2, int trId,
	int tickClass)
{
	userName = str1;
	userSurename = str2;
	trainId = trId;
	ticketClass = tickClass;
}
int User::buyTicket(int classOfTicket, int trainID)
{
	return 0;
}

User::~User()
{
}