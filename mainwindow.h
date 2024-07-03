#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include "gameboard.h"
#include "dice.h"
#include "token.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void rollDice();
    void moveTokens();

private:
    GameBoard m_gameBoard;
    Dice m_dice;
    Token m_token1;
    Token m_token2;
    QPushButton* m_diceButton;
    QTimer* m_animationTimer;
    int m_currentPlayer = 1;
    int m_diceRoll = 0;
    int m_stepsRemaining = 0;
};

#endif // MAINWINDOW_H
