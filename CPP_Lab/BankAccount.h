#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <map>

using namespace std;

// Основной класс, объекты которого и есть созданные кошельки в системе
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