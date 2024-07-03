#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QComboBox"
#include <QPushButton>
#include <QTimer>
#include <QRandomGenerator>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPushButton* m_diceButton;
    QPixmap m_backgroundPixmap;
    QTimer* m_timer;
    int m_currentPosition1;
    int m_currentPosition2;
    int m_currentPlayer;
    int m_diceRoll;

    int m_stepsRemaining;
    QTimer* m_animationTimer;



private slots:
    void rollDice();
    void moveTokens();

};

#endif // MAINWINDOW_H
