#include "Game.h"
#include <iostream>
#include <Player.h>


using namespace std;

string Player::getName() const {
    return name;
}

Player::~Player() {
    allPossibleMoves.clear();
    pieces.clear();
}

const gamePtr &Player::getGame() const {
    return game;
}

Player::Player(string name, gamePtr game, char color) : name(move(name)), game(move(game)), color(color) {
    pieces = vector<unitPtr>();
    allPossibleMoves = vector<tuple<unitPtr, vector<fieldPtr>>>();
}

void Player::calculatePossibleMoves() {
    allPossibleMoves.clear();
    for(unitPtr piece : this->pieces)
    {
        allPossibleMoves.push_back(make_tuple<unitPtr, vector<fieldPtr>>(
                static_cast<shared_ptr<Unit> &&>(piece), piece->calculatePossibleMoves(this->getGame()->getBoard())));
    }
}

void Player::displayPossibleMoves() {
    for(auto tuple : allPossibleMoves)
    {
        if(!get<1>(tuple).empty()){
            for(const auto& move : get<1>(tuple)){
                cout<<get<0>(tuple)->getField()->toString()<<move->toString()<<" ";
            }
            cout<<endl;
        }

    }

}

tuple<unitPtr, fieldPtr> Player::getPossibleMoveFromString(const string& input) {
    unitPtr unit;
    fieldPtr field;
    if(input.size()>4 && input!="reset") throw invalid_argument("Input to long");
    if(input.size()<4) throw invalid_argument("Input to short");
    if(input=="quit") throw 0;
    if(input=="reset") throw 2137;
    if (input.at(0)<'a' ||
    input.at(0)>'a'+7 ||
    input.at(1)<'1' ||
    input.at(1)>'8' ||
    input.at(2)<'a' ||
    input.at(2)>'a'+7 ||
    input.at(3)<'1' ||
    input.at(3)>'8') throw invalid_argument("Move is out of bounds");
    int fromX = (int) (input[0]-'a'), fromY = (int) (input[1]-'1');
    int toX = (int) (input[2]-'a'), toY = (int) (input[3]-'1');
    unit = this->game->getBoard()->getField(fromX, fromY)->getUnit();
    field = this->game->getBoard()->getField(toX, toY);

    if(unit != nullptr){
        for(auto moves : allPossibleMoves){
            if(get<0>(moves)->getType() == unit->getType()){
                for(const auto& f: get<1>(moves)){
                    if(f->toString() == field->toString()) return make_tuple(unit, field);
                }
            }

        }
    }
    throw invalid_argument("Move not possible");

}

bool Player::canMove(const fieldPtr& field) {
    for(auto moves : allPossibleMoves){
        for(const auto& f: get<1>(moves)){
            if(f->toString() == field->toString()) return true;
        }
    }
    return false;
}

bool Player::isChecked() {
    return this->game->getNextPlayer()->canMove(this->king->getField());
}

void Player::deleteIllegalMoves() {

    auto possibleMoves = allPossibleMoves;
    auto otherPossibleMovesBuff = this->getNextPlayer(getName())->allPossibleMoves;
    for(int i = 0; i < possibleMoves.size(); i++){
        vector<fieldPtr> legal;
        for(const auto& f: get<1>(possibleMoves[i])){
            auto lastMove = this->makeMove(make_tuple(get<0>(possibleMoves[i]), f), true);
            this->calculatePossibleMoves();
            this->getNextPlayer(getName())->calculatePossibleMoves();

//            cout<<isChecked()<<endl;
            if(!this->isChecked()) legal.push_back(f);
//            else cout<<"not legal";
            this->getGame()->revertMove(lastMove);
        }
        get<1>(possibleMoves[i]) = legal;

    }
    allPossibleMoves = possibleMoves;


    this->getNextPlayer(getName())->allPossibleMoves = otherPossibleMovesBuff;
}

void Player::setup() {
    pieces.clear();
    if(this->color == 'W'){
        for (int i = 0; i < 8; ++i) {
            fieldPtr field = this->game->getBoard()->getField(i, 1);
            unitPtr buff = make_shared<Pawn>(color, field);
            pieces.push_back(buff);
            field->setUnit(buff);
        }
        //rooks
        fieldPtr field = this->game->getBoard()->getField(0, 0);
        unitPtr buff = make_shared<Rook>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);

        field = this->game->getBoard()->getField(7, 0);
        buff = make_shared<Rook>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);

        //knights
        field = this->game->getBoard()->getField(1, 0);
        buff = make_shared<Knight>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);

        field = this->game->getBoard()->getField(6, 0);
        buff = make_shared<Knight>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);


        //bishops
        field = this->game->getBoard()->getField(2, 0);
        buff = make_shared<Bishop>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);

        field = this->game->getBoard()->getField(5, 0);
        buff = make_shared<Bishop>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);

        //queen
        field = this->game->getBoard()->getField(3, 0);
        buff = make_shared<Queen>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);

        //king
        field = this->game->getBoard()->getField(4, 0);
        buff = make_shared<King>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);
        king = buff;
    }
    else
    {
        for (int i = 0; i < 8; ++i) {
            fieldPtr field = this->game->getBoard()->getField(i, 6);
            unitPtr buff = make_shared<Pawn>(color, field);
            pieces.push_back(buff);
            field->setUnit(buff);
        }
        //rooks
        fieldPtr field = this->game->getBoard()->getField(0, 7);
        unitPtr buff = make_shared<Rook>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);

        field = this->game->getBoard()->getField(7, 7);
        buff = make_shared<Rook>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);

        //knights
        field = this->game->getBoard()->getField(1, 7);
        buff = make_shared<Knight>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);

        field = this->game->getBoard()->getField(6, 7);
        buff = make_shared<Knight>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);


        //bishops
        field = this->game->getBoard()->getField(2, 7);
        buff = make_shared<Bishop>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);

        field = this->game->getBoard()->getField(5, 7);
        buff = make_shared<Bishop>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);

        //queen
        field = this->game->getBoard()->getField(3, 7);
        buff = make_shared<Queen>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);

        //king
        field = this->game->getBoard()->getField(4, 7);
        buff = make_shared<King>(color, field);
        pieces.push_back(buff);
        field->setUnit(buff);
        king = buff;
    }

}

tuple<unitPtr, fieldPtr, fieldPtr, unitPtr> Player::makeMove(tuple<unitPtr, fieldPtr> m, bool mock) {
    fieldPtr field = get<0>(m)->getField();
    unitPtr buff = this->getGame()->getBoard()->move(get<0>(m)->getField(), get<1>(m));

    if(buff!= nullptr && !mock){
        for(auto it = getNextPlayer(getName())->pieces.begin(); it!=getNextPlayer(getName())->pieces.end();){
            if(*it == buff){
                it = getNextPlayer(getName())->pieces.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    return make_tuple(get<0>(m), field, get<1>(m), buff);
}

const vector<tuple<unitPtr, vector<fieldPtr>>> &Player::getAllPossibleMoves() const {
    return allPossibleMoves;
}

playerPtr Player::getNextPlayer(string name) {
    return game->getActivePlayer()->getName() == name ? game->getNextPlayer() : game->getActivePlayer();
}

int Player::getNumberOfMoves() {
    int buff =0;
    for(auto moves : allPossibleMoves)
    {
        buff += get<1>(moves).size();
    }
    return buff;
}

void Player::setGame(const gamePtr &game) {
    Player::game = game;
}
