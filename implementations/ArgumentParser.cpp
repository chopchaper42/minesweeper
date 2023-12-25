//
// Created by greg on 19.12.23.
//

#include "../headers/ArgumentParser.h"
#include <algorithm>
#include <stdexcept>

char* ArgumentParser::getCmdOption(const std::string & option)
{
    char** begin = argv;
    char** end = argv + argc;
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool ArgumentParser::cmdOptionExists(const std::string& option)
{
    return std::find(argv, argv+argc, option) != argv+argc;
}

GameMode ArgumentParser::getMode()  {
    if (!cmdOptionExists("--mode"))
        throw std::invalid_argument("--mode argument with options <easy, medium or hard> needed for running the program");

    char *str = getCmdOption("--mode");
        
    if (std::strcmp(str, "easy") == 0) return GameMode::EASY;
    if (std::strcmp(str, "medium") == 0) return GameMode::MEDIUM;
    if (std::strcmp(str, "hard") == 0) return GameMode::HARD;
    throw std::invalid_argument("--mode argument can only accept <easy, medium or hard> options.");;
}

ArgumentParser::ArgumentParser(int argc, char **argv) {
    this->argc = argc;
    this->argv = argv;
}

