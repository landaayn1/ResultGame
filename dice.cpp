#include "dice.h"

int Dice::roll(){
    return QRandomGenerator::global()->bounded(1, 7);
}
