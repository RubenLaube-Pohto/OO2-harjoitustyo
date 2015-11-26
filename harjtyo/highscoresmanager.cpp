#include "highscoresmanager.h"
#include <fstream>
#include <iostream>

HighscoresManager::HighscoresManager() {
	this->filepath = "";
}
HighscoresManager::HighscoresManager(string file) {
	this->filepath = file;
	loadFromFile();
}
void HighscoresManager::loadFromFile() {
	int score;
	char cName[128];

	ios_base::openmode openflags = ios_base::binary;

	ifstream file(filepath, openflags);
	if (file.is_open()) {
		while (file.peek() != EOF) {
			file.read(cName, sizeof(cName));
			file.read((char*)&score, sizeof(int));
			string name(cName);
			highscores.insert(make_pair(name, score));
		}
		file.close();
	}
}
void HighscoresManager::newScore(string name, int score) {
	if (highscores.size() < MAX_SIZE) {
		highscores.insert(make_pair(name, score));
		writeAllToFile();
	}
	else {
		// TODO add if new score higher than previous worst
	}
	// TODO sort from highest to lowest, could work by just changin key <-> value as multimap is sorted auto by key
}
void HighscoresManager::writeAllToFile() {
	// No filepath set; do nothing
	if (filepath == "")
		return;

	ios_base::openmode openflags = ios_base::binary;

	ofstream file(filepath, openflags);
	if (file.is_open()) {
		for (multimap<string, int>::const_iterator itr = highscores.begin(); itr != highscores.end(); ++itr) {
			// Convert string to char array for writing to binary file
			char cName[128];
			strncpy_s(cName, itr->first.c_str(), sizeof(cName));
			cName[sizeof(cName) - 1] = 0;

			file.write(cName, sizeof(cName));
			file.write((char*)&itr->second, sizeof(int));
		}

		file.close();
	}
}
void HighscoresManager::displayScoresInConsole() {
	for (multimap<string, int>::const_iterator itr = highscores.begin(); itr != highscores.end(); ++itr) {
		cout << itr->first << ": " << itr->second << endl;
	}
}