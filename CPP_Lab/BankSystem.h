#ifndef BANK_SYSTEM_H
#define BANK_SYSTEM_H

#include "BankAccount.h"

#include <map>

using namespace std;

// Класс предназначенный для учёта созданных аккаунтов
// путём хранения их в map (т.е. контейнер хранящий ключ-значени).
// Выполнен через паттерн Синглтон
class BankSystem
{
private:
	static BankSystem* instance;
	map<int, BankAccount*> accounts;
	BankSystem();
	~BankSystem();

public:
	static BankSystem* getInstance();
	void addNewAccount(BankAccount* account);
	map<int, BankAccount*> getAccounts();
};

#endif