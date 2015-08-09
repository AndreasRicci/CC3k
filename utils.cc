#include <cstdlib>
#include <ctime>
#include <string>
#include "utils.h"
#include "constants.h"

using namespace std;

int randomIntInRange(int low, int high) {
    return (low + (rand() % (high - low + 1)));
}

int damage(int attack, int defence, int modifier){
    // Modifier is normally 100.
    // It represents percentage of defence used to calculate damage.

    // Ceiling calculation: Avoiding floats
    int denominator = 100 + defence;
    int percentage = (modifier + denominator - 1) / denominator;

    return attack * percentage;
}

int directionToInt(string direction){
    if (direction == "nw" || direction == ":q"){
        return NW;
    }
    else if (direction == "no" || direction == ":w"){
        return NO;
    }
    else if (direction == "ne" || direction == ":e"){
        return NE;
    }
    else if (direction == "we" || direction == ":a"){
        return WE;
    }
    else if (direction == "ea" || direction == ":d"){
        return EA;
    }
    else if (direction == "sw" || direction == ":z"){
        return SW;
    }
    else if (direction == "so" || direction == ":x"){
        return SO;
    }
    else if (direction == "se" || direction == ":c"){
        return SE;
    }
    else{
        return ERROR;
    }
}


int directionToInt(char direction){
    if (direction == 'q'){
        return NW;
    }
    else if (direction == 'w'){
        return NO;
    }
    else if (direction == 'e'){
        return NE;
    }
    else if (direction == 'a'){
        return WE;
    }
    else if (direction == 'd'){
        return EA;
    }
    else if (direction == 'z'){
        return SW;
    }
    // Some people miss WASD
    else if (direction == 'x' || direction == 's'){
        return SO;
    }
    else if (direction == 'c'){
        return SE;
    }
    else{
        return ERROR;
    }
}

int potionToInt(string shorthand){
    if (shorthand == "RH"){
        return RH;
    }
    else if (shorthand == "PH"){
        return PH;
    }
    else if (shorthand == "BA"){
        return BA;
    }
    else if (shorthand == "WA"){
        return WA;
    }
    else if (shorthand == "BD"){
        return BD;
    }
    else if (shorthand == "WD"){
        return WD;
    }
    else{
        return ERROR;
    }
}

int potionEffect(int currentStat, int change, int multiplier, int upperBound){
    int afterPotion = currentStat + change * multiplier / 100;

    if (afterPotion <= 0){
        return 0;
    }
    else if (upperBound > 0 && afterPotion > upperBound){
        return upperBound;
    }
    else{
        return afterPotion;
    }
}

string getBartition(int numer, int denom, int width, string text, string patternFull, string patternEmpty, int offset){
    // Bartition = Bar Partition
    string bartition = "";

    int fillWidth;
    if (numer >= denom){
        fillWidth = width;
    }
    else if (numer <= 0){
        fillWidth = 0;
    }
    else{
        fillWidth = width * (numer - 1 ) / denom + 1;
    }

    // Writing first section (Full)
    int index;
    int textIndex = 0;
    bartition+= patternFull;
    for (index = 0; index < fillWidth && index < width; index++){
        if (offset > 0 || textIndex == text.length()){
            offset--;
            bartition+= " ";
        }
        else{
            bartition+= text.at(textIndex);
            textIndex++;
        }
    }
    // Writing second section (Empty)
    bartition+= patternEmpty;
    for (; index < width; index++){
        if (offset > 0 || textIndex == text.length()){
            offset--;
            bartition+= " ";
        }
        else{
            bartition+= text.at(textIndex);
            textIndex++;
        }
    }
    bartition+= "\e[0m";
    return bartition;
}

void setTextColour(int colour){

}

void endTextColour(){
    
}