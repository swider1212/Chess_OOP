#include "Game.h"
#include <iostream>

using namespace std;

void Game::initialize(bool load) {
    player1->setGame(shared_from_this());
    player2->setGame(shared_from_this());

    if (!load) {
        cout << "NEW GAME CREATED" << endl;
        this->board = make_shared<Board>();
        this->activePlayer = player1;
        this->player1->setup();
        this->player2->setup();
    }
    else {
        cout << "GAME LOADED" << endl;
    }

    this->player1->calculatePossibleMoves();
    this->player2->calculatePossibleMoves();

}

playerPtr Game::getNextPlayer() {
    if(activePlayer == player1)
    {
        return player2;
    }
    else
    {
        return player1;
    }
}
Game::~Game() {

}

const boardPtr &Game::getBoard() const {
    return board;
}

void Game::simulate() {
    if (getObserver() != nullptr) {
        getObserver()->notify(getBoard());
    }

    bool won = false;

    while(true)
    {
        string input;
        if (!won) {
            cout << "it's " << activePlayer->getName() << " turn" << endl;
            cout << R"(| type move in notation [from file][from rank][to file][to rank], e.g.: "a2a3"
| type "quit" to save game and exit
| type "reset" to reset and start new game)" << endl;
        }
        else {
            cout << R"(| type "quit" to exit game
| type "reset" to reset and start new game)" << endl;
            won = false;
        }
        cin>>input;
        try
        {
            activePlayer->makeMove(activePlayer->getPossibleMoveFromString(input), false);

            activePlayer = getNextPlayer();

            activePlayer->calculatePossibleMoves();
            getNextPlayer()->calculatePossibleMoves();
            activePlayer->deleteIllegalMoves();
            getNextPlayer()->deleteIllegalMoves();

            if (getObserver() != nullptr) {
                getObserver()->notify(getBoard());
            }
            if(activePlayer->isChecked()) cout<< "Player " << activePlayer->getName()<<" is checked";
            if(activePlayer->getNumberOfMoves() == 0)
            {
                if(activePlayer->isChecked())
                {
                    cout<<" and mated." <<endl;
                    cout<<"Player "<< getNextPlayer()->getName()<<" has won."<<endl;
                }
                else
                {
                    cout<<"Player has tied"<<endl;
                }
                reset();
                won = true;
            }
            else if(activePlayer->isChecked())
            {
                cout<<"."<<endl;
            }

        } catch (invalid_argument& ia) {

            cerr << "Invalid argument: " << ia.what() << '\n';
            cout << "possible moves:" << endl;
            activePlayer->displayPossibleMoves();

        } catch (int q) {
            if (q == 2137) {
                reset();
                cout << "GAME RESET" << endl;
                if (getObserver() != nullptr) {
                    getObserver()->notify(getBoard());
                }
            }
            else if (q == 0) break;
        }
    }
    cout << "End" << endl;
}

Game::Game(const observerPtr &observer) : observer(observer) {
    player1 = make_shared<Player>(Player("White", nullptr, 'W'));
    player2 = make_shared<Player>(Player("Black", nullptr, 'B'));
}

void Game::revertMove(tuple<unitPtr, fieldPtr, fieldPtr, unitPtr> lastMove) {
    unitPtr mover = get<0>(lastMove), taker = get<3>(lastMove);
    fieldPtr from = get<1>(lastMove), to = get<2>(lastMove);
    board->move(to,from);
    from->setUnit(mover);
    if(taker) {
        taker->setField(to);
        to->setUnit(taker);
    }


}

const observerPtr &Game::getObserver() const {
    return observer;
}

const playerPtr &Game::getActivePlayer() const {
    return activePlayer;
}

void Game::reset() {
    this->board = make_shared<Board>();
    this->activePlayer = player1;
    this->player1->setup();
    this->player2->setup();

    this->player1->calculatePossibleMoves();
    this->player2->calculatePossibleMoves();
}

void Game::setObserver(const observerPtr &observer) {
    Game::observer = observer;
}
