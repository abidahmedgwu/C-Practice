#include "Account.h"

// Constructors
Account::Account()
{
	username = "";
	password = "";
}

Account::Account(std::string username, std::string password)
{
	this->username = username;
	this->password = password;
}

// Destructor
Account::~Account()
{
	// Do nothing
}

// Getters
std::string Account::getUsername() const
{
	return username;
}

std::string Account::getPassword() const
{
	return password;
}
