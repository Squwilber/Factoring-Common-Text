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
	string filePath;
	string filename;
	vector<string> topFileContent; // Everything before topBP
	vector<string> topBP;
	vector<string> mainFileContent; // Everything inbetween topBP and bottomBP
	vector<string> bottomBP;
	string topBPFilename;
	string bottomBPFilename;
public:
	eBook(string filePath, string filename) : filePath(filePath), filename(filename) { // O(number of lines in the file)
		getboilerplate(filePath); // O(number of lines in the file)
		topBPFilename = "";
		bottomBPFilename = "";
	}

	void getboilerplate(const string filePath) { // O(number of lines in the file)
		ifstream file(filePath);
		string line = "";
		int loc = 0;
		int bottomBPCount = 6;
		bool startbottomBPCountdown = false;
		while(getline(file, line)) {	// O(number of lines in the file)
			if (!line.empty() && line.find_first_not_of(' ') != string::npos) { // Skip blank lines
				addToLocation(line, loc);
				if(loc == 0 && findCaseInsensitive(line, "The Project Gutenberg eBook") != string::npos && findCaseInsensitive(line, "div") != string::npos) { // Marks start of topBP
					loc++;
				} else if(loc == 1 && findCaseInsensitive(line, "</div>") != string::npos) { // Marks end of topBP
					loc++;
				} else if(loc == 2 && findCaseInsensitive(line, "*** END OF THE PROJECT GUTENBERG") != string::npos) { // Marks end of topBP
					startbottomBPCountdown = true;
				} else if(startbottomBPCountdown) {
					bottomBPCount--;
					if(bottomBPCount == 0) {
						loc++;
						startbottomBPCountdown = false;
					}
				}
			}
		}
	}

	void addToLocation(const string &line, const int &loc) {
		switch(loc) {
			case 0:
				topFileContent.push_back(line);
				break;
			case 1:
				topBP.push_back(line);
				break;
			case 2:
				mainFileContent.push_back(line);
				break;
			case 3:
				bottomBP.push_back(line);
				break;
		}
	}

	void createTopBP(const string &topBPFilename) { // O(size of topBP)
		ofstream f(".\\out" + topBPFilename);
		f << "<html><head></head><body>" << endl;
		for(auto i : topBP) {
			f << i << endl;
		}
		f << "</body></html>";
		f.close();
	}

	void createBottomBP(const string &bottomBPFilename) { // O(size of bottomBP)
		ofstream f(".\\out" + bottomBPFilename);
		f << "<html><head></head><body>" << endl;
		for(auto i : bottomBP) {
			f << i << endl;
		}
		f.close();
	}

	friend bool alreadyExistsTop(eBook &check, vector<eBook> &eBooks, string newFilename) { // O(size of eBooks * size of topBP)
		for(auto b : eBooks) { // O(size of eBooks)
			if(check.topBP == b.topBP) { // Compares vectors, returns true if both have same number of elements and each element is the same. O(size of topBP)
				check.topBPFilename = b.topBPFilename;
				return true;
			}
		}
		check.topBPFilename = newFilename;
		return false;
	}
	friend bool alreadyExistsBottom(eBook &check, vector<eBook> &eBooks, string newFilename) { // O(size of eBooks * size of bottomBP)
		for(auto b : eBooks) { // O(size of eBooks)
			if(check.bottomBP == b.bottomBP) { // Compares vectors, returns true if both have same number of elements and each element is the same. O(size of bottomBP)
				check.bottomBPFilename = b.bottomBPFilename;
				return true;
			}
		}
		check.bottomBPFilename = newFilename;
		return false;
	}

	void createFile(const string &mainFilename) {
		ofstream f(mainFilename);
		for(auto i : topFileContent) {
			f << i << endl;
		}
		f << "<div><a href = \"." + topBPFilename + "\">Terms of use</a></div>" << endl;
		for(auto i : mainFileContent) {
			f << i << endl;
		}
		f << "<div><a href = \"." + bottomBPFilename + "\">Full License</a></div>" << endl;
		f << "</body></html>";
		f.close();
	}

};

void copyDir(string path, string out) {
	for (const auto& entry : filesystem::directory_iterator(path)) {
		if(filesystem::is_directory(entry.path())) {
			copyDir(entry.path().string(), out + entry.path().filename().string());
		}
		else {
			ofstream(out + "\\" +  entry.path().filename().string(), ios::binary) << ifstream(entry.path().string(), ios::binary).rdbuf();
		}
	}
}

int main()
{
	int topCount = 1, bottomCount = 1;
	string path = "..\\..\\projectGutenberg";
	vector<eBook> eBooks;
	// Create directory to store boilerplates
	filesystem::create_directory(".\\out");
	filesystem::create_directory(".\\out\\bps");
	//iterate over every file in the given path
	for (const auto& entry : filesystem::directory_iterator(path)) { // O(number of files in the directory)
		// Open document
		string filePath = entry.path().string(); // Convert filepath to string
		string filename = entry.path().filename().string();
		if(findCaseInsensitive(filename, ".html") != string::npos) {
			eBook eB(filePath, filename);
			// Check if boilerplate already exists
			string topName = "\\bps\\topBP" + to_string(topCount) + ".html";
			if(!alreadyExistsTop(eB, eBooks, topName)) {
				// Create new file with top boilerplate text
				eB.createTopBP(topName);
				topCount++;
			}
			string bottomName = "\\bps\\bottomBP" + to_string(bottomCount) + ".html";
			if(!alreadyExistsBottom(eB, eBooks, bottomName)) {
				// Create new file with bottom boilerplate text
				eB.createBottomBP(bottomName);
				bottomCount++;
			}
			// Replace bp in document with link to bp file.
			eB.createFile(".\\out\\" + filename);
			eBooks.push_back(eB);
		} else {
			// Copy html folder if needed
			filesystem::create_directory(".\\out\\" + filename);
			copyDir(filePath, ".\\out\\" + filename);
			
		}
	}
}