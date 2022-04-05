#include "King.h"

using namespace std;

King::King(char color, const fieldPtr &field) : Unit('K', color, field){}

vector<fieldPtr> King::calculatePossibleMoves(boardPtr board) {
    vector<fieldPtr> fields;
    vector<fieldPtr> buff;
    //rook movement
    buff = board->castRay(getColour(),getField()->getX()+1, getField()->getY(), 1, 0, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = board->castRay(getColour(),getField()->getX()-1, getField()->getY(), -1, 0, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = board->castRay(getColour(),getField()->getX(), getField()->getY()-1, 0, -1, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = board->castRay(getColour(),getField()->getX(), getField()->getY()+1, 0, 1, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    //bishop movement
    buff = board->castRay(getColour(),getField()->getX()+1, getField()->getY()+1, 1, 1, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = board->castRay(getColour(),getField()->getX()-1, getField()->getY()+1, -1, 1, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = board->castRay(getColour(),getField()->getX()+1, getField()->getY()-1, 1, -1, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = board->castRay(getColour(),getField()->getX()-1, getField()->getY()-1, -1, -1, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    return fields;
}
