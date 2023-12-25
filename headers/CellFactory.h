//
// Created by greg on 18.12.23.
//

#ifndef MINESWEEPER_CELLFACTORY_H
#define MINESWEEPER_CELLFACTORY_H


#include "Cell.h"

class CellFactory {
public:
    Cell * makeEmptyCell();
    Cell * makeBombCell();
};


#endif //MINESWEEPER_CELLFACTORY_H
