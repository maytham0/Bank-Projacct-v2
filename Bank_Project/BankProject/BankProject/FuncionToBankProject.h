#pragma once
#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include<iomanip>

using namespace std;


namespace BankFuncion {
    const string ClientsFileName = "Client_data.txt";
    struct sClient {
        string AccountNumber;
        string PinCode;
        string Name;
        string Phone;
        double AccountBalance;
        bool MarkForDelete = false;
    };

    vector<string> SplitString(string S1, string Delim) {
        vector<string> vString;
        short pos = 0;
        string sWord;
        // define a string variable
        // use find() function to get the position of the delimiters
        while ((pos = S1.find(Delim)) != std::string::npos) {
            sWord = S1.substr(0, pos); // store the word
            if (sWord != "") {
                vString.push_back(sWord);
            }
            S1.erase(0, pos + Delim.length());
        }
        if (S1 != "") {
            vString.push_back(S1); // it adds last word of the string.
        }
        return vString;
    }
    sClient ConvertLinetoRecord(string Line, string Seperator = "#//#") {
        sClient Client;
        vector<string> vClientData;
        vClientData = SplitString(Line, Seperator);
        Client.AccountNumber = vClientData[0];
        Client.PinCode = vClientData[1];
        Client.Name = vClientData[2];
        Client.Phone = vClientData[3];
        Client.AccountBalance = stod(vClientData[4]); // cast string to double
        return Client;
    }
    string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
        string stClientRecord = "";
        stClientRecord += Client.AccountNumber + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += Client.Name + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += to_string(Client.AccountBalance);
        return stClientRecord;
    }
    vector<sClient> LoadCleintsDataFromFile(string FileName) {
        vector<sClient> vClients;
        fstream MyFile;
        MyFile.open(FileName, ios::in); // read Mode
        if (MyFile.is_open()) {
            string Line;
            sClient Client;
            while (getline(MyFile, Line)) {
                Client = ConvertLinetoRecord(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }
    bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClients) {
        for (sClient& C : vClients) {
            if (C.AccountNumber == AccountNumber) {
                C.MarkForDelete = true;
                return true;
            }
        }
        return false;
    }
    bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client) {
        for (sClient C : vClients) {
            if (C.AccountNumber == AccountNumber) {
                Client = C;
                return true;
            }
        }
        return false;
    }

    bool FindClientByAccountNumber2(string AccountNumber, sClient& Client) {
        vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
        for (sClient C : vClients) {
            if (C.AccountNumber == AccountNumber) {
                Client = C;
                return true;
            }
        }
        return false;
    }
    vector<sClient> SaveCleintsDataToFileToDelet(string FileName, vector<sClient> vClients) {
        fstream MyFile;
        MyFile.open(FileName, ios::out); // overwrite
        string DataLine;
        if (MyFile.is_open()) {
            for (sClient C : vClients) {
                if (C.MarkForDelete == false) { // we only write records that are not marked for delete.
                    DataLine = ConvertRecordToLine(C);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
        return vClients;
    }
    string ReadClientAccountNumber() {
        string AccountNumber = "";
        cout << "\nPlease enter Account Number? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

    void PrintClientCard(sClient Client) {
        cout << "\nThe following are the client details:\n";
        cout << "\n----------------------------------------------\n";
        cout << "\nAccout Number: " << Client.AccountNumber;
        cout << "\nPin Code     : " << Client.PinCode;
        cout << "\nName         : " << Client.Name;
        cout << "\nPhone        : " << Client.Phone;
        cout << "\nAccount Balance: " << Client.AccountBalance;
        cout << "\n----------------------------------------------\n";
    }
    bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients) {
        sClient Client;
        char Answer = 'n';
        if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
            PrintClientCard(Client);
            cout << "\n\nAre you sure you want delete this client? y/n ? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y') {
                MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
                SaveCleintsDataToFileToDelet(ClientsFileName, vClients);
                // Refresh Clients
                vClients = LoadCleintsDataFromFile(ClientsFileName);
                cout << "\n\nClient Deleted Successfully.";
                return true;
            }
        }
        else {
            cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
            return false;
        }
        return false;
    }
    void SaveVectorToFileToUpdate(string FileName, vector <sClient>& vVectorContect)
    {
        fstream MyFile0;
        MyFile0.open(FileName, ios::out);
        string DataLine;
        if (MyFile0.is_open())
        {

            for (sClient Line : vVectorContect)
            {
                DataLine = ConvertRecordToLine(Line);
                MyFile0 << DataLine << endl;
            }
            MyFile0.close();
        }
    }

    void SaveVectorToFileToAdd(string FileName, vector <sClient> vVectorContect)
    {
        fstream MyFile0;
        MyFile0.open(FileName, ios::out | ios::app);

        if (MyFile0.is_open())
        {

            for (sClient Line : vVectorContect)
            {
                MyFile0 << ConvertRecordToLine(Line) << endl;
            }
            MyFile0.close();
        }
    }
    vector<sClient> GetClientInfo()
    {
        sClient D1;
        vector<sClient>vClient;
        cout << "Enter Acount Number :"; getline(cin >> ws, D1.AccountNumber);
        cout << "\nEnter Pin Code :"; getline(cin, D1.PinCode);
        cout << "\nEnter Name :"; getline(cin, D1.Name);
        cout << "\nEnter Phone Number :"; getline(cin, D1.Phone);
        cout << "\nEnter Acount Balanc :"; cin >> D1.AccountBalance;
        cout << endl;

        vClient.push_back(D1);

        return vClient;
    }

    sClient ChangeClientRecord(string AccountNumber) {
        sClient Client;
        Client.AccountNumber = AccountNumber;
        cout << "\n\nEnter PinCode? ";
        getline(cin >> ws, Client.PinCode);
        cout << "Enter Name? ";
        getline(cin, Client.Name);
        cout << "Enter Phone? ";
        getline(cin, Client.Phone);
        cout << "Enter AccountBalance? ";
        cin >> Client.AccountBalance;
        return Client;
    }

    bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients) {
        sClient Client;
        char Answer = 'n';
        if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
            PrintClientCard(Client);
            cout << "\n\nAre you sure you want update this client? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y') {
                for (sClient& C : vClients) {
                    if (C.AccountNumber == AccountNumber) {
                        C = ChangeClientRecord(AccountNumber);
                        break;
                    }
                }
                SaveVectorToFileToUpdate(ClientsFileName, vClients);
                cout << "\n\nClient Updated Successfully.";
                return true;
            }
        }
        else {
            cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
            return false;
        }
        return false;
    }

    void PrintClientRecord(sClient Client) {
        cout << "| " << setw(15) << left << Client.AccountNumber;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(40) << left << Client.Name;
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(12) << left << Client.AccountBalance;
    }
    void PrintAllClientsData(vector<sClient> vClients) {
        cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        for (sClient Client : vClients) {
            PrintClientRecord(Client);
            cout << endl;
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

    void FindClientByAccountNumberToPrintHim(string fileName)
    {
        vector <sClient>vClient;
        vClient = LoadCleintsDataFromFile(ClientsFileName);
        sClient Client;
        string AccountNumber = ReadClientAccountNumber();
        if (FindClientByAccountNumber2(AccountNumber, Client))
        {
            PrintClientCard(Client);
        }
        else cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }
    int  Validate_Number()
    {
        short Number;
        cin >> Number;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Enter a valid one:" << endl;
            cin >> Number;
        }
        return Number;
    }
    int Deposit(string FileName)
    {
        char Answer = 'y';
        bool clientFound = false;
        int DepostNumber;
        vector<sClient> vClient = LoadCleintsDataFromFile(FileName);
        sClient Client;
        string AccountNumber = ReadClientAccountNumber();
        for (sClient& Line : vClient) {
            if (AccountNumber == Line.AccountNumber)
            {
                PrintClientCard(Line);
                clientFound = true;
                cout << "\nPleas Enter Deposit amount? ";
                cin >> DepostNumber;
                cout << "\nAre you sure wont Deposit?(y,n)\n";
                cin >> Answer;
                if (tolower(Answer) == 'y') {

                    Line.AccountBalance = Line.AccountBalance + DepostNumber;
                    SaveVectorToFileToUpdate(FileName, vClient);
                    return Line.AccountBalance;

                }

            }


        }
        if (!clientFound) { cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!"; }
        return -1;
    }
    int WithDrow(string FileName)

    {
        bool clientFund = false;
        char Answer = 'y';
        double WithdrowNumber = 0;
        vector<sClient> vClient = LoadCleintsDataFromFile(FileName);
        sClient Client;
        string AccountNumber = ReadClientAccountNumber();
        for (sClient& Line : vClient) {
            if (AccountNumber == Line.AccountNumber)
            {
                PrintClientCard(Line);
                clientFund = true;


                cout << "\nPleas Enter Withdrow amount? ";
                cin >> WithdrowNumber;

                if (WithdrowNumber > Line.AccountBalance) {
                    cout << "Amount Exceeds the balanc,you can withdrow UP to :" << Line.AccountBalance << endl;
                    cout << "Pleas Enter another amount ?";
                    cin >> WithdrowNumber;
                }
                cout << "\nAre you sure wont Withdrow?(y,n)\n";
                cin >> Answer;
                if (tolower(Answer) == 'y') {

                    Line.AccountBalance = Line.AccountBalance - WithdrowNumber;
                    SaveVectorToFileToUpdate(FileName, vClient);
                    return Line.AccountBalance;

                }

            }

        }
        if (!clientFund) { cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!"; }
        return -1;

    }


    void TotalBalanc(string FileName)
    {

        vector<sClient> vClient = LoadCleintsDataFromFile(FileName);
        sClient Client;

        double TotleBalance =0;
        for (sClient & Line : vClient) {
            cout << "|" <<setw(22)<<left<< Line.AccountNumber <<"|" <<setw(32)<<left<< Line.Name  <<"|" << Line.AccountBalance << endl;
            TotleBalance +=Line.AccountBalance;

           
        }
        cout << "--------------------------------------------------------------\n\n";
        cout << "The Totle Balance For All client(s). <<"<<TotleBalance << ">>\n";
       

    }
    int HowManyClientHave(string FileName)
    {
        vector<sClient>vClient = LoadCleintsDataFromFile(FileName);
        int Count = 0;
        for (sClient & Line : vClient)
        {
            if (!Line.AccountNumber.empty())
            {
                Count++;
            }
        }
        return Count;
    }
}

