#ifndef CONSTANTSH
#define CONSTANTSH

#include <string>;

const std::string TITLE = "Harkkarainen";
const std::string FONT_FILE = "Fonts\\arial.ttf";
const std::string BG_TEXTURE_FILE = "Textures\\background.png";
const std::string PLAYER_TEXTURE_FILE = "Textures\\mech.png";
const std::string ENEMY_TEXTURE_FILE = "Textures\\enemy.png";
const std::string CROSSHAIR_TEXTURE_FILE = "Textures\\crosshair.png";

const std::string GAMEOVER_AUDIO = "Audio\\gameover.wav";
const std::string PLAYER_DEATH_AUDIO = "Audio\\pain.wav";
const std::string BG_MUSIC = "Audio\\bass-or-die-loop.wav";
const std::string PLAYER_SHOOT_AUDIO = "Audio\\flaunch.wav";
const std::string ENEMY_SHOOT_AUDIO = "Audio\\slimeball.wav";

const std::string HIGHSCORES_FILE = "highscores.dat";

const float MOVE_SPEED = 5.0f;
const int WIDTH = 800;
const int HEIGTH = 600;
const float GROUND_WIDTH = 256.0f * 4;
const float GROUND_HEIGTH = 256.0f * 4;
const float ENEMY_SHOOTING_DISTANCE = 300.0f;
const float CAMERA_MAX_OFFSET = 50.0f;

const bool DEBUG = true;

#endif