#include "Pawn.h"

using namespace std;

bool Pawn::promotion(unitPtr &unit) {
    return false;
}

Pawn::Pawn(char color, const fieldPtr &field) : Unit('P', color, field){}

vector<fieldPtr> Pawn::calculatePossibleMoves(boardPtr board) {
    vector<fieldPtr> fields;
    int x = getField()->getX();
    int y = getField()->getY();

    if(getColour() == 'W' && y<7)
    {   //first moves
        if(y==1 && !board->getField(x, y+2)->occupied() && !board->getField(x, y+1)->occupied())
            fields.push_back(board->getField(x, y+2));
        //normal moves
        if(!board->getField(x, y+1)->occupied())
            fields.push_back(board->getField(x, y+1));
        //taking
        auto takeWhiteR = &(board->getField(x+1, y+1));
        auto takeWhiteL = &(board->getField(x-1, y+1));
        if(x < 7 && (*takeWhiteR)->occupied() && (*takeWhiteR)->getUnit()->getColour() != getColour())
            fields.push_back(*takeWhiteR);
        if(x > 0 && (*takeWhiteL)->occupied() && (*takeWhiteL)->getUnit()->getColour() != getColour())
            fields.push_back(*takeWhiteL);
    }else
    {
        if(y>0)
        {
            if(y==6 && !board->getField(x, y-2)->occupied() && !board->getField(x, y-1)->occupied()) fields.push_back(board->getField(x, y-2));
            if(!board->getField(x, y-1)->occupied()) fields.push_back(board->getField(x, y-1));
            //taking
            auto takeBlackR = &(board->getField(x+1, y-1));
            auto takeBlackL = &(board->getField(x-1, y-1));
            if(x < 7 && (*takeBlackR)->occupied() && (*takeBlackR)->getUnit()->getColour() != getColour())
                fields.push_back(*takeBlackR);
            if(x > 0 && (*takeBlackL)->occupied() && (*takeBlackL)->getUnit()->getColour() != getColour())
                fields.push_back(*takeBlackL);
        }

    }



    return fields;
}
