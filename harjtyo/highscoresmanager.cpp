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
			highscores.insert(make_pair(score, name));
		}

		file.close();
	}
}
void HighscoresManager::newScore(string name, int score) {
	// Still room in list so insert directly
	if (highscores.size() < MAX_SIZE) {
		highscores.insert(make_pair(score, name));
		writeAllToFile();
	}
	// Check if the new score is better
	else {
		multimap<int, string>::const_iterator itr = highscores.begin();
		if (itr->first < score) {
			highscores.erase(itr);
			highscores.insert(make_pair(score, name));
		}
	}
}
void HighscoresManager::writeAllToFile() {
	ios_base::openmode openflags = ios_base::binary;

	ofstream file(filepath, openflags);
	if (file.is_open()) {
		for (multimap<int, string>::const_iterator itr = highscores.begin(); itr != highscores.end(); ++itr) {
			// Convert string to char array for writing to binary file
			char cName[128];
			strncpy_s(cName, itr->second.c_str(), sizeof(cName));
			cName[sizeof(cName) - 1] = 0;

			file.write(cName, sizeof(cName));
			file.write((char*)&itr->first, sizeof(int));
		}

		file.close();
	}
}
void HighscoresManager::displayScoresInConsole() {
	for (multimap<int, string>::const_iterator itr = highscores.begin(); itr != highscores.end(); ++itr) {
		cout << itr->second << ": " << itr->first << endl;
	}
}