#pragma once
#include <string>

class Product
{
private:
	std::string name;
	unsigned long long id;
	float price;
	unsigned int quantity;
public:
	Product();
	Product(std::string name, unsigned long long id, float price, unsigned int quantity);
	~Product();
	// Getters
	std::string getName() const;
	unsigned long long getID() const;
	float getPrice() const;
	unsigned int getQuantity() const;
	// Setters
	void setName(std::string name);
	void setID(unsigned long long id);
	void setPrice(float price);
	void setQuantity(unsigned int quantity);
};
