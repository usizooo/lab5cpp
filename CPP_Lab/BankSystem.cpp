#include "BankSystem.h"

#include <iostream>

using namespace std;

// ������������� ����������� ���������� � ������
BankSystem* BankSystem::instance = nullptr;

// ������ �������� ����������� ��� ������ ��������,
// ����� ��� ����, ����� �� ��� ������ ������ �����������
// ��������� ��-���������, ��� ��������� ���� ���������
BankSystem::BankSystem() { }

// � �������������� ������� �� ����� ������, �.�.
// �������� ��������� �� BankAccount �� map
BankSystem::~BankSystem()
{
    for (auto account : this->accounts)
        delete account.second;
    cout << "������ �������" << endl;
}

// ����������� ������ �������� �� ���������
void BankSystem::addNewAccount(BankAccount* account)
{
    this->accounts.insert({ account->getAccountNumber(), account });
}

// ������� ����� map �� ����� ����������
map<int, BankAccount*> BankSystem::getAccounts()
{
    return this->accounts;
}

// ����� ������������ ��� ����� ������������ ��������� BankSystem
// (���� ���������)
BankSystem* BankSystem::getInstance()
{
    if (BankSystem::instance == nullptr)
        BankSystem::instance = new BankSystem();
    return BankSystem::instance;
}