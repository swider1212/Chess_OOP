#ifndef GAME_KING_H
#define GAME_KING_H

#include "Unit.h"

class King : public Unit {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Unit>(*this);
    }
public:
    King(char color, const fieldPtr &field);
    std::vector<fieldPtr> calculatePossibleMoves(boardPtr board) override;
    King() : Unit() {}
};

#endif //GAME_KING_H
