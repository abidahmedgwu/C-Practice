#include "Inventory.h"
#include <iostream>

// Constructors
Inventory::Inventory()
{
	inventory[0] = Product();
}

Inventory::Inventory(std::vector<Product> &inventory)
{
	this->inventory = inventory;
}

// Destructor
Inventory::~Inventory()
{
	// Do nothing
}

// Displays the entire inventory with product details
void Inventory::printInventory() const
{
	if (size(inventory) == 0)
	{
		std::cout << "Inventory is empty\n\n";
		return;
	}
	for (int i = 0; i < size(inventory); i++)
	{
		std::cout << "Item: " << inventory[i].getName() << "\nID: " << inventory[i].getID() <<
			"\nPrice: $" << inventory[i].getPrice() << "\nQuantity: " << inventory[i].getQuantity()
			<< "\n\n";
	}
	std::cout << "Inventory Value: $" << getInventoryValue() << "\n\n";
}

// Gets the size of the inventory
int Inventory::getSize() const
{
	return size(inventory);
}

// Gets the product at a certain index
// Cannot be directly modified
Product Inventory::getProduct(int index) const
{
	return inventory[index];
}

// Gets a certain product by its id
// Returns the pointer for direct modification
// 0(n) time
Product* Inventory::getProductByID(unsigned long long id)
{
	for (int i = 0; i < size(inventory); i++)
	{
		if (inventory[i].getID() == id)
		{
			return &inventory[i];
		}
	}
	return nullptr;
}
// Adds an item to the inventory
void Inventory::addItem(Product item)
{
	inventory.push_back(item);
}

// Deletes an item in the inventory completely by using the item id
// O(n) time
void Inventory::removeItem(unsigned long long id)
{
	for (int i = 0; i < size(inventory); i++)
	{
		if (inventory[i].getID() == id)
		{
			inventory.erase(inventory.begin() + i);
			return;
		}
	}
}

// Reduces a certain quantity of a product by using the item id
//O(n) time
void Inventory::reduceQuantity(unsigned long long id, unsigned int numDelete)
{
	return getProductByID(id)->setQuantity(getProductByID(id)->getQuantity() - numDelete);
}

// Gets the total price of all the items in the inventory
float Inventory::getInventoryValue() const
{
	float total = 0.0;
	for (int i = 0; i < size(inventory); i++)
	{
		total += (inventory[i].getPrice() * inventory[i].getQuantity());
	}
	return total;
}