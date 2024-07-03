#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QPixmap>
#include <QPainter>

class GameBoard {
public:
    GameBoard(int width, int height);
    void drawBoard(QPainter& painter);
    void drawToken(QPainter& painter, int position, int player);

private:
    QPixmap m_backgroundPixmap;
    int m_numColumns = 7;
    int m_numRows = 5;
    int m_circleSize;
    int m_circleSpacing;
    int m_startX = 50;
    int m_startY;
};

#endif // GAMEBOARD_H
