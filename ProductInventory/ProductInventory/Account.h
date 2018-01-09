#pragma once
#include <string>

class Account
{
private:
	std::string username;
	std::string password;
public:
	Account();
	Account(std::string username, std::string password);
	~Account();
	std::string getUsername() const;
	std::string getPassword() const;
};

