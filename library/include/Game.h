#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "typedefs.h"
#include "Board.h"
#include "Player.h"
#include <boost/serialization/shared_ptr.hpp>

class Observer
{
public:
    virtual bool notify(boardPtr board) = 0;
};

typedef std::shared_ptr<Observer> observerPtr;

class Game : public std::enable_shared_from_this<Game> {
private:
    playerPtr player1;
    playerPtr player2;
    playerPtr activePlayer;
    boardPtr board;
    observerPtr observer;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & player1;
        ar & player2;
        ar & activePlayer;
        ar & board;
    }

public:
    Game(const observerPtr &observer);

    const observerPtr &getObserver() const;

    virtual ~Game();

    void initialize(bool load);

    playerPtr getNextPlayer();

    const boardPtr &getBoard() const;

    void simulate();

    void revertMove(std::tuple<unitPtr, fieldPtr, fieldPtr, unitPtr> lastMove);

    const playerPtr &getActivePlayer() const;

    void setObserver(const observerPtr &observer);

    Game() {}

    void reset();
};


#endif //GAME_GAME_H
