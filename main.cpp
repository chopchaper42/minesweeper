#include <iostream>
#include <cstring>
#include <ctime>
#include <vector>
#include <thread>
#include "headers/Game.h"
#include "headers/Cell.h"
#include "headers/GameMode.h"
#include "headers/CellFactory.h"
#include "headers/ArgumentParser.h"

int main(int argc, char** argv) {
    ArgumentParser parser(argc, argv);
    Game * game;

    if (parser.cmdOptionExists("--help")) {
        std::cout << "The minesweeper game." << std::endl;
        std::cout << "For running the game you should specify the --mode parameter." << std::endl;
        std::cout << R"(--mode takes "easy", "medium" or "hard" options.)" << std::endl;
        std::cout << "Easy mode: 9*9 field, 10 mines. Medium mode: 16*16 field, 40 mines. Hard mode: 31*16 field, 99 mines." << std::endl;
        std::cout << "Game rules:" << std::endl;
        std::cout << "There are 4 commands:" << std::endl;
        std::cout << "1. open <x> <y> to open the cell on coordinates <x> <y>. Be careful, if you hit the mine, the game will end." << std::endl;
        std::cout << "2. mark <x> <y> to mark the cell on coordinates <x> <y>." << std::endl;
        std::cout << "3. unmark <x> <y> to unmark the cell on coordinates <x> <y>." << std::endl;
        std::cout << "4. quit to quit the game." << std::endl;
        std::cout << R"("#" cell means closed cell, "?" cell means marked cell, a cell with a number means that there are exactly so much mines around this cell.)" << std::endl;

        std::cout << "That's all. Good luck!" << std::endl;
        return 0;
    }


    //
    GameMode mode;
    try {
        mode = parser.getMode();
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    game = new Game(mode);

    while (game->isPlaying()) {

        // print the field
        game->renderField();


        std::string line; // line from the input stream
        std::string token;
        std::vector<std::string> tokens;

        getline(std::cin, line);

        //tokenize the input line
        for (char c : line) {
            if (c == ' ' || c == '\t') {
                tokens.push_back(token);
                token = "";
                continue;
            }

            token += c;
        }

        tokens.push_back(token);


        if (tokens[0] == "quit") {
            game->endGame();
            std::cout << "Game over!" << std::endl;

        } else if (tokens[0] == "mark") {
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

            // mark the <X,Y> cell
            game->markCell(x, y);


        } else if (tokens[0] == "open") {
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

            // values starting from 0, not from 1
            size_t prog_x = x - 1;
            size_t prog_y = y - 1;

            // opens the <X,Y> cell
            game->openCell(prog_x, prog_y);

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

            // unmark the <X,Y> cell
            game->unmarkCell(x, y);

        } else {
            // invalid command
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


