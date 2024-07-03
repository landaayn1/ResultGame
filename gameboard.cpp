#include "gameboard.h"

GameBoard::GameBoard(int width, int height)
    : m_backgroundPixmap(QPixmap("C:\\Users\\User\\Desktop\\Projects\\ProgectQt\\Game\\image\\space.jpg")) {
    m_circleSize = qMin(width / (m_numColumns * 1.2), height / (m_numRows * 1.2));
    m_circleSpacing = m_circleSize * 1.2;
    m_startY = (height - m_numRows * m_circleSpacing) / 2;
}

void GameBoard::drawBoard(QPainter& painter) {
    painter.drawPixmap(0, 0, painter.device()->width(), painter.device()->height(), m_backgroundPixmap);

    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numColumns; j++) {
            int x = m_startX + j * m_circleSpacing;
            int y = m_startY + i * m_circleSpacing;
            int index = i * m_numColumns + j;
            if (index < 35) {
                QColor color = QColor::fromHsv(index * 10, 255, 255);
                painter.setBrush(QBrush(color));
                painter.drawEllipse(x, y, m_circleSize, m_circleSize);
                painter.setPen(Qt::black);
                painter.drawText(x + m_circleSize / 4, y + m_circleSize / 2, QString::number(index + 1));
            }
        }
    }
}

void GameBoard::drawToken(QPainter& painter, int position, int player) {
    painter.setBrush(QBrush(Qt::lightGray));
    painter.drawEllipse(m_startX + (position % m_numColumns) * m_circleSpacing, m_startY + (position / m_numColumns) * m_circleSpacing, m_circleSize / 2, m_circleSize / 2);
    painter.drawText(m_startX + (position % m_numColumns) * m_circleSpacing + m_circleSize / 8, m_startY + (position / m_numColumns) * m_circleSpacing + m_circleSize / 4, QString::number(player));
}
