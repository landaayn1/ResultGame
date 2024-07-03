#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_gameBoard(width(), height()), m_token1(0), m_token2(0) {
    // Create the dice button
    m_diceButton = new QPushButton("Roll Dice", this);
    connect(m_diceButton, &QPushButton::clicked, this, &MainWindow::rollDice);

    // Create the animation timer
    m_animationTimer = new QTimer(this);
    connect(m_animationTimer, &QTimer::timeout, this, &MainWindow::moveTokens);
}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    m_gameBoard.drawBoard(painter);
    m_gameBoard.drawToken(painter, m_token1.position(), 1);
    m_gameBoard.drawToken(painter, m_token2.position(), 2);

    // Display the dice roll
    int diceSize = 50;
    int diceX = width() - diceSize - 50;
    int diceY = (height() - diceSize) / 2;
    painter.drawRect(diceX, diceY, diceSize, diceSize);
    painter.drawText(diceX + diceSize / 4, diceY + diceSize / 2, QString("%1").arg(m_diceRoll));

    // Update the dice button position
    m_diceButton->setGeometry(width() - m_diceButton->width() - 50, height() - 50, m_diceButton->width(), m_diceButton->height());
}

void MainWindow::rollDice() {
    m_diceRoll = m_dice.roll();
    qDebug() << "Dice rolled:" << m_diceRoll;

    if (m_currentPlayer == 1) {
        m_stepsRemaining = m_diceRoll;
    } else {
        m_stepsRemaining = m_diceRoll;
    }

    m_animationTimer->start(500); // Start the animation with a 500ms interval
}

void MainWindow::moveTokens() {
    if (m_stepsRemaining > 0) {
        if (m_currentPlayer == 1) {
            m_token1.move(1);
        } else {
            m_token2.move(1);
        }
        m_stepsRemaining--;
        update();
    } else {
        m_animationTimer->stop();
        m_currentPlayer = (m_currentPlayer == 1) ? 2 : 1;
    }
}
