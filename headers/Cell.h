//
// Created by greg on 18.12.23.
//

#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H

class Cell {
public:
    explicit Cell(bool hasMine) {
        this->hasMine = hasMine;
    }
    Cell() {
        hasMine = false;
    }
    void plantMine();
    void mark();
    void unmark();
    void open();

    bool withMine();
    bool isOpened();
    bool isMarked();
private:
    bool opened = false;
    bool hasMine;
    bool marked = false;
};


#endif //MINESWEEPER_CELL_H
