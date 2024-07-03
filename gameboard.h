#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QPixmap>
#include <QPainter>

class GameBoard {
public:
    GameBoard(int width, int height);
    void drawBoard(QPainter& painter, int x, int y);
    void drawToken(QPainter& painter, int position, int tokenId, int x, int y);
    void setCircleColors(const QColor& brownColor, const QColor& grayColor, const QColor& blueColor, const QColor& redColor, const QColor& greenColor);

private:
    QPixmap m_backgroundPixmap;
    int m_numColumns = 7;
    int m_numRows = 5;
    int m_circleSize;
    int m_circleSpacing;
    int m_startX = 50;
    int m_startY;

    QColor m_brownColor;
    QColor m_grayColor;
    QColor m_blueColor;
    QColor m_redColor;
    QColor m_greenColor;

};

#endif // GAMEBOARD_H
