#include "Field.h"
#include "Unit.h"
#include <sstream>

using namespace std;

int Field::getX() const {
    return x;
}

int Field::getY() const {
    return y;
}

const unitPtr &Field::getUnit() const {
    return unit;
}

void Field::setUnit(const unitPtr &unit) {
    this->unit = unit;
}
bool Field::occupied() const
{
    if(unit != nullptr) {
        return true;
    }
    else
        return false;
    }

Field::Field(int x, int y) : x(x), y(y), unit(nullptr) {}

string Field::toString() {
    stringstream ss;
    ss << (char)(x+'a') << y+1;
    return ss.str();
}