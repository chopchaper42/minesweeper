//
// Created by greg on 18.12.23.
//

#include "../headers/Cell.h"

void Cell::plantMine() {
    hasMine = true;
}

bool Cell::withMine() {
    return hasMine;
}

bool Cell::isOpened() {
    return opened;
}

bool Cell::isMarked() {
    return marked;
}

void Cell::mark() {
    marked = true;
}

void Cell::unmark() {
    marked = false;
}

void Cell::open() {
    opened = true;
}
