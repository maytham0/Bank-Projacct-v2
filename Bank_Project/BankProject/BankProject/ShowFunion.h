#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<cctype>
#include "FuncionToBankProject.h"
#include<iomanip>
using namespace std;
using namespace BankFuncion;
 namespace Screen {
	const string ClientFileName = "Client_data.txt";

	enum enTransaction_Menue_Screen {
		eDposit=1,eWithdrow=2,eTotelBalanc=3 ,eMainMene=4
	};
	void Transactcion();
	void GoBackToTransactionMenue()
	{
		
		cout << "\n\nPress any key to go back to Transaction Menue...";
		system("pause>0");
		cout << endl;
		Transactcion();
	}
	short ReadNumberToPerfromTransctionMenueScreen()
	{
		short N;
	
		cin >> N;
		return N;
	}
	void ShowDeposit()
	{
		cout << "---------------------------\n";
		cout << "\t Deposit  \n";
			cout << "---------------------------\n";
		Deposit(ClientFileName);
	}
	void ShowWithdrow() {
		cout << "---------------------------\n";
		cout << "\t Deposit  \n";
		cout << "---------------------------\n";
		WithDrow(ClientFileName);
	}
	void ShowTotelBalanc()
	{
		cout << setw(40) << "Balances List (" << HowManyClientHave(ClientFileName) << ") Client(s).\n";
		cout << "--------------------------------------------------------------\n";
		cout << "| Account Number" << setw(20) << "| Client Name" << setw(30)<< "| Balanc \n";
		cout << "--------------------------------------------------------------\n";
		TotalBalanc(ClientFileName);
	}
	void PerfromTransctionMenueScreen(enTransaction_Menue_Screen TransactionMenue)
	{
		
		switch (TransactionMenue)
		{
		case enTransaction_Menue_Screen::eDposit:
			system("cls");
			//Deposit;
			//Deposit(ClientFileName);
			ShowDeposit();
			GoBackToTransactionMenue();
			break;
		case enTransaction_Menue_Screen::eWithdrow:
			system("cls");
			//withdow
			//WithDrow(ClientsFileName);
			ShowWithdrow();
			GoBackToTransactionMenue();
			break;

		case enTransaction_Menue_Screen::eTotelBalanc:
			system("cls");
			
			//TotleBalace;
			//TotalBalanc(ClientsFileName);
			ShowTotelBalanc();
			GoBackToTransactionMenue();
			break;
		case enTransaction_Menue_Screen::eMainMene:
			system("cls");
			//main Menue 

			break;

		}
	}
	void Transactcion()
	{
		system("cls");
		cout << "==========================================\n";
		cout << setw(32) << right << "Transaction Menue Screen\n";
		cout << "==========================================\n";
		cout << setw(16) << right << "[1]" << " Deposit.\n";
		cout << setw(16) << right << "[2]" << " Withdrow.\n";
		cout << setw(16) << right << "[3]" << " Total Balances.\n";
		cout << setw(16) << right << "[4]" << " Main Menue.\n";
		cout << "==========================================\n";

		cout << "Choose what do you want to do ? [1 to 4]?";
		PerfromTransctionMenueScreen((enTransaction_Menue_Screen)ReadNumberToPerfromTransctionMenueScreen());
	}
	void MainMenueScreen() {
		cout << "==========================================\n";
		cout << setw(32) << right << "Main Menue Screen\n";
		cout << "==========================================\n";
		cout << setw(16) << right << "[1]" << " Show Client List.\n";
		cout << setw(16) << right << "[2]" << " Add New Client.\n";
		cout << setw(16) << right << "[3]" << " Delete Client.\n";
		cout << setw(16) << right << "[4]" << " Update Client.\n";
		cout << setw(16) << right << "[5]" << " Find Client.\n";
		cout << setw(16) << right << "[6]" << " Transaction.\n";
		cout << setw(16) << right << "[7]" << " Exit.\n";
		cout << "==========================================\n";

		cout << "Choose what do you want to do ? [1 to 7]?";
		
	}


	void MainMenueChoos(int WhatYouChoos)
	{
		
		vector<sClient>vClient = LoadCleintsDataFromFile(ClientFileName);
		switch (WhatYouChoos)
		{
		case 1:
			//Show Client 
			PrintAllClientsData(LoadCleintsDataFromFile(ClientFileName));
			break;
		case 2:
			//AddNewClient
			SaveVectorToFileToAdd(ClientFileName,GetClientInfo());
			break;

		case 3:
			//Delete
			DeleteClientByAccountNumber(ReadClientAccountNumber(), vClient);
			break;
		case 4 :
			//Update Client
			UpdateClientByAccountNumber(ReadClientAccountNumber(), vClient);
			break;
		case 5 :
			//Find Client
			FindClientByAccountNumberToPrintHim(ClientsFileName);
			break;
		case 6:
			//Transcaton
			Transactcion();
			break;
		case 7 :
			//Exit 
			system("cls");
			cout << "App is End =) <3";
			system("pause>0");
			exit(0);
			break;

		default :
			cout << "\nYour Choose Wrong ,Choos Right One Agen\n";

			//MAke him go bake to start 

		}
	}


	void ElsePage()
	{
		do{
			MainMenueScreen();
			//system("cls");
			MainMenueChoos(Validate_Number());
			system("pause");

			system("cls");

		} while (0==0);
	}
	}
