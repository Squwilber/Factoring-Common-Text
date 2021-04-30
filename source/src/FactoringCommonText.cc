/*
	Authors: Trevor Dawideit and Gousemoodhin Nadif
	cite: filesystem library, https://en.cppreference.com/w/cpp/filesystem/directory_iterator
	cite: findCaseInsensitive function, https://thispointer.com/implementing-a-case-insensitive-stringfind-in-c/
	I pledge my honor that I have abided by the Stevens Honor System.
*/
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>

using namespace std;

size_t findCaseInsensitive(string data, string toSearch, size_t pos = 0) {
	// Convert complete given String to lower case
	transform(data.begin(), data.end(), data.begin(), ::tolower);
	// Convert complete given Sub String to lower case
	transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
	// Find sub string in given string
	return data.find(toSearch, pos);
}

class eBook {
private:
	string filename;
	vector<string> topBP;
	vector<string> bottomBP;
	string topBPFile;
	string bottomBPFile;
public:
	eBook(string filename) : filename(filename) { // O(number of lines in the file)
		getboilerplate(filename); // O(number of lines in the file)
		topBPFile = "";
		bottomBPFile = "";
	}

	void getboilerplate(string filename) { // O(number of lines in the file)
		ifstream file(filename);
		string line = "";
		bool isBoilerplate = true;
		bool isTopBP = true;
		getline(file, line);
		if(findCaseInsensitive(line, "The Project Gutenberg eBook") == string::npos) { // Skip first line if it mentions the title of the book
			topBP.push_back(line);
		}
		while(getline(file, line)) {	// O(number of lines in the file)
			if(findCaseInsensitive(line, "The Project Gutenberg eBook") != string::npos) { // Skip first line if it mentions the title of the book
				continue;
			}
			if(findCaseInsensitive(line, "Title: ") != string::npos) { // "Title: " denotes the end of the top boilerplate
				isBoilerplate = false;
			}
			else if(findCaseInsensitive(line, "START: FULL LICENSE") != string::npos) { // "Title: " denotes the start of the bottom boilerplate
				isBoilerplate = true;
				isTopBP = false;
			}

			if(isBoilerplate) { // If line is part of the boilerplate, add it to the vector.
				if(isTopBP) {
					topBP.push_back(line);
				} else {
					bottomBP.push_back(line);
				}
			}
		}
	}

	void createTopBP(string filename) { // O(size of topBP)
		ofstream f(filename);
		for(auto i: topBP) {
			f << i << endl;
		}
		f.close();
	}
	void createBottomBP(string filename) { // O(size of bottomBP)
		ofstream f(filename);
		for(auto i: bottomBP) {
			f << i << endl;
		}
		f.close();
	}

	friend bool alreadyExistsTop(eBook check, vector<eBook>& eBooks, string filename) { // O(size of eBooks * size of topBP)
		for(auto b: eBooks) { // O(size of eBooks)
			if(check.topBP == b.topBP) { // Compares vectors, returns true if both have same number of elements and each element is the same. O(size of topBP)
				check.topBPFile = b.topBPFile;
				return true;
			}
		}
		check.topBPFile = filename;
		return false;
	}
	friend bool alreadyExistsBottom(eBook check, vector<eBook>& eBooks, string filename) { // O(size of eBooks * size of bottomBP)
		for(auto b: eBooks) { // O(size of eBooks)
			if(check.bottomBP == b.bottomBP) { // Compares vectors, returns true if both have same number of elements and each element is the same. O(size of bottomBP)
				check.bottomBPFile = b.bottomBPFile;
				return true;
			}
		}
		check.bottomBPFile = filename;
		return false;
	}
};

int main()
{
	int topCount = 1, bottomCount = 1;
	string path = "..\\..\\projectGutenberg";
	vector<eBook> eBooks;
	// Create directory to store boilerplates
	filesystem::create_directory(".\\out");
	//iterate over every file in the given path
	for (const auto& entry : filesystem::directory_iterator(path)) { // O(number of files in the directory)
		// Open document
		string filename = entry.path().string(); // Convert filepath to string
		eBook eB(filename);
		// Check if boilerplate already exists
		string topName = ".\\out\\topBP" + to_string(topCount) + ".txt";
		if(!alreadyExistsTop(eB, eBooks, topName)) {
			// Create new file with top boilerplate text
			eB.createTopBP(topName);
			topCount++;
		}
		string bottomName = ".\\out\\bottomBP" + to_string(bottomCount) + ".txt";
		if(!alreadyExistsBottom(eB, eBooks, bottomName)) {
			// Create new file with bottom boilerplate text
			eB.createBottomBP(bottomName);
			bottomCount++;
		}
		// Replace bp in document with link to bp file.

		eBooks.push_back(eB);
	}
}