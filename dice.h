#ifndef DICE_H
#define DICE_H

#include <QRandomGenerator>

class Dice {
public:
    int roll() {
        return QRandomGenerator::global()->bounded(1, 7);
    }
};

#endif // DICE_H
