#include "Knight.h"

using namespace std;

Knight::Knight(char color, const fieldPtr &field) : Unit('N', color, field){}

vector<fieldPtr> Knight::calculatePossibleMoves(boardPtr board) {
    vector<fieldPtr> fields;
    vector<fieldPtr> buff;
    buff = knightPossibleMovesCase(board, 2, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = knightPossibleMovesCase(board, -2, 1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = knightPossibleMovesCase(board, 2, -1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = knightPossibleMovesCase(board, -2, -1);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = knightPossibleMovesCase(board, 1, 2);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = knightPossibleMovesCase(board, -1, 2);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = knightPossibleMovesCase(board, 1, -2);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    buff = knightPossibleMovesCase(board, -1, -2);
    fields.insert(fields.end(), buff.begin(), buff.end());
    buff.clear();
    return fields;
}

vector<fieldPtr> Knight::knightPossibleMovesCase(boardPtr board, int dx, int dy) {
    vector<fieldPtr> fields;
    fieldPtr field;
    int x = getField()->getX();
    int y = getField()->getY();
    if(x+dx < 8 && y+dy < 8 && x+dx >= 0 && y+dy >= 0)
    {
        field = board->getField(x+dx, y+dy);
        if(field->occupied())
        {
            if(field->getUnit()->getColour() != getColour()) fields.push_back(field);
        }
        else
        {
            fields.push_back(field);
        }
    }
    return fields;
}
