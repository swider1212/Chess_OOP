#include "Rook.h"

using namespace std;

Rook::Rook(char color, const fieldPtr &field) : Unit('R', color, field)    {}

vector<fieldPtr> Rook::calculatePossibleMoves(boardPtr board) {
    vector<fieldPtr> fields;
    vector<fieldPtr> buff;
    buff = board->castRay(getColour(),getField()->getX()+1, getField()->getY(), 1, 0);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = board->castRay(getColour(),getField()->getX()-1, getField()->getY(), -1, 0);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = board->castRay(getColour(),getField()->getX(), getField()->getY()-1, 0, -1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = board->castRay(getColour(),getField()->getX(), getField()->getY()+1, 0, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    return fields;
}
