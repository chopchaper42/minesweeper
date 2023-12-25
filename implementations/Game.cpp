//
// Created by greg on 14.12.23.
//

#include "../headers/Game.h"
#include "../headers/Cell.h"
#include <iostream>
#include <array>
#include <vector>
#include <iomanip>


int from_X(int x) { return x == 0 ? 0 : x - 1; }
int from_y(int y) { return y == 0 ? 0 : y - 1; }
int to_x(int x, int columns) { return x == columns - 1 ? x + 1 : x + 2; }
int to_y(int y, int rows) { return y == rows - 1 ? y + 1 : y + 2; }

int Game::getCellIndex(int x, int y) { return y * columns + x; }


void Game::renderField() {

    if (columns > 9) {
        std::cout << std::setw(29);
        for (int i = 0; i < columns + 1; i++) {
            int dec = i / 10;
            if (dec != 0)
                std::cout << "  " << dec;
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < columns; ++i) {
        std::cout << "  " << (i + 1) % 10;
    }
    std::cout << std::endl;

    // print upper border
    for (int i = 0; i < columns * 3 + 2; ++i)
        std::cout << '-';

    std::cout << std::endl;

    for (int i = 0; i < rows; ++i) {
        std::cout << "|";
        for (int j = 0; j < columns; ++j) {
            int index = i * columns + j;

            if (isPlaying()) {
                if (cells[index]->isOpened()) {
                    int minesAround = calculateMinesAround(j, i);
                    std::cout << " " << minesAround << " ";
                } else if (cells[index]->isMarked()) {
                    std::cout << " ? ";
                } else {
                    /*if (cells[index]->withMine())
                        std::cout << " * ";
                    else*/
                    std::cout << " # ";
                }
            }
        }

        std::cout << "|  " << i + 1 << std::endl;
    }

    // print bottom border
    for (int i = 0; i < columns * 3 + 2; ++i)
        std::cout << '-';

    std::cout << std::endl;

}

// TODO: handle edge cases
int Game::calculateMinesAround(int x, int y) {
    size_t counter = 0;

    int i, to__y;

    try {
        i = from_y(y);
        to__y = to_y(y, rows);
    } catch (std::exception& e)
    {
        std::cout << "Exception caught : " << e.what() << std::endl;
    }

    try {
        // edge cases: x, y
        for (/*int i = from_y(y)*/; i < /*to_y(y, rows)*/ to__y; i++) {
            for (int j = from_X(x); j < to_x(x, columns); j++) {
                if (cells[i * columns + j]->withMine())
                    counter++;
            }
        }
    } catch (std::exception& e)
    {
        std::cerr << "Exception caught : " << e.what() << std::endl;
    }

    return counter;
}

void Game::initField(size_t rows, size_t columns) {
    this->rows = rows;
    this->columns = columns;

    for (int i = 0; i < getCellsAmount(); i++)
        cells.push_back(new Cell());

    plantMines();
}

size_t Game::getCellsAmount() {
    return rows * columns;
}

bool Game::isPlaying() const {
    return play;
}

Game::Game(GameMode mode) {
    this->mode = mode;
    switch (mode) {
        case GameMode::EASY:
            initField(9, 9);
            break;
        case GameMode::MEDIUM:
            initField(16, 16);
            break;
        case GameMode::HARD:
            initField(16, 31);
            break;
    }
}

size_t Game::getMinesAmount() {
    switch (mode) {
        case GameMode::EASY:
            return 10;
        case GameMode::MEDIUM:
            return 40;
        case GameMode::HARD:
            return 99;
    }
}

void Game::endGame() {
    play = false;
}

void Game::plantMines() {
    std::srand(time(nullptr)); // use current time as seed for random generator
    int random_value = std::rand();

    size_t count = 0;

    while (count != getMinesAmount()) {
        size_t random_value = std::rand();

        size_t cellIndex = random_value % getCellsAmount();

        if (cells[cellIndex]->withMine())
            continue;

        cells[cellIndex]->plantMine();
        count++;
    }
}

void Game::markCell(int x, int y) {
    cells[(y-1) * columns + (x-1)]->mark();
}

void Game::unmarkCell(int x, int y) {
    cells[(y-1) * columns + (x-1)]->unmark();
}

void Game::openCell(int x, int y) {
    // 1. if has mine -> end game
    int index = y * columns + x;
    if (cells[index]->withMine()) {
        endGame();
        return;
    }
    // 2. if no mine
    cells[index]->open();

    tryOpen(x, y);

}

void Game::tryOpen(int x, int y) {
    int index = y * columns + x;

   // if there is mine, don't open
    if (cells[index]->withMine()) // or is opened. Remove from below
        return;

    cells[index]->open();

    // if there are mines around, open and stop
    if (calculateMinesAround(x, y) > 0) { return; }

    if (x - 1 >= 0 && !cells[getCellIndex(x - 1, y)]->isOpened())
        tryOpen(x - 1, y); // the left cell
    if (y - 1 >= 0 && !cells[getCellIndex(x, y - 1)]->isOpened())
        tryOpen(x, y - 1); // the upper cell
    if (x + 1 < columns && !cells[getCellIndex(x + 1, y)]->isOpened())
        tryOpen(x + 1, y); // the right cell
    if (y + 1 < rows && !cells[getCellIndex(x, y + 1)]->isOpened())
        tryOpen(x, y + 1); // the bottom cell
}

bool Game::isWin() {
    bool win = true;
    for (Cell * c : cells) {
        if (!c->isOpened() && !c->withMine()) {
            win = false;
        }
    }
    return win;
}

Game::~Game() {
    for (Cell * c : cells)
        delete c;
}
