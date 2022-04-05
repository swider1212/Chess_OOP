#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <string>
#include "typedefs.h"
#include "Pawn.h"
#include "Rook.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>

class Player {
private:
    std::string name;
    gamePtr game;
    char color;
    unitPtr king;
    std::vector<unitPtr> pieces;
    std::vector<std::tuple<unitPtr, std::vector<fieldPtr>>> allPossibleMoves;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & name;
        ar & game;
        ar & color;
        ar & king;
        ar & pieces;
    }

public:
    void setGame(const gamePtr &game);

    Player(std::string name, gamePtr game, char color);

    std::string getName() const;

    void displayPossibleMoves();

    void calculatePossibleMoves();

    std::tuple<unitPtr, fieldPtr> getPossibleMoveFromString(const std::string&);

    std::tuple<unitPtr, fieldPtr, fieldPtr, unitPtr> makeMove(std::tuple<unitPtr, fieldPtr>, bool mock);

    void deleteIllegalMoves();

    void setup();

    bool isChecked();

    bool canMove(const fieldPtr& field);

    virtual ~Player();

    const gamePtr &getGame() const;

    playerPtr getNextPlayer(std::string name);

    int getNumberOfMoves();

    const std::vector<std::tuple<unitPtr, std::vector<fieldPtr>>> &getAllPossibleMoves() const;

    Player() {}
};

#endif //GAME_PLAYER_H
