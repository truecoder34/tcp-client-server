
#include "stdafx.h"
#include <WS2tcpip.h>
#include <string>
#include <fstream>
#include <iostream>
#include <msclr/marshal_cppstd.h>

#include "User.h"
#include "TrainsSchedule.h"

#pragma comment (lib, "ws2_32.lib")

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace std;


// ПРОТОТИПЫ ФУНКЦИЙ
void start_listen(SOCKET clientSocket);
SqlConnection^ connectToDB();
TrainsSchedule findListOfTrains(SqlConnection^ conn, String^ first_point, String^ second_point);
void bookTicket(SqlConnection^ conn, User booker);

// ГЛОБАЛЬНАЯ ВИДИМОСТЬ
//....................
User activeUser("empty", "empty", 0, 0);
TrainsSchedule currentSchedule("empty", "empty", "empty", "empty",
	0, 0, 0, 0, 0, 0, 0);
string firstPointGlobal;

int main(cli::array<System::String ^> ^args)
{
	setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы

	/*User activeUser("Vladislav", "Plotnikov");
	TrainsSchedule currentSchedule("Volgograd-1", "Saratov-1", "09-11-2018", "10-11-2018",
		003, 30, 17, 55, 4500, 2300, 1300, 102);*/

		// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0) {
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return 0;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		cerr << "Can't create a socket! Quitting" << endl;
		return 0;
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening 
	listen(listening, SOMAXCONN);

	// Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];		// Client's remote name
	char service[NI_MAXSERV];	// Service (i.e. port) the client is connect on

	ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		cout << host << " connected on port " << service << endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " <<
			ntohs(client.sin_port) << endl;
	}

	// Close listening socket
	closesocket(listening);

	start_listen(clientSocket); // начинаем рекурсивное прослушивание с заикленным while-ом внутри 

	// Close the socket
	closesocket(clientSocket);
	// Cleanup winsock
	WSACleanup();
	system("pause");
    return 0;
}


void start_listen(SOCKET clientSocket) {
	char buf[4096];
	// INITIALIZE BY 1
	for (int i = 0; i < 4096; i++)
	{
		buf[i] = 1;
	}

	ZeroMemory(buf, 4096);
	int itter = 2;
	// в recv происходит получение данных от клиента


	// Wait for client to send data	
	int bytesShift = 0;
	int bytesReceived = 0;
	//int itterOfRecieved = 0;


	
	while (true) 
	{

		bytesReceived = recv(clientSocket, &buf[bytesShift], 8192, 0); // ждем получение данных (блокирующая функция - задерживает выполнение кода на себе ожидая)
		bytesShift += bytesReceived;

		// FILL BUFFER
		// Указатель на ПОСЛЕДНИЙ ЭЛЕМЕНТ СТРОКИ 
		char * pch = strchr(buf, '\0');
		// ЕСЛИ ЕГО НЕТ, то ЖДЕМ 
		while (pch == NULL) 
		{
			bytesReceived = recv(clientSocket, &buf[bytesShift], 8192, 0); // ждем получение данных (блокирующая функция - задерживает выполнение кода на себе ожидая)
			bytesShift += bytesReceived;
			pch = strchr(buf, '\0');
		}

		// Считаю индекс нуль элемента
		int id = pch - buf + 1;

		if (bytesReceived == -1) {
			cout << activeUser.userName << " - Закрытие соединения..." << endl;
			// Close the socket
			closesocket(clientSocket);
			// Cleanup winsock
			WSACleanup();

			break;
		}

		// ОПЕРАЦИЯ НОМЕР 1 на клиенте - Ввод точки отправления поезда
		if (buf[0] == '1' && id == bytesShift)
		{
			cout << "Точка отправления поезда получена" << endl;
			send(clientSocket, "Поиск поездов начат, введите точку прибытия...", sizeof("Поиск поездов начат, введите точку прибытия..."), 0); // лог для клиента
			char pointOne[200]; // получение точки отправления на сервере

			int letterIndex = 0;
			while (buf[itter] != '\0')
			{
				pointOne[letterIndex] = buf[itter];
				itter++;
				letterIndex++;
			}

			// подготовка к поиску в базе
			// 1 - Подкоючились к БД - не обязательно
			SqlConnection^ conn = connectToDB();
			// 2 - Записываем точку ОТПРАВЛЕНИЯ в глобальную переменную 
			// Сначала преобразуем строчки 
			string pin(pointOne);
			firstPointGlobal = pin.substr(0, itter - 2);
			String^ firstPointConverted = gcnew String(pin.substr(0, itter - 2).c_str()); // ТУТ СТРОКА С КАВЫЧКАМИ получается 



			// запись точки отправки в глобальную видимость
			itter = 2;

			char buf[8192];
			bytesReceived = 0;
			bytesShift = 0;
		}


		// ОПЕРАЦИЯ НОМЕР 2 на клиенте - Ввод точки отправления поезда
		if (buf[0] == '2' && id == bytesShift)
		{
			cout << "Точка прибытия поезда получена" << endl;
			//send(clientSocket, "Поиск поездов продолжается...", sizeof("Поиск поездов продолжается..."), 0); // лог для клиента
			char pointTwo[200]; // получение точки отправления на сервере

			int letterIndex = 0;
			while (buf[itter] != '\0')
			{
				pointTwo[letterIndex] = buf[itter];
				itter++;
				letterIndex++;
			}

			// ПОИСК В БАЗЕ - поиск в базе по точке отправки и точке прибытия
			// 1 - Подкоючились к БД - не обязательно
			SqlConnection^ conn = connectToDB();
			// Сначала преобразуем строчки 
			string pin(pointTwo);
			String^ secondPointConverted = gcnew String(pin.substr(0, itter - 2).c_str()); // ТУТ СТРОКА С КАВЫЧКАМИ получается 
			String^ firstPointConverted = gcnew String(firstPointGlobal.c_str()); // ТУТ СТРОКА С КАВЫЧКАМИ получается 

																						   // Ищем в базе по 2м параметрам: Точка отправки, точка прибытия
			currentSchedule = findListOfTrains(conn, firstPointConverted, secondPointConverted);

			char answerString[8192];
			char delimeter[2] = ";";
			char bufferForNumbers[10];
		
			strcpy(answerString, currentSchedule.pointOne.c_str());
			strcat(answerString, delimeter);

			strcat(answerString, currentSchedule.pointTwo.c_str());
			strcat(answerString, delimeter);
			strcat(answerString, currentSchedule.dateDepart.c_str());
			strcat(answerString, delimeter);
			strcat(answerString, currentSchedule.dateArrival.c_str());

			strcat(answerString, delimeter);
			strcat(answerString, "Свобободно А=");
			sprintf(bufferForNumbers, "%d", currentSchedule.freePlacesA);
			strcat(answerString, bufferForNumbers);

			strcat(answerString, delimeter);
			strcat(answerString, "Цена А=");
			sprintf(bufferForNumbers, "%d", currentSchedule.CostA);
			strcat(answerString, bufferForNumbers);

			strcat(answerString, delimeter);
			strcat(answerString, "Свобободно B=");
			sprintf(bufferForNumbers, "%d", currentSchedule.freePlacesB);
			strcat(answerString, bufferForNumbers);

			strcat(answerString, delimeter);
			strcat(answerString, "Цена B=");
			sprintf(bufferForNumbers, "%d", currentSchedule.CostB);
			strcat(answerString, bufferForNumbers);

			strcat(answerString, delimeter);
			strcat(answerString, "Свобободно C=");
			sprintf(bufferForNumbers, "%d", currentSchedule.freePlacesC);
			strcat(answerString, bufferForNumbers);

			strcat(answerString, delimeter);
			strcat(answerString, "Цена C=");
			sprintf(bufferForNumbers, "%d", currentSchedule.CostC);
			strcat(answerString, bufferForNumbers);

			strcat(answerString, delimeter);
			strcat(answerString, "Номер поезда =");
			sprintf(bufferForNumbers, "%d", currentSchedule.trainId);
			strcat(answerString, bufferForNumbers);
			//strcat(answerString, delimeter);
			// Отправить список поездов 
			send(clientSocket, answerString, sizeof(answerString), 0);
			itter = 2;

			char buf[8192];
			bytesReceived = 0;
			bytesShift = 0;
		}

		// ОПЕРАЦИЯ НОМЕР 3 на клиенте -  ВЫВОД ВСЕГО РАСПИСАНИЯ
		if (buf[0] == '3' && id == bytesShift)
		{
			cout << "Запрос на получение ВСЕГО рассписания" << endl;
			send(clientSocket, "РАСПИСАНИЕ", sizeof("РАСПИСАНИЕ"), 0); // лог для клиента
			char scheduleFull[1000]; // получение точки отправления на сервере

			int letterIndex = 0;
			while (buf[itter] != '\0')
			{

				scheduleFull[letterIndex] = buf[itter];
				itter++;
				letterIndex++;
			}
			// поиск в базе по точке отправки
			// запись точки отправки в глобальную видимость

			// Отправить список поездов 
			//send(clientSocket, "Волгоград 1 - Саратов 001Ж", sizeof("Волгоград 1 - Саратов 001Ж"), 0);
			itter = 2;
			char buf[8192];
			bytesReceived = 0;
			bytesShift = 0;
		}

		// ОПЕРАЦИЯ НОМЕР 4 на клиенте - Бронирование билета
		if (buf[0] == '4' && id == bytesShift)
		{
			cout << "Информаиция для бронирования получена" << endl;
			send(clientSocket, "Билет забронирован", sizeof("Билет забронирован"), 0); // лог для клиента
			char infoAboutBooking[400]; // получение точки отправления на сервере

			int letterIndex = 0;

			while (buf[itter] != '\0')
			{
				infoAboutBooking[letterIndex] = buf[itter];
				itter++;
				letterIndex++;
			}

			// Spliting string
			char * pch;
			pch = strtok(infoAboutBooking, ";");
			activeUser.userName = pch;
			int itterOfElemsInMessage = 1;
			while (pch != NULL)
			{
				printf("%s\n", pch);
				pch = strtok(NULL, ";");
				if (itterOfElemsInMessage == 1)
				{
					activeUser.userSurename = pch;
				}
				if (itterOfElemsInMessage == 2)
				{
					activeUser.trainId = atoi(pch);
				}
				if (itterOfElemsInMessage == 3)
				{
					activeUser.ticketClass = atoi(pch);
				}
				itterOfElemsInMessage++;
			}

			//activeUser.userName =

			SqlConnection^ conn = connectToDB();
			bookTicket(conn, activeUser);
			// 

			// Отправить список поездов 
			//send(clientSocket, "Волгоград 1 - Саратов 001Ж", sizeof("Волгоград 1 - Саратов 001Ж"), 0);
			itter = 2;
			char buf[8192];
			bytesReceived = 0;
			bytesShift = 0;
		}


		cout << string(buf, 0, bytesReceived) << endl; // Получили от клиента 

		// Echo message back to client
		//send(clientSocket, buf, bytesReceived + 1, 0); // отправили весь буфер

		//start_listen(clientSocket); // рекурсия
	}
}


SqlConnection^ connectToDB() {
	SqlConnection^ conn;
	SqlConnectionStringBuilder^ connStringBuilder;

	connStringBuilder = gcnew SqlConnectionStringBuilder();
	connStringBuilder->DataSource = "DESKTOP-TQJGJM7\\SQLEXPRESS"; // CHANGE IT 
	connStringBuilder->InitialCatalog = "DB_Railway_CB";
	connStringBuilder->IntegratedSecurity = true;

	conn = gcnew SqlConnection(Convert::ToString(connStringBuilder));

	cout << "БД DB_Railway_CB подключена успешно" << endl;

	return conn;
}


TrainsSchedule findListOfTrains(SqlConnection^ conn, String^ first_point, String^ second_point)
{
	std::string point1;
	std::string point2;
	std::string date1;
	std::string date2;
	int id = 0;
	int fPlacesA = 0;
	int fPlacesB = 0;
	int fPlacesC = 0;
	int cost1 = 0;
	int cost2 = 0;
	int cost3 = 0;

	try {
		String^ sqlQueryText = "SELECT * FROM [dbo].[tbSchedule] WHERE [departStation] = '" + first_point + "' AND [arriveStation] = '" + second_point +"'";
		SqlCommand^ sqlCmd = gcnew SqlCommand(sqlQueryText, conn);
		conn->Open();

		SqlDataReader^ reader = sqlCmd->ExecuteReader();
		
		// Рассматриваю кейс где на запрос ОДНА СТРОЧКА
		while (reader->Read()) {
			point1 = msclr::interop::marshal_as< std::string >(reader["departStation"]->ToString());
			point2 = msclr::interop::marshal_as< std::string >(reader["arriveStation"]->ToString());
			date1 = msclr::interop::marshal_as< std::string >(reader["timeDepart"]->ToString());
			date2 = msclr::interop::marshal_as< std::string >(reader["timeArrive"]->ToString());
			id = Convert::ToInt32(reader["trainID"]);
			fPlacesA = Convert::ToInt32(reader["placesA"]);
			fPlacesB = Convert::ToInt32(reader["placesB"]);
			fPlacesC = Convert::ToInt32(reader["placesC"]);
			cost1 = Convert::ToInt32(reader["costA"]);
			cost2 = Convert::ToInt32(reader["costB"]);
			cost3 = Convert::ToInt32(reader["costC"]);
		}

	}

	finally{
		if (conn != nullptr) {
			 conn->Close();
		}
	}

	TrainsSchedule schedule(point1,point2,
			date1,
			date2,
			id, fPlacesA, fPlacesB, fPlacesC,
			cost1, cost2, cost3);
	return schedule;
}

// Метод бронирования билета
void bookTicket(SqlConnection^ conn, User booker)
{
	try {
		String^ name = gcnew String(booker.userName.c_str());
		String^ surname = gcnew String(booker.userSurename.c_str());
		String^ cmdText = "INSERT INTO [dbo].[bookedTickets] ([trainID], [name], [surname],[ticketClass]) VALUES(" + booker.trainId + ",'" + name + "','" + surname + "'," + booker.ticketClass + ")";
		SqlCommand^ cmd = gcnew SqlCommand(cmdText, conn);
		conn->Open();
		cmd->ExecuteNonQuery();
	}
	finally{
		if (conn != nullptr) {
			 conn->Close();
		}
	}
}