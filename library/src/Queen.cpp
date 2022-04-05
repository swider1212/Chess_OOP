#include "Queen.h"

using namespace std;

Queen::Queen(char color, const fieldPtr &field) : Unit('Q', color, field){}

vector<fieldPtr> Queen::calculatePossibleMoves(boardPtr board) {
    vector<fieldPtr> fields;
    vector<fieldPtr> buff;
    //rook movement
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
    //bishop movement
    buff = board->castRay(getColour(),getField()->getX()+1, getField()->getY()+1, 1, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = board->castRay(getColour(),getField()->getX()-1, getField()->getY()+1, -1, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = board->castRay(getColour(),getField()->getX()+1, getField()->getY()-1, 1, -1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = board->castRay(getColour(),getField()->getX()-1, getField()->getY()-1, -1, -1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    return fields;
}
