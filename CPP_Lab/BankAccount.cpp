#include "BankSystem.h"
#include "BankAccount.h"

BankAccount::BankAccount(int accountNumber, double balance)
{
	this->accountNumber = accountNumber;
	this->balance = balance;
	// При создании нового аккаунта ОБЯЗАТЕЛЬНО
	// регистрируем его в системе
	BankSystem::getInstance()->addNewAccount(this);
}

void BankAccount::deposit(double value)
{
	this->balance += value;
}

void BankAccount::withdraw(double value)
{
	this->balance -= value;
}

double BankAccount::getBalance()
{
	return this->balance;
}

double BankAccount::getInterest()
{
	return this->balance * this->interestRate * (1. / 12.);
}

void BankAccount::setInterestRate(double value)
{
	this->interestRate = value;
}

int BankAccount::getAccountNumber()
{
	return this->accountNumber;
}