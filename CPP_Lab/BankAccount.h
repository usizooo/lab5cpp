#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <map>

using namespace std;

// �������� �����, ������� �������� � ���� ��������� �������� � �������
class BankAccount
{
private:
	int accountNumber;
	double balance;
	double interestRate = 0.1;

public:
	BankAccount(int accountNumber, double balance);

	void deposit(double value);
	void withdraw(double value);
	double getBalance();
	double getInterest();
	void setInterestRate(double value);
	int getAccountNumber();

};

#endif