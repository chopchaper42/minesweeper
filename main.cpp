#include <iostream>
#include <cstring>
#include <ctime>
#include <vector>
#include "headers/Game.h"
#include "headers/Cell.h"
#include "headers/GameMode.h"
#include "headers/CellFactory.h"
#include "headers/ArgumentParser.h"

int main(int argc, char** argv) {
    ArgumentParser parser;
    Game * game;

    switch(parser.getMode(argv[1])) {
        case GameMode::BAD:
            std::cout << "Bad argument! Only easy, medium or hard are allowed. Was: " << argv[0] << std::endl;
            return -1;
        default:
            game = new Game(parser.getMode(argv[1]));
            break;
    }


    while (game->isPlaying()) {

        game->renderField();

        // TODO: ask for input
        std::string cmd;
        std::string line;
        std::vector<std::string> tokens;

        getline(std::cin, line);

        //tokenize the input line
        for (char c : line) {
            if (c == ' ' || c == '\t') {
                tokens.push_back(cmd);
                cmd = "";
                continue;
            }

            cmd += c;
        }

        tokens.push_back(cmd);

        if (tokens[0] == "quit") {
            game->endGame();
            std::cout << "Game over!" << std::endl;

        } else if (tokens[0] == "mark") {
            // parse coordinates, handle exceptions
            int x, y;

            if (tokens.size() < 3) {
                std::cout << "Should be 3 arguments: command, x, y. Was " << tokens.size() << ". Try again: " << std::endl;
                continue;
            }

            // parse x coordinate
            try {
                x = std::stoi(tokens[1]);
            } catch (const std::invalid_argument& e) {
                std::cout << "Y coordinate should be integer. Try again: " << std::endl;
                continue;
            }

            if (x < 1 || x > game->getColumns()) {
                std::cout << "X coordinate should be in between 1 and " << game->getColumns() << ". Was " << x << ". Try again: " << std::endl;
                continue;
            }

            // parse y coordinate
             try {
                 y = std::stoi(tokens[2]);
             } catch (const std::invalid_argument& e) {
                 std::cout << "Y coordinate should be integer. Try again: " << std::endl;
                 continue;
             }

            if (y < 1 || y > game->getRows()) {
                std::cout << "Y coordinate should be in between 1 and " << game->getRows() << ". Was " << y << ". Try again: " << std::endl;
                continue;
            }

            game->markCell(x, y);


        } else if (tokens[0] == "open") {
            int x, y;

            // parse coordinates, open the cell
            if (tokens.size() < 3) {
                std::cout << "Should be 3 arguments: command, x, y. Was " << tokens.size() << ". Try again: " << std::endl;
                continue;
            }

            // parse x coordinate
            try {
                x = std::stoi(tokens[1]);
            } catch (const std::invalid_argument& e) {
                std::cout << "Y coordinate should be integer. Try again: " << std::endl;
                continue;
            }

            if (x < 1 || x > game->getColumns()) {
                std::cout << "X coordinate should be in between 1 and " << game->getColumns() << ". Was " << x << ". Try again: " << std::endl;
                continue;
            }

            // parse y coordinate
            try {
                y = std::stoi(tokens[2]);
            } catch (const std::invalid_argument& e) {
                std::cout << "Y coordinate should be integer. Try again: " << std::endl;
                continue;
            }

            if (y < 1 || y > game->getRows()) {
                std::cout << "Y coordinate should be in between 1 and " << game->getRows() << ". Was " << y << ". Try again: " << std::endl;
                continue;
            }

            size_t prog_x = x - 1;
            size_t prog_y = y - 1;
            game->openCell(prog_x, prog_y);

            if (!game->isPlaying())
                std::cout << "Game is over!" << std::endl;

        } else if (tokens[0] == "unmark") {
            int x, y;

            if (tokens.size() < 3) {
                std::cout << "Should be 3 arguments: command, x, y. Was " << tokens.size() << ". Try again: " << std::endl;
                continue;
            }

            // parse x coordinate
            try {
                x = std::stoi(tokens[1]);
            } catch (const std::invalid_argument& e) {
                std::cout << "Y coordinate should be integer. Try again: " << std::endl;
                continue;
            }

            if (x < 1 || x > game->getColumns()) {
                std::cout << "X coordinate should be in between 1 and " << game->getColumns() << ". Was " << x << ". Try again: " << std::endl;
                continue;
            }

            // parse y coordinate
            try {
                y = std::stoi(tokens[2]);
            } catch (const std::invalid_argument& e) {
                std::cout << "Y coordinate should be integer. Try again: " << std::endl;
                continue;
            }

            if (y < 1 || y > game->getRows()) {
                std::cout << "Y coordinate should be in between 1 and " << game->getRows() << ". Was " << y << ". Try again: " << std::endl;
                continue;
            }

            game->unmarkCell(x, y);


        } else {
            std::cout << "Bad input! Try again: " << std::endl;
            continue;
        }

        if (game->isWin()) {
            game->endGame();
            std::cout << "Win!" << std::endl;
        }
    }

    delete game;
}


