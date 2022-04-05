#ifndef GAME_PAWN_H
#define GAME_PAWN_H

#include "Unit.h"

class Pawn : public Unit {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Unit>(*this);
    }
public:
    Pawn(char color, const fieldPtr &field);
    bool promotion(unitPtr &unit);
    std::vector<fieldPtr> calculatePossibleMoves(boardPtr board) override;
    Pawn() : Unit() {}
};

#endif //GAME_PAWN_H
