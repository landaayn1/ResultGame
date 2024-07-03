#include "gameboard.h"

GameBoard::GameBoard(int width, int height)
    : m_backgroundPixmap(QPixmap("C:\\Users\\User\\Desktop\\Projects\\ProgectQt\\Game\\image\\space.jpg")) {
    m_circleSize = qMin(width / (m_numColumns * 1.2), height / (m_numRows * 1.2));
    m_circleSpacing = m_circleSize * 1.2;
    m_startY = (height - m_numRows * m_circleSpacing) / 2;
}

void GameBoard::drawBoard(QPainter &painter, int x, int y) {
        painter.drawPixmap(x, y, painter.device()->width(), painter.device()->height(), m_backgroundPixmap);

        for (int i = 0; i < m_numRows; i++) {
            for (int j = 0; j < m_numColumns; j++) {
                int boardX = x + m_startX + j * m_circleSpacing;
                int boardY = y + m_startY + i * m_circleSpacing;
                int index = i * m_numColumns + j;
                if (index < 35) {
                    QColor color = QColor::fromHsv(index * 10, 255, 255);
                    painter.setBrush(QBrush(color));
                    painter.drawEllipse(boardX, boardY, m_circleSize, m_circleSize);
                    painter.setPen(Qt::black);
                    painter.drawText(boardX + m_circleSize / 4, boardY + m_circleSize / 2, QString::number(index + 1));
                }
            }
        }
}

void GameBoard::drawToken(QPainter &painter, int position, int tokenId, int x, int y){
    int tokenX = x + m_startX + (position % m_numColumns) * m_circleSpacing;
    int tokenY = y + m_startY + (position / m_numColumns) * m_circleSpacing;
    painter.setBrush(QBrush(Qt::lightGray));
    painter.drawEllipse(tokenX, tokenY, m_circleSize / 2, m_circleSize / 2);
    painter.drawText(tokenX + m_circleSize / 8, tokenY + m_circleSize / 4, QString::number(tokenId));
}

void GameBoard::setCircleColors(const QColor &brownColor, const QColor &grayColor, const QColor &blueColor, const QColor &redColor, const QColor &greenColor) {
    m_brownColor = brownColor;
    m_grayColor = grayColor;
    m_blueColor = blueColor;
    m_redColor = redColor;
    m_greenColor = greenColor;
}

