//
// Created by greg on 19.12.23.
//

#include "../headers/ArgumentParser.h"

GameMode ArgumentParser::getMode(char *str)  {
    if (std::strcmp(str, "easy") == 0) return GameMode::EASY;
    if (std::strcmp(str, "medium") == 0) return GameMode::MEDIUM;
    if (std::strcmp(str, "hard") == 0) return GameMode::HARD;
    return GameMode::BAD;
}
