#ifndef CONSTANTSH
#define CONSTANTSH

#include <string>;

const std::string TITLE = "Harkkarainen";
const std::string FONT_FILE = "Fonts\\arial.ttf";
const std::string BG_TEXTURE_FILE = "Textures\\background.png";
const std::string PLAYER_TEXTURE_FILE = "Textures\\mech.png";
const std::string ENEMY_TEXTURE_FILE = "Textures\\enemy.png";
const std::string GAMEOVER_AUDIO = "Audio\\gameover.wav";
const std::string PLAYER_DEATH_AUDIO = "Audio\\pain.wav";
const std::string BG_MUSIC = "Audio\\bass-or-die-loop.wav";

const float MOVE_SPEED = 5.0f;
const int WIDTH = 800;
const int HEIGTH = 600;
const float GROUND_WIDTH = 256.0f * 4;
const float GROUND_HEIGTH = 256.0f * 4;

const bool DEBUG = true;

#endif