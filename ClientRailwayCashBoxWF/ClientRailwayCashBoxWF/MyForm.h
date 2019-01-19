#pragma once

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <string>
#include <msclr\marshal_cppstd.h>

namespace ClientRailwayCashBoxWF {

	SOCKET sock; // сокет который потом вернется из winsock_start()
	std::string userInput; // 

	//setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	SOCKET winsock_start() {
		std::string ipAddress = "127.0.0.1";// IP Address of the server
		int port = 54000;// Listening port # on the server

		// Initialize WinSock

		WSAData data;
		WORD ver = MAKEWORD(2, 2);
		int wsResult = WSAStartup(ver, &data);
		if (wsResult != 0)
		{
			cerr << "Can't start Winsock, Err #" << wsResult << endl;
			//return;
		}

		// Create socket
		SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET)
		{
			cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
			WSACleanup();
			//return;
		}

		// Fill in a hint structure
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(port);
		inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

		// Connect to server
		int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
		if (connResult == SOCKET_ERROR)
		{
			cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
			closesocket(sock);
			WSACleanup();
			//return;
		}

		return sock;

	}

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			// предусмотреть реконнект ?

			sock = winsock_start(); // запускаем подключение - получаем глобальный сокет
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  tbDepartSt;
	protected:

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  tbArrivalSt;

	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  tbName;


	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  tbTrainID;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::RadioButton^  radioButtonA;
	private: System::Windows::Forms::RadioButton^  radioButtonB;
	private: System::Windows::Forms::RadioButton^  radioButtonС;





	private: System::Windows::Forms::TextBox^  tbMsg;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::TextBox^  tbSurname;
	private: System::Windows::Forms::Label^  label7;



	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tbDepartSt = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tbArrivalSt = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tbName = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->tbTrainID = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->radioButtonA = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonС = (gcnew System::Windows::Forms::RadioButton());
			this->tbMsg = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->tbSurname = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(16, 44);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(582, 31);
			this->button1->TabIndex = 0;
			this->button1->Text = L"1 - Start search";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// tbDepartSt
			// 
			this->tbDepartSt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tbDepartSt->Location = System::Drawing::Point(154, 12);
			this->tbDepartSt->Name = L"tbDepartSt";
			this->tbDepartSt->Size = System::Drawing::Size(444, 26);
			this->tbDepartSt->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(12, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(133, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Departure station";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(12, 87);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(104, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Arrival station";
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// tbArrivalSt
			// 
			this->tbArrivalSt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tbArrivalSt->Location = System::Drawing::Point(154, 81);
			this->tbArrivalSt->Name = L"tbArrivalSt";
			this->tbArrivalSt->Size = System::Drawing::Size(444, 26);
			this->tbArrivalSt->TabIndex = 4;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(16, 113);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(582, 33);
			this->button2->TabIndex = 5;
			this->button2->Text = L"2 - Start search";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->richTextBox1->Location = System::Drawing::Point(16, 185);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(582, 127);
			this->richTextBox1->TabIndex = 6;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox1_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(12, 162);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(76, 20);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Schedule";
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Cursor = System::Windows::Forms::Cursors::Default;
			this->label4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(244, 379);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(99, 20);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Book ticket";
			this->label4->Click += gcnew System::EventHandler(this, &MyForm::label4_Click);
			// 
			// tbName
			// 
			this->tbName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tbName->Location = System::Drawing::Point(69, 414);
			this->tbName->Name = L"tbName";
			this->tbName->Size = System::Drawing::Size(208, 26);
			this->tbName->TabIndex = 9;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->ImageAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->label5->Location = System::Drawing::Point(12, 417);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(51, 20);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Name";
			this->label5->Click += gcnew System::EventHandler(this, &MyForm::label5_Click);
			// 
			// tbTrainID
			// 
			this->tbTrainID->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tbTrainID->Location = System::Drawing::Point(170, 452);
			this->tbTrainID->Name = L"tbTrainID";
			this->tbTrainID->Size = System::Drawing::Size(429, 26);
			this->tbTrainID->TabIndex = 11;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->ImageAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->label6->Location = System::Drawing::Point(13, 458);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(65, 20);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Train ID";
			this->label6->Click += gcnew System::EventHandler(this, &MyForm::label6_Click);
			// 
			// radioButtonA
			// 
			this->radioButtonA->AutoSize = true;
			this->radioButtonA->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButtonA->Location = System::Drawing::Point(17, 501);
			this->radioButtonA->Name = L"radioButtonA";
			this->radioButtonA->Size = System::Drawing::Size(81, 24);
			this->radioButtonA->TabIndex = 13;
			this->radioButtonA->TabStop = true;
			this->radioButtonA->Text = L"Class A";
			this->radioButtonA->UseVisualStyleBackColor = true;
			this->radioButtonA->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButtonA_CheckedChanged);
			// 
			// radioButtonB
			// 
			this->radioButtonB->AutoSize = true;
			this->radioButtonB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButtonB->Location = System::Drawing::Point(275, 501);
			this->radioButtonB->Name = L"radioButtonB";
			this->radioButtonB->Size = System::Drawing::Size(81, 24);
			this->radioButtonB->TabIndex = 14;
			this->radioButtonB->TabStop = true;
			this->radioButtonB->Text = L"Class B";
			this->radioButtonB->UseVisualStyleBackColor = true;
			this->radioButtonB->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButtonB_CheckedChanged);
			// 
			// radioButtonС
			// 
			this->radioButtonС->AutoSize = true;
			this->radioButtonС->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButtonС->Location = System::Drawing::Point(518, 501);
			this->radioButtonС->Name = L"radioButtonС";
			this->radioButtonС->Size = System::Drawing::Size(81, 24);
			this->radioButtonС->TabIndex = 15;
			this->radioButtonС->TabStop = true;
			this->radioButtonС->Text = L"Class C";
			this->radioButtonС->UseVisualStyleBackColor = true;
			this->radioButtonС->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButtonC_CheckedChanged);
			// 
			// tbMsg
			// 
			this->tbMsg->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tbMsg->Location = System::Drawing::Point(17, 592);
			this->tbMsg->Name = L"tbMsg";
			this->tbMsg->Size = System::Drawing::Size(582, 26);
			this->tbMsg->TabIndex = 17;
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(16, 328);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(582, 33);
			this->button3->TabIndex = 18;
			this->button3->Text = L"3 - Get all schedule";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button5
			// 
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button5->Location = System::Drawing::Point(17, 531);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(581, 32);
			this->button5->TabIndex = 19;
			this->button5->Text = L"4 - Book ticket";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// tbSurname
			// 
			this->tbSurname->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tbSurname->Location = System::Drawing::Point(391, 414);
			this->tbSurname->Name = L"tbSurname";
			this->tbSurname->Size = System::Drawing::Size(208, 26);
			this->tbSurname->TabIndex = 20;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(311, 417);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(74, 20);
			this->label7->TabIndex = 21;
			this->label7->Text = L"Surname";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(613, 656);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->tbSurname);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->tbMsg);
			this->Controls->Add(this->radioButtonС);
			this->Controls->Add(this->radioButtonB);
			this->Controls->Add(this->radioButtonA);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->tbTrainID);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->tbName);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->tbArrivalSt);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tbDepartSt);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {}
		private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {}
		private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {}
		private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {}
		private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {}
		private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {}
		private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {}


		String^ ticketClass; 
		private: System::Void radioButtonA_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			ticketClass = "A";
		}
		private: System::Void radioButtonB_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			ticketClass = "B";
		}
		private: System::Void radioButtonC_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			ticketClass = "C";
		}

		/*
			Отправка на сервер ПЕРВОЙ точки. 
			Точки отправления. 
			Код команды 1
		*/ 
		private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			// Do-while loop to send and receive data
			char buf[8192];
			// INITIALIZE buf by 1 symbols. PREVENT \0 symbol appearance 
			memset(buf,1,sizeof(char)*8192);

			userInput = "1"; // тип операции		

			System::String^ DepartSt = tbDepartSt->Text; // считали текст из поля DepartSt	
			msclr::interop::marshal_context context;
			std::string normalDepartSt = context.marshal_as<std::string>(DepartSt); // преобразовали String^ в std::string

			userInput += ' ' + normalDepartSt;// собираем цифру-операцию пробел Точка отправления

			if (userInput.size() > 0)		// Make sure the user has typed in something
			{
				int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0); // отправляем серверу
				if (sendResult != SOCKET_ERROR)
				{
					// Wait for response
					int bytesReceived = recv(sock, buf, 8192, 0); // принимаем ответ от сервера			

					// TRY TO GET ALL DATA, TO PREVENT INTERUPTIONS
					char * pch = strchr(buf, '\0'); // Parse by \0 symbol 

					// IF THERE IS NO \0 symbol in recieved STRING
					while (pch == NULL)
					{
						//WAIT UNTILL WE GET THIS SYMBOL
						bytesReceived = recv(sock, buf, 8192, 0); // ждем получение данных (блокирующая функция - задерживает выполнение кода на себе ожидая)
						pch = strchr(buf, '\0');
					}
					// -----------

					if (bytesReceived > 0)
					{
						std::string response = buf;
						msclr::interop::marshal_context context;
						System::String^ logStr = context.marshal_as<String^>(buf); // преобразовали std::string в String^
						richTextBox1->Text = "Ответ сервера: " + logStr; // записать ответ сервера в поле лога
					}
				}
			}
		}

		/*
			Отправка на сервер ВТОРОЙ точки. 
			Точки прибытия.
			Код команды 2. 
			Получение всего расписания
		*/ 
		private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			// Do-while loop to send and receive data
			char buf[8192];
			userInput = "2"; // тип операции		

			System::String^ ArrivalSt = tbArrivalSt->Text; // считали текст из поля ArrivalSt	
			msclr::interop::marshal_context context;
			std::string normalArrivalSt = context.marshal_as<std::string>(ArrivalSt); // преобразовали String^ в std::string

			userInput += ' ' + normalArrivalSt;// собираем цифру-операцию пробел Точка прибытия

			if (userInput.size() > 0)		// Make sure the user has typed in something
			{
				int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0); // отправляем серверу
				if (sendResult != SOCKET_ERROR)
				{
					// Wait for response
					ZeroMemory(buf, 8192);
					int bytesReceived = recv(sock, buf, 8192, 0); // принимаем ответ от сервера					

					if (bytesReceived > 0)
					{
						std::string response = buf;
						msclr::interop::marshal_context context;
						System::String^ logStr = context.marshal_as<String^>(buf); // преобразовали std::string в String^
						richTextBox1->Text = "Ответ сервера: " + logStr; // записать ответ сервера в поле лога
					}
				}
			}
		}

		/*
			Отправка на сервер команды о запросе на вывод ВСЕГО расписания. 
			Сервер присылает ВСЕ ДОСТУПНОЕ расписание
			Клиент выводит его в РичТекстБокс
			Если расписания нет - выводит что расписания в базе нет
			Код команды 3. 
		*/ 
		private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			// Do-while loop to send and receive data
			char buf[8192];
			userInput = "3"; // тип операции
			userInput += ' '; 

			if (userInput.size() > 0)		// Make sure the user has typed in something
			{
				int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0); // отправляем серверу
				if (sendResult != SOCKET_ERROR)
				{
					// Wait for response
					ZeroMemory(buf, 8192);
					int bytesReceived = recv(sock, buf, 8192, 0); // принимаем ответ от сервера					

					if (bytesReceived > 0)
					{
						std::string response = buf;
						msclr::interop::marshal_context context;
						System::String^ logStr = context.marshal_as<String^>(buf); // преобразовали std::string в String^
						richTextBox1->Text = "Ответ сервера: " + logStr; // записать ответ сервера в поле лога
					}
				}
			}
		}

	
		private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			
		}


		
		/*
			Отправка на сервер команды о запросе на бронировние места в определенном поезде
			Отправояется на сервер ИМЯ_Фамилия;IDпоезда;Класс
			Код команды 4.
		*/
		private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			// Do-while loop to send and receive data
			char buf[8192];
			userInput = "4"; // тип операции
			msclr::interop::marshal_context context;

			// Get text from tbName
			System::String^ name = tbName->Text;
			std::string normalName = context.marshal_as<std::string>(name); // преобразовали String^ в std::string

			// Get text from tbSurname
			System::String^ surname = tbSurname->Text;
			std::string normalSurname = context.marshal_as<std::string>(surname); // преобразовали String^ в std::string

			// Get text from tbTrainID
			System::String^ trainId = tbTrainID->Text;
			//msclr::interop::marshal_context context;
			std::string normalTrainId = context.marshal_as<std::string>(trainId); // преобразовали String^ в std::string

			int intNormalTicketClass;
			//msclr::interop::marshal_context context;
			if (ticketClass == "A") 
			{
				intNormalTicketClass = 1; // преобразовали String^ в std::string;
			}
			else if (ticketClass == "B") 
			{
				intNormalTicketClass = 2;
			}
			else if (ticketClass == "C")
			{
				intNormalTicketClass = 3;
			}
			std::string normalTicketClass = context.marshal_as<std::string>(ticketClass); // преобразовали String^ в std::string;

			// FORM STRING TO SEND SERVER
			userInput += ' ' + normalName + ';' + normalSurname + ';' + normalTrainId + ';' + std::to_string(intNormalTicketClass);


			if (userInput.size() > 0)		// Make sure the user has typed in something
			{
				int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0); // отправляем серверу
				if (sendResult != SOCKET_ERROR)
				{
					// Wait for response
					ZeroMemory(buf, 8192);
					int bytesReceived = recv(sock, buf, 8192, 0); // принимаем ответ от сервера					

					if (bytesReceived > 0)
					{
						std::string response = buf;
						msclr::interop::marshal_context context;
						System::String^ logStr = context.marshal_as<String^>(buf); // преобразовали std::string в String^
						tbMsg->Text = logStr; // записать ответ сервера в поле лога
					}
				}
			}
		}
	};
}
