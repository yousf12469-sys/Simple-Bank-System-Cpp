#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

const string ClientsFileName = "Clients.text";

void ShowMainMenue();
void ShowTransactionMenue();

vector <string> SplitString(string S9, string Delim)
{
    vector <string> vString;
    short pos = 0;
    string sWord;

    while ((pos = S9.find(Delim)) != std::string::npos)
    {
        sWord = S9.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S9.erase(0, pos + Delim.length());
    }
    if (S9 != "")
    {
        vString.push_back(S9);
    }
    return vString;
}

struct stClinet
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    int CountBalance = 0;
    bool MarkForDelete = false;
};

string ConvertRecordToLine(stClinet Clinet, string Separator = "#//#")
{
    string stClinetRecord = "";
    stClinetRecord += Clinet.AccountNumber + Separator;
    stClinetRecord += Clinet.PinCode + Separator;
    stClinetRecord += Clinet.Name + Separator;
    stClinetRecord += Clinet.Phone + Separator;
    stClinetRecord += to_string(Clinet.CountBalance);

    return stClinetRecord;
}

stClinet CounvertLineToRecord(string Line, string Separator = "#//#")
{
    stClinet Clinet;
    vector<string> vClinetData;

    vClinetData = SplitString(Line, Separator);

    Clinet.AccountNumber = vClinetData[0];
    Clinet.PinCode = vClinetData[1];
    Clinet.Name = vClinetData[2];
    Clinet.Phone = vClinetData[3];
    Clinet.CountBalance = stod(vClinetData[4]);

    return Clinet;
}

void PrintClinetRecord(stClinet Clinet)
{
    cout << "\n\nThe following are the client Delete : \n\n";

    cout << "Account number   :" << Clinet.AccountNumber << endl;
    cout << "pinCode          :" << Clinet.PinCode << endl;
    cout << "Name             :" << Clinet.Name << endl;
    cout << "phone            :" << Clinet.Phone << endl;
    cout << "Account balance  :" << Clinet.CountBalance << endl;

}

vector <stClinet> LoadClientsDataFromFile(string FileName)
{
    vector<stClinet> vClient;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClinet Clinet;

        while (getline(MyFile, Line))
        {
            Clinet = CounvertLineToRecord(Line);
            vClient.push_back(Clinet);
        }
        MyFile.close();
    }
    return vClient;
}

void PrintClientRecord(stClinet Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(30) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.CountBalance;

}

void PrintClientRecordBalanceLine(stClinet Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.CountBalance;
}

void PrintAllClientsData()
{
    vector <stClinet> vClients = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\t Client List (" << vClients.size() << ")  Client(s). ";
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code ";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Phone ";
    cout << "| " << left << setw(12) << "Balance ";

    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\tno clients available in the system!";
    else


        for (stClinet Client : vClients)
        {
            PrintClientRecord(Client);

            cout << endl;
        }

    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;
}

void ShowTotalBalances()
{
    vector <stClinet> vClients = LoadClientsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    double TotalBalances = 0;
    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (stClinet Client : vClients)
        {
            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.CountBalance;
            cout << endl;
        }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
}

stClinet ReadNewClient()
{
    stClinet Client;

    cout << "Enter Account Number ? ";
    
    getline(cin >> ws, Client.AccountNumber);

    cout << "Enter PinCode ? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name ? ";
    getline(cin, Client.Name);

    cout << "Enter Phone ? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance ? ";
    cin >> Client.CountBalance;

    return Client;

}

void AddDataLineToFile(string FileName, string strDataLine)
{
    fstream MyFile;
    char Revision = 'y';

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << strDataLine << endl;
        MyFile.close();
    }
}

void AddNewClient()
{
    stClinet Client;
    Client = ReadNewClient();

    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddClients()
{
    char AddMore = 'Y';

    do
    {
        system("cls");
        cout << "Adding New Client : \n\n";
        AddNewClient();

        cout << "\nClient Added Successfully , do you want to add more clients ? "; 
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool FindClientByAccountNumber(string AccountNumber, vector<stClinet> vClients, stClinet& Client)
{
    for (stClinet c : vClients)
    {
        if (c.AccountNumber == AccountNumber)
        {
            Client = c;
            return true;
        }
    }
    return false;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "please enter Account number? ";
    cin >> AccountNumber;
    return AccountNumber;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClinet>& vClients)
{
    for (stClinet& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector <stClinet> SaveClientsDataToFile(string FileName, vector <stClinet> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;

    if (MyFile.is_open())
    {
        for (stClinet c : vClients)
        {
            if (c.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(c);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClinet>& vClients)
{
    stClinet Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClinetRecord(Client);

        cout << "\n\nAre you sure you want delete client ? n/y ?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);

            vClients = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\n Client Deleted Successfully. \n";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n"; 
            return false;
    }
}

stClinet ChangeClientRecord(string AccountNumber)
{
    stClinet Client;
    Client.AccountNumber = AccountNumber;

    cout << "enter pin code ?";
    getline(cin >> ws, Client.PinCode);

    cout << "enter name ?";
    getline(cin, Client.Name);

    cout << "enter phone ?";
    getline(cin, Client.Phone);

    cout << "enter account balance ?";
    cin >> Client.CountBalance;

    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClinet>& vClients)
{
    stClinet Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClinetRecord(Client);

        cout << "\n\nAre you sure you want delete client ? n/y ?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (stClinet& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientsDataToFile(ClientsFileName, vClients);

            // Refresh Clients 
            vClients = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\n Client Deleted Successfully. \n";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";

        return false;
    }
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <stClinet> vClients)
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y / n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        for (stClinet& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.CountBalance += Amount;
                SaveClientsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.CountBalance;
                return true;
            }
        }
        return false;
    }
}

void ShowDeleteClientScreen()
{
    cout << "\n______________________________________________________________\n";
    cout << "\tDelete client screen";
    cout << "\n______________________________________________________________\n";
    
    vector <stClinet> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
    
}

void ShowUpdateClientScreen()
{
    cout << "\n______________________________________________________________\n";
    cout << "\tUpdate client screen";
    cout << "\n______________________________________________________________\n";

    vector <stClinet> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowAddNewClientsScreen()
{
    cout << "\n______________________________________________________________\n";
    cout << "\tAdd client screen";
    cout << "\n______________________________________________________________\n";

    AddClients();

}

void ShowFindClientScreen()
{
    cout << "\n______________________________________________________________\n";
    cout << "\tfind client screen";
    cout << "\n______________________________________________________________\n";

    vector <stClinet> vClients = LoadClientsDataFromFile(ClientsFileName);
    stClinet Client;
    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClinetRecord(Client);
    else
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";

}

void ShowEndScreen()
{
    cout << "\n______________________________________________________________\n";
    cout << "\tprogram ends";
    cout << "\n______________________________________________________________\n";

}

void ShowDepositScreen()
{
    cout << "\n______________________________________________________________\n";
    cout << "\tDeposit Screen";
    cout << "\n______________________________________________________________\n";

    stClinet Client;
    vector <stClinet> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClinetRecord(Client);

    double Amount = 0;
    cout << "\nplease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithDrawScreen()
{
    cout << "\n______________________________________________________________\n";
    cout << "\tWithdraw Screen";
    cout << "\n______________________________________________________________\n";

    stClinet Client;
    vector <stClinet> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClinetRecord(Client);
    double Amount = 0;
    cout << "\nplease enter deposit amount? ";
    cin >> Amount;

    while (Amount > Client.CountBalance)
    {
        cout << "\nAmount exceeds the balance, you can withdraw up to : " << Client.CountBalance;
        cout << "\nplease enter another amount? ";
        cin >> Amount;
    }
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void ShowTotalBalancesScreen()
{
    ShowTotalBalances();
}

enum enTransactionsMenuueOptions {eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4};

enum enMainMenueOptions
{
    eListClients = 1, eAddNewClients = 2, eDeleteClients = 3, eUpdateClient = 4, eFindClient = 5, enShowTransactionsMenue = 6, eExit = 7
};

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to main menue...";
    system("pause>0");
    ShowMainMenue();
}

void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to transaction menue...";
    system("pause>0");
    ShowTransactionMenue();
}

short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void PerfromTransactionsMenueOption(enTransactionsMenuueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenuueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsMenuueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsMenuueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsMenuueOptions::eShowMainMenue:
    {
        ShowMainMenue();
    }
    }
}

void ShowTransactionMenue()
{
    system("cls");
    cout << "=========================================================================\n";
    cout << "\t\tTransaction Menue screen\n";
    cout << "=========================================================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] withdraw.\n";
    cout << "\t[3] total balance.\n";
    cout << "\t[4] main menue.\n";

    PerfromTransactionsMenueOption((enTransactionsMenuueOptions)ReadTransactionsMenueOption());
}

short ReadMainMeneuOption()
{
    cout << "choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch(MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        PrintAllClientsData();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClients:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eDeleteClients:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;
    
    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::enShowTransactionsMenue:
        system("cls");
        ShowTransactionMenue();
        break;

    case enMainMenueOptions::eExit:
        system("cls");
        ShowEndScreen();
        break;
    }
}


void ShowMainMenue()
{
    system("cls");
    cout << "==============================================================================\n";
    cout << "\t\tMain menue screen\n";
    cout << "==============================================================================\n";
    cout << "\t[1] Show Client List.\n";

    cout << "\t[2] Add new Client List.\n";
    
    cout << "\t[3] Delete Client List.\n";
    
    cout << "\t[4] update Client List.\n";
    
    cout << "\t[5] find Client List.\n";
    
    cout << "\t[6] Transaction.\n";

    cout << "\t[7] Exit.\n";

    cout << "=======================================================================================\n";

    PerfromMainMenueOption((enMainMenueOptions)ReadMainMeneuOption());

}



int main()
{
    ShowMainMenue();

    system("pause>0");

    return 0;
}

