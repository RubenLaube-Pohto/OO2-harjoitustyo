#ifndef HIGHSCORESMANAGERH
#define HIGHSCORESMANAGERH

#include <string>
#include <map>

using namespace std;

class HighscoresManager {
public:
	HighscoresManager();
	HighscoresManager(string);
	void newScore(string, int);
	void displayScoresInConsole();
private:
	multimap<int, string> highscores;
	const unsigned int MAX_SIZE = 5;
	string filepath;

	void loadFromFile();
	void writeAllToFile();
};

#endif