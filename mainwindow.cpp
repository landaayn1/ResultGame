#include "mainwindow.h"
#include <QPainter>
#include <QPushButton>
#include <QRandomGenerator>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Загрузка картинки
    m_backgroundPixmap = QPixmap("C:\\Users\\User\\Desktop\\Projects\\ProgectQt\\Game\\image\\space.jpg");

    // Создание кнопки для генерации случайного числа
    m_diceButton = new QPushButton("Roll Dice", this);
    connect(m_diceButton, &QPushButton::clicked, this, &MainWindow::rollDice);

    // Начальная позиция фишек
    m_currentPosition1 = 0;
    m_currentPosition2 = 0;
    m_currentPlayer = 1; // 1 for player 1, 2 for player 2
    m_diceRoll = 0;
    m_stepsRemaining = 0;
    m_animationTimer = new QTimer(this);
    connect(m_animationTimer, &QTimer::timeout, this, &MainWindow::moveTokens);
}


MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), m_backgroundPixmap);

    // Рисование игрового поля
    int numColumns = 7;
    int numRows = 5;
    int circleSize = qMin(width() / (numColumns * 1.2), height() / (numRows * 1.2));
    int circleSpacing = circleSize * 1.2;
    int startX = (width() - numColumns * circleSpacing) / 2;
    int startY = (height() - numRows * circleSpacing) / 2;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            int x = startX + j * circleSpacing;
            int y = startY + i * circleSpacing;
            int index = i * numColumns + j;
            if (index < 35) {
                QColor color = QColor::fromHsv(index * 10, 255, 255);
                painter.setBrush(QBrush(color));
                painter.drawEllipse(x, y, circleSize, circleSize);
                painter.setPen(Qt::black);
                painter.drawText(x + circleSize / 4, y + circleSize / 2, QString::number(index + 1));
            }
        }
    }

    // Рисование фишек
    painter.setBrush(QBrush(Qt::lightGray));
    painter.drawEllipse(startX + (m_currentPosition1 % 7) * circleSpacing, startY + (m_currentPosition1 / 7) * circleSpacing, circleSize / 2, circleSize / 2);
    painter.drawText(startX + (m_currentPosition1 % 7) * circleSpacing + circleSize / 8, startY + (m_currentPosition1 / 7) * circleSpacing + circleSize / 4, "36");

    painter.setBrush(QBrush(Qt::lightGray));
    painter.drawEllipse(startX + (m_currentPosition2 % 7) * circleSpacing, startY + (m_currentPosition2 / 7) * circleSpacing, circleSize / 2, circleSize / 2);
    painter.drawText(startX + (m_currentPosition2 % 7) * circleSpacing + circleSize / 8, startY + (m_currentPosition2 / 7) * circleSpacing + circleSize / 4, "37");

    // Отображение текущей позиции фишек
    painter.setPen(Qt::white);
    painter.drawText(10, height() - 10, QString("Current Position: %1, %2").arg(m_currentPosition1 + 1).arg(m_currentPosition2 + 1));

    // Отображение последнего броска кубика
    painter.drawText(width() - 100, height() - 10, QString("Dice Roll: %1").arg(m_diceRoll));

    // Обновление положения и размера кнопки
    m_diceButton->setGeometry((width() - m_diceButton->width()) / 2, height() - 50, m_diceButton->width(), m_diceButton->height());
}

void MainWindow::rollDice()
{
    m_diceRoll = QRandomGenerator::global()->bounded(1, 7);
    qDebug() << "Dice rolled:" << m_diceRoll;

    if (m_currentPlayer == 1) {
        m_stepsRemaining = m_diceRoll;
    } else {
        m_stepsRemaining = m_diceRoll;
    }

    m_animationTimer->start(500); // Начать анимацию с интервалом 500 мс
}

void MainWindow::moveTokens()
{
    if (m_stepsRemaining > 0) {
        if (m_currentPlayer == 1) {
            m_currentPosition1++;
            if (m_currentPosition1 >= 37) {
                m_currentPosition1 = 0;
            }
        } else {
            m_currentPosition2++;
            if (m_currentPosition2 >= 37) {
                m_currentPosition2 = 0;
            }
        }
        m_stepsRemaining--;
        update();
    } else {
        m_animationTimer->stop();
        m_currentPlayer = (m_currentPlayer == 1) ? 2 : 1;
    }
}
