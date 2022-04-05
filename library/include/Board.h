#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "typedefs.h"
#include "Field.h"
#include <vector>
#include <memory>
#include <boost/serialization/shared_ptr.hpp>

class Board : public std::enable_shared_from_this<Board> {
private:
    std::vector<std::vector<fieldPtr>> array;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & array;
    }

public:
    Board();

    virtual ~Board();

    const fieldPtr &getField(int x, int y) const;

    std::vector<fieldPtr> castRay(char color, int startX, int startY, int vX, int vY, int range=7);

    unitPtr move(fieldPtr from, fieldPtr to);

    void display() const;
};

#endif //GAME_BOARD_H
