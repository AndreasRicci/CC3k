#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

int randomIntInRange(int low = 0, int high = 7);

int damage(int attack, int defence, int modifier = 100);

int directionToInt(std::string direction);

int directionToInt(char direction);

int potionToInt(std::string shorthand);

int potionEffect(int currentStat, int change, int multiplier=100, int upperBound=0);

std::string getBartition(int numer, int denom, int width, std::string text, std::string patternFull = "\e[1;30;42m", std::string patternEmpty = "\e[30;41m", int offset=0);

void setTextColour(int colour);
void endTextColour();
//void setBackgroundColour(int colour);
//void endBackgroundColour();

#endif
