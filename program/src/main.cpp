#include <iostream>
#include "Game.h"
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>

using namespace std;

void print(const unitPtr &unit) {
    cout << unit->getColour() << unit->getType();
}

bool cliObserver(const boardPtr &board) {
    cout << endl << "   a  b  c  d  e  f  g  h" << endl;
    cout << " -------------------------" << endl;
    for (int y = 7; y >= 0; y--) {
        cout << y + 1;
        for (int x = 0; x < 8; x++) {
            cout << "|";
            if (board->getField(x,y)->occupied())
                print(board->getField(x,y)->getUnit());
            else
                cout << "  ";
        }
        cout << "|" << y + 1 << endl << " -------------------------" << endl;
    }
    cout << "   a  b  c  d  e  f  g  h" << endl << endl;

    return false;
}

class CLIObserver: public Observer
{
public:
    bool notify(boardPtr board) {
        return cliObserver(board);
    }
};

int main() {

    observerPtr gameObserver = make_shared<CLIObserver>();
    gamePtr game = make_shared<Game>(gameObserver);

    //load if file present
    ifstream ifs("store.txt");
    if (ifs.good()) {
        boost::archive::text_iarchive ia(ifs);
        ia.register_type(static_cast<Bishop *>(nullptr));
        ia.register_type(static_cast<King *>(nullptr));
        ia.register_type(static_cast<Knight *>(nullptr));
        ia.register_type(static_cast<Pawn *>(nullptr));
        ia.register_type(static_cast<Queen *>(nullptr));
        ia.register_type(static_cast<Rook *>(nullptr));
        ia & game;
        //for separation: reclaiming observer after deserialization
        game->setObserver(gameObserver);
    }

    //proper game
    game->initialize(ifs.good());
    game->simulate();

    //save once quit
    ofstream ofs("store.txt");
    boost::archive::text_oarchive oa(ofs);
    oa.register_type(static_cast<Bishop *>(nullptr));
    oa.register_type(static_cast<King *>(nullptr));
    oa.register_type(static_cast<Knight *>(nullptr));
    oa.register_type(static_cast<Pawn *>(nullptr));
    oa.register_type(static_cast<Queen *>(nullptr));
    oa.register_type(static_cast<Rook *>(nullptr));
    oa & game;

    return 0;
}