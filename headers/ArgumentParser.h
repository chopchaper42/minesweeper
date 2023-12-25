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
    GameMode getMode();
    char* getCmdOption(const std::string & option);
    bool cmdOptionExists(const std::string& option);
    ArgumentParser(int argc, char** argv);
private:
    int argc;
    char** argv;
};


#endif //MINESWEEPER_ARGUMENTPARSER_H
