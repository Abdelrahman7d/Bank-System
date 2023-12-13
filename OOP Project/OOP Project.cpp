
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsLoginScreen.h"
using namespace std;

enum enProsses{pAddNew = 0, pDelete = 1};
string RequestAccounNumber() {
	cout << "Please write the account number : " << endl;
	return clsInputValidate::ReadString();
}

void RequestClientInfo(clsBankClient& Client) {

	cout << "\nEnter FirstName: ";
	Client.FirstName = clsInputValidate::ReadString();

	cout << "\nEnter LastName: ";
	Client.LastName = clsInputValidate::ReadString();

	cout << "\nEnter Email: ";
	Client.Email = clsInputValidate::ReadString();

	cout << "\nEnter Phone: ";
	Client.Phone = clsInputValidate::ReadString();

	cout << "\nEnter PinCode: ";
	Client.PinCode = clsInputValidate::ReadString();

	cout << "\nEnter Account Balance: ";
	Client.AccountBalance = clsInputValidate::ReadFloatNumber();
}

void PrintSaveResult(clsBankClient::enSaveResults result, clsBankClient client) {

	switch (result)
	{
	case clsBankClient::svFaildEmptyObject:
	{
		cout << "\nError account was not saved because it's Empty\n";
		break;
	}
	case clsBankClient::svSucceeded:
	{
		cout << "\nAccount was saved successfully :-)\n";
		client.Print();
		break;
	}
	case clsBankClient::svFaildAccountNumberExists:
	{
		cout << "\nFaild to add account because the account number is already exist!\n";
		break;
	}
	}
}

bool IsValidAccountNumber(enProsses prosses, string AccountNumber) {
	switch (prosses)
	{
	case pAddNew:
		return clsBankClient::IsClientExist(AccountNumber);
		break;
	case pDelete:
		return !clsBankClient::IsClientExist(AccountNumber);
		break;
	}
}

string GetAccountNumberValidationErrorMessage(enProsses prosses, string AccountNumber) {
	switch (prosses)
	{
	case pAddNew:
		return "\nThe entered account number '" + AccountNumber + "' is already exist, please try again : \n";
		break;
	case pDelete:
		return "\nThe entered account number '" + AccountNumber + "' is not exist, Please try again : \n";
		break;
	}
}

string GetValidAccountNumber(enProsses prosses) {

	string AccountNumber = "";

	cout << "Please enter the account number : \n";
	AccountNumber = clsInputValidate::ReadString();

	while (IsValidAccountNumber(prosses, AccountNumber)) {

		cout << GetAccountNumberValidationErrorMessage(prosses, AccountNumber);
		AccountNumber = clsInputValidate::ReadString();
	}

	return AccountNumber;
}

//Opreations
void UpdateClient() {

	clsBankClient client = clsBankClient::Find(RequestAccounNumber());

	while (client.IsEmpty()) {
		cout << "There is no client wiht the entered account number, Please try agian!" << endl;
		client = clsBankClient::Find(RequestAccounNumber());
	}

	client.Print();

	cout << "\n\nUpdate Client Info:";
	cout << "\n____________________\n";

	RequestClientInfo(client);

	clsBankClient::enSaveResults result;

	result = client.Save();

	PrintSaveResult(result, client);
}

void AddNewClient() {

	string AccountNumber = GetValidAccountNumber(enProsses::pAddNew);

	clsBankClient client = clsBankClient::GetAddNewClientObject(AccountNumber);

	RequestClientInfo(client);
	
	clsBankClient::enSaveResults result;
	result = client.Save();

	PrintSaveResult(result,client);
}

void DeleteClient() {

	string AccountNumber = GetValidAccountNumber(enProsses::pDelete);

	clsBankClient client = clsBankClient::Find(AccountNumber);

	client.Print();

	cout << "\nAre you sure that you want to delete this client ? (Y/y)\n";

	char Answer = 'n';
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y') {
		if (client.Delete()) {
			cout << "\nClient was deleted successfully :-)\n";		
		}
		else {
			cout << "\nError, The client was not delteted!\n";
		}
	}

	
	
	clsBankClient::enSaveResults result;
	result = client.Save();

	PrintSaveResult(result, client);
}

void PrintClientRecordLine(clsBankClient Client)
{

	cout << "| " << setw(15) << left << Client.AccountNumber();
	cout << "| " << setw(20) << left << Client.FullName();
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(20) << left << Client.Email;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowClientsList()
{

	vector <clsBankClient> vClients = clsBankClient::GetClientsList();

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(20) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(20) << "Email";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else

		for (clsBankClient Client : vClients)
		{

			PrintClientRecordLine(Client);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;


	double TotalBalances = clsBankClient::GetTotalBalances();

	cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
	cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";

}

int main()
{

	while (clsLoginScreen::ShowLoginScreen());
	system("pause>0");
}