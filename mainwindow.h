#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QFile>
#include <QDateTime>

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

    void newGame();
    void aboutTriggered();
    void rulesTriggered();
    void saveResultsTriggered();
    void exitTriggered();

private:
    void createMenu();

    GameBoard m_gameBoard;
    Dice m_dice;
    Token m_token1;
    Token m_token2;
    QPushButton* m_diceButton;
    QTimer* m_animationTimer;
    int m_currentPlayer = 1;
    int m_diceRoll = 0;
    int m_stepsRemaining = 0;

    QMenuBar* menuBar;
    QMenu* gameMenu;
    QAction* newGameAction;
    QAction* rulesAction;
    QAction* aboutAction;
    QAction* saveResultsAction;
    QAction* exitAction;

    int m_currentAttempt = 0;
};

#endif // MAINWINDOW_H
