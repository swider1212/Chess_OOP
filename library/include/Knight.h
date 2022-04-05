#ifndef GAME_KNIGHT_H
#define GAME_KNIGHT_H

#include "Unit.h"

class Knight : public Unit {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Unit>(*this);
    }
public:
    Knight(char color, const fieldPtr &field);
    std::vector<fieldPtr> knightPossibleMovesCase(boardPtr board, int dx, int dy);
    std::vector<fieldPtr> calculatePossibleMoves(boardPtr board) override;
    Knight() : Unit() {}
};

#endif //GAME_KNIGHT_H
