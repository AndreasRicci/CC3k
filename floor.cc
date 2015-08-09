#include <vector>
#include <iostream>
#include <fstream>
#include "floor.h"
#include "cell.h"
#include "chamber.h"
#include "constants.h"
#include "direction.h"

using namespace std;

const string floorFile = "floor.txt";        // Layout of floor

// Floors are currently hardcoded
Floor::Floor() {
    char layoutCopy[ROWS][COLMS]; // This is used during Chamber creation
    
    // Set up all of the Cells
    ifstream in(floorFile.c_str());
    for(int r = 0; r < ROWS; ++r) {
        string line;
        getline(in, line);
        
        for(int c = 0; c < line.length(); ++c) {
            char ch = line.at(c);
            if (ch != '|' && ch != '-' && ch != '.' && ch != '#' && ch != ' ' && ch != '+')
                ch = '.';
            cells[r][c] = new Cell(ch);
            #ifdef DLC
            if (r == 0 || c == 0 || r == ROWS - 1 || c == line.length() - 1){
                cells[r][c]->setEdge(true);
            }
            #endif
            layoutCopy[r][c] = ch;
        }
    }
    
    // Create the Chambers
    for(int i = 0; i < CHAMBERS; ++i) {
        chambers[i] = new Chamber();
        floodFillChamber(&layoutCopy, chambers[i]);
    }
}

Floor::~Floor() {
    // Delete all Chambers
    for(int i = 0; i < CHAMBERS; ++i) {
        if(chambers[i] != NULL) {
            delete chambers[i];
        }
    }
    
    // Delete all Cells
    for(int r = 0; r < ROWS; ++r) {
        for(int c = 0; c < COLMS; ++c) {
            if(cells[r][c] != NULL) {
                delete cells[r][c];
            }
        }
    }
}

void Floor::floodFillHelper(char (*layout)[ROWS][COLMS], Chamber *chamber, int r, int c) {
    if((*layout)[r][c] == DISPLAY_CELLS[FLOOR]) {
        chamber->addCell(cells[r][c]);                  // Add the Cell to the Chamber
        (*layout)[r][c] = 'V';                          // Mark as Visited
        for(int i = 0; i < maxDirs; ++i) {
            Direction dir = dirs[i];                    // Which direction are we looking for another Floor tile in?
            int neighbourRow = r + dir.northSouth;
            int neighbourCol = c + dir.eastWest;
            
            // Check for a valid neighbour in this direction
            if(neighbourRow >= 0 && neighbourRow < ROWS && neighbourCol >= 0 && neighbourCol < COLMS) {
                floodFillHelper(layout, chamber, neighbourRow, neighbourCol);      // Recurse to find more Floor tiles in this Chamber
            }
        }
    }
}

void Floor::floodFillChamber(char (*layout)[ROWS][COLMS], Chamber *chamber) {
    for(int r = 0; r < ROWS; ++r) {
        for(int c = 0; c < COLMS; ++c) {
            if((*layout)[r][c] == DISPLAY_CELLS[FLOOR]) {   // Find the first Floor tile (denoting a Chamber)
                floodFillHelper(layout, chamber, r, c);
                return;
            }
        }
    }
}

void Floor::clearFloor() {
    for(int r = 0; r < ROWS; ++r) {
        for(int c = 0; c < COLMS; ++c) {
            if(cells[r][c] != NULL) {
                cells[r][c]->setOccupant(NULL);     // Setting occupant to NULL removes previous occupant
            }
        }
    }
}

Cell *Floor::getCell(int row, int col) {
    return cells[row][col];
}

Chamber *Floor::getChamber(int chamberNumber) {
    return chambers[chamberNumber - 1];
}

bool Floor::hasConnections(){
    return connected;
}

void Floor::connect(){
    connected = true;
}

ostream &operator<<(ostream &out, Floor &floor) {
    // Outputting a Floor involves outputting each Cell line by line
    for(int r = 0; r < ROWS; ++r) {
        for(int c = 0; c < COLMS; ++c) {
            if(floor.cells[r][c] != NULL) {
                out << *(floor.cells[r][c]);
            }
        }
        out << endl;
    }
    
    return out;
}
