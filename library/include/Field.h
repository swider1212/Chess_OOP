#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "typedefs.h"
#include <boost/serialization/shared_ptr.hpp>

class Field {
private:
    int x;
    int y;
    unitPtr unit;
    boardPtr board;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & x;
        ar & y;
        ar & unit;
        ar & board;
    }

public:
    int getX() const;

    int getY() const;

    const unitPtr &getUnit() const;

    void setUnit(const unitPtr &unit);

    bool occupied() const;

    Field(int x, int y);

    std::string toString();

    Field() {}
};


#endif //GAME_FIELD_H
