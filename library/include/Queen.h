#ifndef GAME_QUEEN_H
#define GAME_QUEEN_H

#include "Unit.h"

class Queen : public Unit{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Unit>(*this);
    }
public:
    Queen(char color, const fieldPtr &field);
    std::vector<fieldPtr> calculatePossibleMoves(boardPtr board) override;
    Queen() : Unit() {}
};

#endif //GAME_QUEEN_H
