#include "BankSystem.h"
#include "BankAccount.h"

#include <iostream>

using namespace std;

// ���������� ������������� ������ BankAccount ������� ��� ��������� �� ����� �� ����
bool transfer(int accountNumber1, int accountNumber2, double value)
{
	auto accounts = BankSystem::getInstance()->getAccounts();
	accounts[accountNumber1]->withdraw(value);
	accounts[accountNumber2]->deposit(value);
	return true;
}
// ����� ������ �� �������� �� �������
void printAccount(BankAccount* account)
{
	cout << "����� ��������: " << account->getAccountNumber() << endl;
	cout << "������: " << account->getBalance() << endl;
	cout << "����������� ��������: " << account->getInterest() << endl << endl;
}
// ���� ������ �������� � ����������
int inputAccountNumber(bool isInit = false)
{
	int accountNumber;
	cout << "������� ����� �����: ";
	cin >> accountNumber;
	auto accounts = BankSystem::getInstance()->getAccounts();

	// ������� ������� ��������������� �� ������ �������
	return accounts.find(accountNumber) != accounts.end() 
		? accountNumber
		// ���� ���, �������, ���������� �� ������� �������� ��� 
		// �������� ������ ��������
		: isInit && accountNumber > 0 ? accountNumber : -1;
}
// ���� �������� ������� � ����������
double inputMoneyValue(int accountNumber = -1)
{
	double value;
	cout << "������� �����: ";
	cin >> value;

	// ���� ������ �����-�� accountNumber, ������ ��
	// �������� ����� ������ �� ����� ��� �����-�� �����
	if (accountNumber != -1)
	{
		auto accounts = BankSystem::getInstance()->getAccounts();
		// ������ �������� �������� �� ������ ��������� �����
		if (accounts[accountNumber]->getBalance() < value)
			return -1;
	}

	// �������� �� ��, ��� �������� ����� ������������
	return value >= 0
		? value
		: -1;
}
// ���� ���������� ������ � ����������
double inputInterestRate()
{
	double value;
	cout << "������� ���������� ������ [0; 1]: ";
	cin >> value;
	
	// ������ �������� �� ��, ��� �������� ���������� ������
	// � �������� �� ���� �� �������
	return value >= 0 && value <= 1
		? value
		: -1;
}

int main()
{
	setlocale(LC_ALL, "ru");

	// ����� ��� ����� ������� �� ��������� ���������� ����������� ����������
	// ��� ������������ ����� �������. ����������� ��, ����� ����������� ���� 
	// � switch-case �� ������ ��������� �������� � �������

	bool isActive = true;

	while (isActive)
	{
		cout << "������� ����� �����" << endl;
		char c; cin >> ws >> c;

		system("cls");

		cout << "��������:" << endl;
		cout << "0 - ������� ����� �������" << endl;
		cout << "1 - ���������� ��� ��������" << endl;
		cout << "2 - ��������� ������ � ����� �� ����" << endl;
		cout << "3 - ���������� ������ (�� ������)" << endl;
		cout << "4 - ��������� ������ (�� ������)" << endl;
		cout << "5 - ����� ������ � �������� (�� ������)" << endl;
		cout << "6 - ���������� ����������� �������� (�� ������)" << endl;
		cout << "7 - ���������� ���������� ������ (�� ������)" << endl;
		cout << "8 - �����" << endl;

		char action;
		cin >> ws >> action;
		switch (action)
		{
		case '0':
		{
			int accountNumber = inputAccountNumber(true);
			if (accountNumber == -1)
			{
				cout << "����� ������������ ����� ��������" << endl;
				break;
			}

			double balance = inputMoneyValue();
			if (balance == -1)
			{
				cout << "������ ������������ �������� �����" << endl;
				break;
			}

			BankAccount* ba = new BankAccount(accountNumber, balance);

			break;
		}
		case '1':
		{
			auto accounts = BankSystem::getInstance()->getAccounts();
			if (accounts.size() == 0)
			{
				cout << "���� ��� ��������� ���������" << endl;
				break;
			}
			for (auto account : accounts)
				printAccount(account.second);

			break;
		}
		case '2':
		{
			int accountNumber1 = inputAccountNumber();
			if (accountNumber1 == -1)
			{
				cout << "��������� ����� �������� �� ��������������� � �������" << endl;
				break;
			}

			int accountNumber2 = inputAccountNumber();
			if (accountNumber2 == -1)
			{
				cout << "��������� ����� �������� �� ��������������� � �������" << endl;
				break;
			}

			double value = inputMoneyValue(accountNumber1);
			if (value == -1)
			{
				cout << "������ ������������ �������� �����" << endl;
				break;
			}

			transfer(accountNumber1, accountNumber2, value);

			break;
		}
		case '3':
		{
			int accountNumber = inputAccountNumber();
			if (accountNumber == -1)
			{
				cout << "��������� ����� �������� �� ��������������� � �������" << endl;
				break;
			}

			auto accounts = BankSystem::getInstance()->getAccounts();
			cout << accounts[accountNumber]->getBalance() << endl;

			break;
		}	
		case '4':
		{
			int accountNumber = inputAccountNumber();
			if (accountNumber == -1)
			{
				cout << "��������� ����� �������� �� ��������������� � �������" << endl;
				break;
			}

			double value = inputMoneyValue();
			if (value == -1)
			{
				cout << "������ ������������ �������� �����" << endl;
				break;
			}

			auto accounts = BankSystem::getInstance()->getAccounts();
			accounts[accountNumber]->deposit(value);
			cout << "���� ������� ��������" << endl;

			break;
		}
		case '5':
		{
			int accountNumber = inputAccountNumber();
			if (accountNumber == -1)
			{
				cout << "��������� ����� �������� �� ��������������� � �������" << endl;
				break;
			}

			double value = inputMoneyValue(accountNumber);
			if (value == -1)
			{
				cout << "������ ������������ �������� �����" << endl;
				break;
			}

			auto accounts = BankSystem::getInstance()->getAccounts();
			accounts[accountNumber]->withdraw(value);
			cout << "������ ������� �������� �� �����" << endl;

			break;
		}
		case '6':
		{
			int accountNumber = inputAccountNumber();
			if (accountNumber == -1)
			{
				cout << "��������� ����� �������� �� ��������������� � �������" << endl;
				break;
			}

			auto accounts = BankSystem::getInstance()->getAccounts();
			cout << accounts[accountNumber]->getInterest() << endl;

			break;
		}
		case '7':
		{
			int accountNumber = inputAccountNumber();
			if (accountNumber == -1)
			{
				cout << "��������� ����� �������� �� ��������������� � �������" << endl;
				break;
			}

			double value = inputInterestRate();
			if (value == -1)
			{
				cout << "������ ������������ ���������� ������" << endl;
				break;
			}

			auto accounts = BankSystem::getInstance()->getAccounts();
			accounts[accountNumber]->setInterestRate(value);
			cout << "���������� ������ ���� ������� ��������" << endl;

			break;
		}
		case '8':
			isActive = false;
			break;
		default:
			cout << "�������� ����� ��������" << endl;
		}
	}

	return 0;
}