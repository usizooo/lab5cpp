#include "BankSystem.h"
#include "BankAccount.h"

#include <iostream>

using namespace std;

// Реализация дружественной классу BankAccount фукнции для переводов со счёта на счёт
bool transfer(int accountNumber1, int accountNumber2, double value)
{
	auto accounts = BankSystem::getInstance()->getAccounts();
	accounts[accountNumber1]->withdraw(value);
	accounts[accountNumber2]->deposit(value);
	return true;
}
// Вывод данных об аккануте на консоль
void printAccount(BankAccount* account)
{
	cout << "Номер аккаунта: " << account->getAccountNumber() << endl;
	cout << "Баланс: " << account->getBalance() << endl;
	cout << "Накопленные проценты: " << account->getInterest() << endl << endl;
}
// Ввод номера аккаунта с валидацией
int inputAccountNumber(bool isInit = false)
{
	int accountNumber;
	cout << "Введите номер счёта: ";
	cin >> accountNumber;
	auto accounts = BankSystem::getInstance()->getAccounts();

	// Смотрим сначала зарегистрирован ли данный аккаунт
	return accounts.find(accountNumber) != accounts.end() 
		? accountNumber
		// Если нет, смотрим, корректное ли введено значение для 
		// создания нового аккаунта
		: isInit && accountNumber > 0 ? accountNumber : -1;
}
// Ввод денежных средств с валидацией
double inputMoneyValue(int accountNumber = -1)
{
	double value;
	cout << "Введите сумму: ";
	cin >> value;

	// Если указан какой-то accountNumber, значит мы
	// пытаемся снять деньги со счёта для каких-то целей
	if (accountNumber != -1)
	{
		auto accounts = BankSystem::getInstance()->getAccounts();
		// Делаем проверку возможно ли снятие указанной суммы
		if (accounts[accountNumber]->getBalance() < value)
			return -1;
	}

	// Проверка на то, что введённая сумма положительна
	return value >= 0
		? value
		: -1;
}
// Ввод процентной ставки с валидацией
double inputInterestRate()
{
	double value;
	cout << "Введите процентную ставку [0; 1]: ";
	cin >> value;
	
	// Делаем проверку на то, что введённая процентная ставка
	// в пределах от нуля до единицы
	return value >= 0 && value <= 1
		? value
		: -1;
}

int main()
{
	setlocale(LC_ALL, "ru");

	// Далее идёт самая простая из возможных реализация консольного интерфейса
	// для тестирования нашей системы. Реализовано всё, через бесконечный цикл 
	// и switch-case на каждое возможное дейтсвие в системе

	bool isActive = true;

	while (isActive)
	{
		cout << "Введите любую букву" << endl;
		char c; cin >> ws >> c;

		system("cls");

		cout << "Действия:" << endl;
		cout << "0 - Создать новый аккаунт" << endl;
		cout << "1 - Посмотреть все аккаунты" << endl;
		cout << "2 - Перевести деньги с счёта на счёт" << endl;
		cout << "3 - Посмотреть баланс (по номеру)" << endl;
		cout << "4 - Пополнить кошелёк (по номеру)" << endl;
		cout << "5 - Снять деньги с кошелька (по номеру)" << endl;
		cout << "6 - Посмотреть накопленные проценты (по номеру)" << endl;
		cout << "7 - Установить процентную ставку (по номеру)" << endl;
		cout << "8 - Выход" << endl;

		char action;
		cin >> ws >> action;
		switch (action)
		{
		case '0':
		{
			int accountNumber = inputAccountNumber(true);
			if (accountNumber == -1)
			{
				cout << "Задан некорректный номер аккаунта" << endl;
				break;
			}

			double balance = inputMoneyValue();
			if (balance == -1)
			{
				cout << "Задана некорректная денежная сумма" << endl;
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
				cout << "Пока нет созданных кошельков" << endl;
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
				cout << "Указанный номер аккаунта не зарегистрирован в системе" << endl;
				break;
			}

			int accountNumber2 = inputAccountNumber();
			if (accountNumber2 == -1)
			{
				cout << "Указанный номер аккаунта не зарегистрирован в системе" << endl;
				break;
			}

			double value = inputMoneyValue(accountNumber1);
			if (value == -1)
			{
				cout << "Задана некорректная денежная сумма" << endl;
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
				cout << "Указанный номер аккаунта не зарегистрирован в системе" << endl;
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
				cout << "Указанный номер аккаунта не зарегистрирован в системе" << endl;
				break;
			}

			double value = inputMoneyValue();
			if (value == -1)
			{
				cout << "Задана некорректная денежная сумма" << endl;
				break;
			}

			auto accounts = BankSystem::getInstance()->getAccounts();
			accounts[accountNumber]->deposit(value);
			cout << "Счёт успешно пополнен" << endl;

			break;
		}
		case '5':
		{
			int accountNumber = inputAccountNumber();
			if (accountNumber == -1)
			{
				cout << "Указанный номер аккаунта не зарегистрирован в системе" << endl;
				break;
			}

			double value = inputMoneyValue(accountNumber);
			if (value == -1)
			{
				cout << "Задана некорректная денежная сумма" << endl;
				break;
			}

			auto accounts = BankSystem::getInstance()->getAccounts();
			accounts[accountNumber]->withdraw(value);
			cout << "Деньги успешно выведены со счёта" << endl;

			break;
		}
		case '6':
		{
			int accountNumber = inputAccountNumber();
			if (accountNumber == -1)
			{
				cout << "Указанный номер аккаунта не зарегистрирован в системе" << endl;
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
				cout << "Указанный номер аккаунта не зарегистрирован в системе" << endl;
				break;
			}

			double value = inputInterestRate();
			if (value == -1)
			{
				cout << "Задана некорректная процентная ставка" << endl;
				break;
			}

			auto accounts = BankSystem::getInstance()->getAccounts();
			accounts[accountNumber]->setInterestRate(value);
			cout << "Процентная ставка была успешно изменена" << endl;

			break;
		}
		case '8':
			isActive = false;
			break;
		default:
			cout << "Неверный номер действия" << endl;
		}
	}

	return 0;
}