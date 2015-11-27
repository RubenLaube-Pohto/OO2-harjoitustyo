#ifndef HIGHSCORESMANAGERH
#define HIGHSCORESMANAGERH

#include <SFML\Graphics\Text.hpp>
#include <string>
#include <map>

using namespace std;

class HighscoresManager : public sf::Text {
public:
	HighscoresManager(string);
	void newScore(string, int);
	int getWorstScore();
private:
	multimap<int, string> highscores;
	const unsigned int MAX_SIZE = 5;
	string filepath;

	void loadFromFile();
	void writeAllToFile();
	string getScoresString();
};

#endif