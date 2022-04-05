#ifndef GAME_ROOK_H
#define GAME_ROOK_H

#include "Unit.h"

class Rook : public Unit {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Unit>(*this);
    }
public:
    Rook(char color, const fieldPtr &field);
    std::vector<fieldPtr> calculatePossibleMoves(boardPtr board) override;
    Rook() : Unit() {}
};

#endif //GAME_ROOK_H
