#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QColor>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_gameBoard(width(), height()), m_token1(0), m_token2(0) {

    createMenu();

    /*
    QMenu* gameMenu = menuBar()->addMenu("Game");
    QAction* newGameAction = gameMenu->addAction("New Game");
    QAction* exitAction = gameMenu->addAction("Exit");
    connect(newGameAction, &QAction::triggered, this, &MainWindow::newGame);
    connect(exitAction, &QAction::triggered, this, &QApplication::quit);
    */

    m_diceButton = new QPushButton("Roll Dice", this);
    connect(m_diceButton, &QPushButton::clicked, this, &MainWindow::rollDice);

    m_animationTimer = new QTimer(this);
    connect(m_animationTimer, &QTimer::timeout, this, &MainWindow::moveTokens);

    m_gameBoard.setCircleColors(QColor(139, 69, 19),
                                QColor(128, 128, 128),
                                QColor(173, 216, 230),
                                QColor(255, 0, 0),
                                QColor(0, 255, 0));
}

MainWindow::~MainWindow() {}

void MainWindow::newGame() {

    m_token1.reset();
    m_token2.reset();
    m_currentPlayer = 1;
    m_stepsRemaining = 0;
    update();
    m_initialPosition1 = 0;
    m_initialPosition2 = 0;
    newPosition = 0;
    newPosition1 = 0;
    finishPosition = 0;
    finishPosition1 = 0;
    m_diceRoll = 0;
}

void MainWindow::rulesTriggered() {
    QMessageBox::information(this, "Game Rules", "We have two colors: blue and light blue. They take turns moving around the playing field: yellow player comes first, and then blue player. Goal: reach the end of the field. When a chip lands on a red square, it moves 3 squares forward, on a gray one - 3 squares back, on a black one - to the beginning of the playing field, on a blue one - it makes an additional move.");
}

void MainWindow::aboutTriggered() {
    QMessageBox::information(this, "About Game", "The game was created as part of computing practice by students of the Faculty of Applied Mathematics and Informatics of BSU. Project Github: https://github.com/vitmark-06/Game4.git");
}

void MainWindow::saveResultsTriggered() {
    /*
    QFile file("game_results.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);

        QString winnerName;
        if (winner != nullptr) {
            winnerName = getPlayerNameByToken(winner);
        } else {
            winnerName = "No Winner";
        }

        out << "Attempt #" << m_currentAttempt << " - Winner: " << winnerName << "\n";
        out << "Date: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "\n\n";

        file.close();
        QMessageBox::information(this, "Results Saved", "Game results have been saved.");

        m_currentAttempt++;
    } else {
        QMessageBox::warning(this, "Error", "Unable to save game results.");
    }
    */
}

void MainWindow::exitTriggered() {
    QMessageBox::StandardButton result = QMessageBox::question(this, "Exit Game", "Are you sure you want to exit the game?",
                                                               QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes) {
        QApplication::exit();
    }
}

void MainWindow::createMenu() {
    menuBar = new QMenuBar(this);
    gameMenu = menuBar->addMenu("Game");

    newGameAction = new QAction("New Game", this);
    newGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    gameMenu->addAction(newGameAction);

    rulesAction = new QAction("Rules", this);
    rulesAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    gameMenu->addAction(rulesAction);

    aboutAction = new QAction("About", this);
    aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    gameMenu->addAction(aboutAction);

    gameMenu->addSeparator();

    saveResultsAction = new QAction("Save Results", this);
    saveResultsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    gameMenu->addAction(saveResultsAction);

    exitAction = new QAction("Exit", this);
    exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    gameMenu->addAction(exitAction);

    connect(newGameAction, &QAction::triggered, this, &MainWindow::newGame);
    connect(rulesAction, &QAction::triggered, this, &MainWindow::rulesTriggered);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutTriggered);
    connect(saveResultsAction, &QAction::triggered, this, &MainWindow::saveResultsTriggered);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitTriggered);
}

void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    int boardY = 50;

    m_gameBoard.drawBoard(painter, 0, boardY);
    m_gameBoard.drawToken(painter, m_token1.position(), 1, 0, boardY);
    m_gameBoard.drawToken(painter, m_token2.position(), 2, 0, boardY);

    // Display the dice roll
    int diceSize = 50;
    int diceX = width() - diceSize - 50;
    int diceY = boardY + (height() - diceSize) / 2;
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
        finishPosition = m_initialPosition1 + m_diceRoll;
    } else {
        m_stepsRemaining = m_diceRoll;
        finishPosition1 = m_initialPosition2 + m_diceRoll;
    }

    m_animationTimer->start(500); // Start the animation with a 500ms interval
}

void MainWindow::moveTokens() {
    if (m_stepsRemaining > 0) {
        if (m_currentPlayer == 1) {
            newPosition = m_token1.position() + 1;
            if ((newPosition == finishPosition && finishPosition == 4) || (newPosition == finishPosition && finishPosition == 13) || (newPosition == finishPosition && finishPosition == 23) || (newPosition == finishPosition && finishPosition == 32)) {
                // Двигаемся на две клетки вперед
                m_token1.setPosition(newPosition + 2);
                m_stepsRemaining--;
            } else if ((newPosition == finishPosition && finishPosition == 8) || (newPosition == finishPosition && finishPosition == 17) || (newPosition == finishPosition && finishPosition == 27)) {
                // Двигаемся на три клетки назад
                m_token1.setPosition(newPosition - 3);
                m_stepsRemaining--;
            } else if ((newPosition == finishPosition && finishPosition == 20) || (newPosition == finishPosition && finishPosition == 30)) {
                // Перемещаемся в начало
                m_token1.reset();
                m_stepsRemaining--;
            } else {
                m_token1.move(1);
                m_stepsRemaining--;
            }
        } else {
            newPosition1 = m_token2.position() + 1;
            if ((newPosition1 == finishPosition1 && finishPosition1 == 4) || (newPosition1 == finishPosition1 && finishPosition1 == 13) || (newPosition1 == finishPosition1 && finishPosition1 == 23) || (newPosition1 == finishPosition1 && finishPosition1 == 32)) {
                // Двигаемся на две клетки вперед
                m_token2.setPosition(newPosition1 + 2);
                m_stepsRemaining--;
            } else if ((newPosition1 == finishPosition1 && finishPosition1 == 8) || (newPosition1 == finishPosition1 && finishPosition1 == 17) || (newPosition1 == finishPosition1 && finishPosition1 == 27)) {
                // Двигаемся на три клетки назад
                m_token2.setPosition(newPosition1 - 3);
                m_stepsRemaining--;
            } else if ((newPosition1 == finishPosition1 && finishPosition1 == 20) || (newPosition1 == finishPosition1 && finishPosition1 == 30)) {
                // Перемещаемся в начало
                m_token2.reset();
                m_stepsRemaining--;
            } else {
                m_token2.move(1);
                m_stepsRemaining--;
            }
        }
        m_initialPosition1 = m_token1.position();
        m_initialPosition2 = m_token2.position();
        qDebug() << m_token1.position();
        update();
    } else {
        m_animationTimer->stop();
        m_currentPlayer = (m_currentPlayer == 1) ? 2 : 1;
    }
}
