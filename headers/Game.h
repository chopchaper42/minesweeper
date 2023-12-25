//
// Created by greg on 14.12.23.
//

#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#include <stdio.h>
#include <vector>
#include "GameMode.h"
#include "Cell.h"

class Game {
public:
    Game(GameMode mode);

    void renderField();
    void endGame();
    void markCell(int x, int y);
    void unmarkCell(int x, int y);
    void openCell(int x, int y);
    int calculateMinesAround(int x, int y);
    int getCellIndex(int x, int y);

    bool isPlaying() const;
    bool isWin();
    size_t getCellsAmount();
    size_t getMinesAmount();
    size_t getRows() { return rows; }
    size_t getColumns() { return columns; }

    ~Game();
private:
    void initField(size_t rows, size_t columns);
    void plantMines();
    void tryOpen(int x, int y);
    size_t rows;
    size_t columns;
    bool play = true;
    GameMode mode;
    std::vector<Cell*> cells;
};


#endif //MINESWEEPER_GAME_H
