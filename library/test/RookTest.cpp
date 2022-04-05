#include "Rook.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(RookMovementSuite)

    BOOST_AUTO_TEST_CASE(RookCalculateA1)
    {
        boardPtr board = std::make_shared<Board>();
        unitPtr rookW = std::make_shared<Rook>(Rook('W', nullptr));

        board->getField(0, 0)->setUnit(rookW);
        rookW->setField( board->getField(0, 0));
        board->display();
        std::vector<fieldPtr> moves = rookW->calculatePossibleMoves(board);

        std::stringstream ss;
        for(fieldPtr field:moves)
        {
            ss<<field->toString()<<" ";
        }
        BOOST_REQUIRE_EQUAL(ss.str(), "b1 c1 d1 e1 f1 g1 h1 a2 a3 a4 a5 a6 a7 a8 ");
    }

    BOOST_AUTO_TEST_CASE(RookCalculateH8)
    {
        boardPtr board = std::make_shared<Board>();
        unitPtr rookW = std::make_shared<Rook>(Rook('W', nullptr));

        board->getField(7, 7)->setUnit(rookW);
        rookW->setField( board->getField(7, 7));
        board->display();
        std::vector<fieldPtr> moves = rookW->calculatePossibleMoves(board);

        std::stringstream ss;
        for(fieldPtr field:moves)
        {
            ss<<field->toString()<<" ";
        }
        BOOST_REQUIRE_EQUAL(ss.str(), "g8 f8 e8 d8 c8 b8 a8 h7 h6 h5 h4 h3 h2 h1 ");
    }


BOOST_AUTO_TEST_SUITE_END()