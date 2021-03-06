// ProductInventory.cpp : Defines the entry point for the console application.
//

#include "Inventory.h"
#include "Account.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void writeData(Inventory &rInventory);
bool idCheck(Inventory &rInventory, unsigned long long idToCheck);
void idErrorMessage(unsigned long long idToCheck);
bool idCheckFlag(Inventory &rInventory, unsigned long long idToCheck);
bool checkLogin(std::vector<Account> &rAccounts, std::string username, std::string password);

enum choice { VIEW = 1, ADD = 2, EDIT = 3, DELETE = 4, LOGOUT = 9 }; // Main menu choice enum
enum editChoice { NAME = 1, ID, PRICE, ADD_QUANTITY, REDUCE_QUANTITY, MAIN_MENU = 9 }; // Edit menu choice enum

int main()
{
	// Get existing products from inventory.txt
	std::vector<Product> products;
	std::ifstream infile;
	infile.open("inventory.txt", std::ios::in);
	std::string name;
	unsigned long long id;
	float price;
	unsigned int quantity;
	while (infile >> name >> id >> price >> quantity)
	{
		products.push_back(Product(name, id, price, quantity));
	}
	Inventory myInventory(products);
	infile.close();

	// Get accounts from accounts.txt
	std::vector<Account> accounts;
	infile.open("accounts.txt", std::ios::in);
	std::string username, password;
	while (infile >> username >> password)
	{
		accounts.push_back(Account(username, password));
	}

	// Remove the products vector to free up memory
	std::vector<Product>().swap(products);

	// Run the program forever until the user quits
	while (true)
	{
		// Login Screen
		bool loginFlag = true;
		while (loginFlag)
		{
			std::cout << "-----------------------------\n\tLogin Screen\n-----------------------------\n\n";
			std::cout << "Username: ";
			std::cin >> username;
			std::cout << "\nPassword: ";
			std::cin >> password;
			std::cout << "\n";
			if (!checkLogin(accounts, username, password))
			{
				std::cout << "Invalid username and/or password\n\n";
				std::cin.clear();
			}
			else
			{
				std::cout << "Access granted.\n\n";
				loginFlag = false;
			}
		}
		// Main Menu
		std::cout << "-------------------------\n\tMain Menu\n-------------------------\n\n";
		std::cout << "1: View Inventory\n2: Add Product\n3: Edit Inventory\n4: Delete Product\n9: Logout\n\n";

		// Retrieve user input and error check
		bool flag = true;
		unsigned short choice; // Main menu choice
		while (flag)
		{
			std::cout << "What would you like to do? ";
			std::cin >> choice;
			std::cout << "\n";
			if (!std::cin || (choice != VIEW && choice != ADD && choice != EDIT && choice != DELETE 
				&& choice != LOGOUT))
			{
				std::cout << "Invalid input. Try again\n\n";
				std::cin.clear();
			}
			else
			{
				flag = false;
			}
		}

		// React to user input
		// View inventory
		if (choice == VIEW)
		{
			myInventory.printInventory();
		}
		// Add a product
		else if (choice == ADD)
		{
			std::cout << "Enter the name, id, price, and quantity of the product separated by a space. ";
			std::cin >> name >> id >> price >> quantity;
			myInventory.addItem(Product(name, id, price, quantity));

			// Write the data to inventory.txt
			std::ofstream outfile;
			outfile.open("inventory.txt", std::ios::app);
			outfile << name << " " << id << " " << price << " " << quantity << "\n";
			outfile.close();

			std::cout << "Added.\n";
		}
		else if (choice == EDIT)
		{
			// Repeat the edit menu until the user returns to the main menu
			while (true)
			{
				std::cout << "-------------------------\n\tEdit Menu\n-------------------------\n\n";
				std::cout << "1: Change Product Name\n2: Change Product ID\n3: Change Price\n4: Add Quantity\n"
					<< "5: Reduce Quantity\n9: Main Menu\n\n";
				// Retrieve user input and error check for edit menu
				bool editFlag = true;
				unsigned short editChoice;
				while (editFlag)
				{
					std::cout << "What would you like to do? ";
					std::cin >> editChoice;
					std::cout << "\n";
					if (!std::cin || (editChoice != NAME && editChoice != ID && editChoice != PRICE 
						&& editChoice != ADD_QUANTITY && editChoice != REDUCE_QUANTITY 
						&& editChoice != MAIN_MENU))
					{
						std::cout << "Invalid input. Try again\n\n";
						std::cin.clear();
					}
					else
					{
						editFlag = false;
					}
				}

				// React to user input
				bool idFlag = true;
				if (editChoice == MAIN_MENU)
				{
					break;
				}
				else if (editChoice == NAME)
				{
					std::string newName;
					while (idFlag) {
						std::cout << "Enter the product ID and its new name separated by a space. ";
						std::cin >> id >> newName;
						std::cout << "\n";
						idFlag = idCheckFlag(myInventory, id);
					}
					myInventory.getProductByID(id)->setName(newName);
				}
				else if (editChoice == ID)
				{
					unsigned long long newID;
					while (idFlag)
					{
						std::cout << "Enter the product ID and its new ID separated by a space. ";
						std::cin >> id >> newID;
						std::cout << "\n";
						idFlag = idCheckFlag(myInventory, id);
					}
					myInventory.getProductByID(id)->setID(newID);
				}
				else if (editChoice == PRICE)
				{
					float price;
					while (idFlag)
					{
						std::cout << "Enter the product ID and its new price separated by a space. ";
						std::cin >> id >> price;
						std::cout << "\n";
						idFlag = idCheckFlag(myInventory, id);
					}
					myInventory.getProductByID(id)->setPrice(price);
				}
				else if (editChoice == ADD_QUANTITY)
				{
					unsigned int amountToAdd;
					while (idFlag)
					{
						std::cout << "Enter the product ID and the amount to add separated by a space. ";
						std::cin >> id >> amountToAdd;
						std::cout << "\n";
						idFlag = idCheckFlag(myInventory, id);
					}
					myInventory.getProductByID(id)->setQuantity(
						myInventory.getProductByID(id)->getQuantity() + amountToAdd);
				}
				else if (editChoice == REDUCE_QUANTITY)
				{
					unsigned int amountToReduce;
					while (idFlag)
					{
						std::cout << "Enter the product ID and the amount to reduce separated by a space. ";
						std::cin >> id >> amountToReduce;
						std::cout << "\n";
						idFlag = idCheckFlag(myInventory, id);
					}
					myInventory.getProductByID(id)->setQuantity(
						myInventory.getProductByID(id)->getQuantity() - amountToReduce);
				}
				// Update inventory.txt
				writeData(myInventory);
				std::cout << "Updated.\n";
			}
		}
		// Remove a product
		else if (choice == DELETE)
		{
			bool idFlag = true;
			while (idFlag)
			{
				std::cout << "Enter the id of the product you want to delete. ";
				std::cin >> id;
				std::cout << "\n";
				idFlag = idCheckFlag(myInventory, id);
			}
			myInventory.removeItem(id);

			// Remove the product from the inventory.txt
			writeData(myInventory);
			std::cout << "Deleted.\n";
		}
		else if (choice == LOGOUT)
		{
			std::cout << "Logging out...\n";
			continue;
		}
	}
	return 0;
}

// Writes inventory data to inventory.txt
void writeData(Inventory &rInventory)
{
	std::ofstream outfile;
	outfile.open("inventory.txt");
	for (int i = 0; i < rInventory.getSize(); i++)
	{
		outfile << rInventory.getProduct(i).getName() << " " << rInventory.getProduct(i).getID()
			<< " " << rInventory.getProduct(i).getPrice() << " " << rInventory.getProduct(i).getQuantity()
			<< "\n";
	}
	outfile.close();
}

// Checks to see if the product ID exists
// O(n) time
bool idCheck(Inventory &rInventory, unsigned long long idToCheck)
{
	for (int i = 0; i < rInventory.getSize(); i++)
	{
		if (rInventory.getProduct(i).getID() == idToCheck)
		{
			return true;
		}
	}
	return false;
}

// Error message for an invalid ID.
void idErrorMessage(unsigned long long idToCheck)
{
	std::cout << "ID: " << idToCheck << " does not exist. Try again.\n\n";
	std::cin.clear();
}

// Returns a boolean baesd on whether or not the id exists
// Returns an error message if the id does not exist and clears the input stream
bool idCheckFlag(Inventory &rInventory, unsigned long long idToCheck)
{
	if (!idCheck(rInventory, idToCheck))
	{
		idErrorMessage(idToCheck);
		std::cin.clear();
		return true;
	}
	else
	{
		return false;
	}
}

// Checks to see if login information is valid
// O(n) time
bool checkLogin(std::vector<Account> &rAccounts, std::string username, std::string password)
{
	for (int i = 0; i < size(rAccounts); i++)
	{
		if (rAccounts[i].getUsername() == username && rAccounts[i].getPassword() == password)
		{
			return true;
		}
	}
	return false;
}