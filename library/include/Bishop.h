#ifndef GAME_BISHOP_H
#define GAME_BISHOP_H

#include "Unit.h"

class Bishop : public Unit {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Unit>(*this);
    }
public:
    std::vector<fieldPtr> calculatePossibleMoves(boardPtr board) override;
    Bishop(char colour, const fieldPtr &field);
    Bishop() : Unit() {}
};


#endif //GAME_BISHOP_H
