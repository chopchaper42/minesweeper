//
// Created by greg on 19.12.23.
//

#ifndef MINESWEEPER_ARGUMENTPARSER_H
#define MINESWEEPER_ARGUMENTPARSER_H

#include <cstring>
#include <string>
#include "GameMode.h"

class ArgumentParser {
public:
    GameMode getMode(char* str);
};


#endif //MINESWEEPER_ARGUMENTPARSER_H
