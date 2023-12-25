//
// Created by greg on 18.12.23.
//

#include "../headers/CellFactory.h"

Cell * CellFactory::makeBombCell() {
        return new Cell(true);
}

Cell * CellFactory::makeEmptyCell() {
    return new Cell(false);
}
