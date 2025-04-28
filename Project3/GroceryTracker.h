#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H

#include <unordered_map>
#include <iostream>

// tracks and prints items and their frequencies
class GroceryTracker
{
public:

	void readGroceryData();

	void mainMenu();

	void searchFreq();

	void printFreqList();

	void printHistogram();

private:

	void createBackupFile();

	std::unordered_map<std::string, int> m_freqMap;

};

#endif // !GROCERY_TRACKER_H