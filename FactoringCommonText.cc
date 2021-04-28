/*
	Authors: Trevor Dawideit and Gousemoodhin Nadif
	cite: filesystem library, https://en.cppreference.com/w/cpp/filesystem/directory_iterator
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

size_t findCaseInsensitive(string data, string toSearch, size_t pos = 0) { // Cite: https://thispointer.com/implementing-a-case-insensitive-stringfind-in-c/
	// Convert complete given String to lower case
	transform(data.begin(), data.end(), data.begin(), ::tolower);
	// Convert complete given Sub String to lower case
	transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
	// Find sub string in given string
	return data.find(toSearch, pos);
}

int main()
{
	string path = ".\\Project_Gutenberg";
	for (const auto& entry : filesystem::directory_iterator(path)) { //iterates over every file in the given path
		// Open document
		string filename = entry.path().string(); // Convert filepath to string
		cout << filename << endl;
		ifstream file(filename); // Open file for processing

		// Find the top and bottom boilerplates
		string line = "";
		bool isBoilerplate = true;
		vector<string> boilerplate;
		while(getline(file, line)) {
			if(findCaseInsensitive(line, "The Project Gutenberg eBook") != string::npos) { // Skip first line if it mentions the title of the book
				continue;
			}
			if(findCaseInsensitive(line, "Title: ") != string::npos) { // "Title: " denotes the end of the top boilerplate
				isBoilerplate = false;
			}
			else if(findCaseInsensitive(line, "START: FULL LICENSE") != string::npos) { // "Title: " denotes the start of the bottom boilerplate
				isBoilerplate = true;
			}

			if(isBoilerplate) { // if line is part of the boilerplate, add it to the vector.
				boilerplate.push_back(line);
			}
		}

		// Check if boilerplate already exists

		// If no: Create a new file with the boilerplate

		// Replace bp in document with link to bp file.
	}
}