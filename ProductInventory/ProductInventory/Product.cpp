#include "Product.h"

// Constructors
Product::Product() {
	name = "";
	id = 0;
	price = 0;
	quantity = 0;
}

Product::Product(std::string name, unsigned long long id, float price, unsigned int quantity)
{
	this->name = name;
	this->id = id;
	this->price = price;
	this->quantity = quantity;
}

// Deconstructor
Product::~Product()
{
	// Do nothing
}

// Getters
std::string Product::getName() const
{
	return name;
}

unsigned long long Product::getID() const
{
	return id;
}

float Product::getPrice() const
{
	return price;
}

unsigned int Product::getQuantity() const
{
	return quantity;
}

// Setters
void Product::setName(std::string name)
{
	this->name = name;
}

void Product::setID(unsigned long long id)
{
	this->id = id;
}

void Product::setPrice(float price)
{
	this->price = price;
}

void Product::setQuantity(unsigned int quantity)
{
	this->quantity = quantity;
}
