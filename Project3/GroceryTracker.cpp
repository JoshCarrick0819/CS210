#include "GroceryTracker.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

// reads the grocery list from CS210_Project_Three_Input_File.txt
void GroceryTracker::readGroceryData()
{
	try
	{
		m_freqMap.clear(); // clear map 

		std::ifstream inFile("CS210_Project_Three_Input_File.txt", std::ios::in); // open file read only
		if (!inFile) // if file does not exist or encounters a problem opening
		{
			throw std::runtime_error("Could not open input file.");
		}

		std::string currItem;
		while (std::getline(inFile, currItem))
		{
			if (currItem.empty())
			{
				throw std::runtime_error("Encountered empty line in input file.");
			}
			m_freqMap[currItem]++; // will create new entry if one does not exist, then increments count by one
		}
		inFile.close(); // close the file
		createBackupFile();
	}
	catch (const std::exception& e) // if exception is thrown exit the program
	{
		std::cerr << "Fatal Error: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

// create the frequency.dat backup file for the grocery data
void GroceryTracker::createBackupFile()
{
	std::ofstream outFile("frequency.dat", std::ios::out); // file open for write only

	if (outFile.is_open()) {

		for (auto it = m_freqMap.begin(); it != m_freqMap.end(); ++it) // iterate through the map
		{
			outFile << it->first << " " << it->second << std::endl;

		}


		outFile.close(); // close outfile
		std::cout << "Backup file written successfully!" << std::endl;
	}
	else { // file not opened or encountered an issue when opening
		std::cerr << "Error opening file: frequency.dat\n";
	}

}

// serves as main menu UI for the application
void GroceryTracker::mainMenu()
{
	// menu text
	std::cout << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "	1: Search for Item" << std::endl;
	std::cout << "	2: Print Frequency List" << std::endl;
	std::cout << "	3: Print Frequency Histogram" << std::endl;
	std::cout << "	4: Exit" << std::endl << std::endl;

	std::cout << "Enter your selection: ";

	// read in selection
	int selection;
	try // error is thrown if type is not an int
	{
		if (!(std::cin >> selection))
		{
			throw std::runtime_error("Invalid input! Expected an int.");
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		std::cin.clear(); // Clear error flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
	}
	switch (selection)
	{
	case 1:
		searchFreq();
		break;
	case 2:
		printFreqList();
		break;
	case 3:
		printHistogram();
		break;
	case 4:
		exit(0);
	}
}

// search the list for a item and return the frequency
void GroceryTracker::searchFreq()
{
	std::string searchTerm;
	try // maybe redundant try/catch but kept to ensure correct input
	{
		std::cout << std::endl;
		std::cout << "Enter Item to search for: ";

		if (!(std::cin >> searchTerm)) // should never trigger unless cin is corrupted 
		{
			throw std::runtime_error("Invalid input! Expected a string.");
		}
		if (searchTerm.empty()) { // cin >> should always extract at least 1 char
			throw std::runtime_error("String cannot be empty.");
		}

	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		std::cin.clear(); // Clear error flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
	}


	auto it = m_freqMap.find(searchTerm); // Search for the key

	if (it != m_freqMap.end()) {
		// Key found
		std::cout << searchTerm << " count: " << it->second << std::endl;
	}
	else {
		// Key not found
		std::cout << "Item \"" << searchTerm << "\" not found!" << std::endl;
	}
	// Clear any leftover input
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << std::endl << "Press Enter to Continue...";
	std::cin.get();
}

// prints the list of all frequencies
void GroceryTracker::printFreqList()
{
	std::cout << std::endl;
	for (auto it = m_freqMap.begin(); it != m_freqMap.end(); ++it)
	{
		std::cout << std::setw(20) << it->first << " " << it->second << std::endl;
	}

	// Clear any leftover input
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << std::endl << "Press Enter to Continue...";
	std::cin.get();
}

// print all frequencies in histogram format
void GroceryTracker::printHistogram()
{
	std::cout << std::endl;
	for (auto it = m_freqMap.begin(); it != m_freqMap.end(); ++it)
	{
		std::cout << std::setw(20) << it->first << " ";
		for (int i = 0; i < it->second; ++i)
		{
			std::cout << "*";
		}
		std::cout << std::endl;
	}
	// Clear any leftover input
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << std::endl << "Press Enter to Continue...";
	std::cin.get();
}