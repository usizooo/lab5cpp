#include "BankSystem.h"

#include <iostream>

using namespace std;

// Инициализация статической переменной в классе
BankSystem* BankSystem::instance = nullptr;

// Пустой ЗАКРЫТЫЙ конструктор для работы паттерна,
// нужен для того, чтобы не был создан пустой конструктор
// ПУБЛИЧНЫЙ по-умолчанию, что разрушает идею Синглтона
BankSystem::BankSystem() { }

// В деконструкторе очищаем за собой память, т.е.
// зачищаем указатели на BankAccount из map
BankSystem::~BankSystem()
{
    for (auto account : this->accounts)
        delete account.second;
    cout << "Память очищена" << endl;
}

// Регистрация нового аккаунта по указателю
void BankSystem::addNewAccount(BankAccount* account)
{
    this->accounts.insert({ account->getAccountNumber(), account });
}

// Возврат копии map со всеми аккаунтами
map<int, BankAccount*> BankSystem::getAccounts()
{
    return this->accounts;
}

// Метод возвращающий ТОТ САМЫЙ ЕДИНСТВЕННЫЙ экземпляр BankSystem
// (идея Синглтона)
BankSystem* BankSystem::getInstance()
{
    if (BankSystem::instance == nullptr)
        BankSystem::instance = new BankSystem();
    return BankSystem::instance;
}