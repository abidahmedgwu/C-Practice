#pragma once
#include <vector>
#include "Product.h"

class Inventory
{
private:
	std::vector<Product> inventory;
public:
	Inventory();
	Inventory(std::vector<Product> &inventory);
	~Inventory();
	void printInventory() const;
	int getSize() const;
	Product getProduct(int index) const;
	Product* getProductByID(unsigned long long id);
	void addItem(Product item);
	void removeItem(unsigned long long id);
	void reduceQuantity(unsigned long long id, unsigned int numDelete);
	float getInventoryValue() const;
};
