#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QPushButton>
#include "settings.h"

class SnakeItem;
class GameField;
class Snake;

class GameField : public QWidget{
    Q_OBJECT
private:
    Snake *snake;
    int snakeItemSize;
    SnakeItem *food;
    QTimer *moveSnakeTimer;
    int fieldSize;
    int score;
    bool isPause;
    bool isBtnStartPressed;
    bool isGameOver;
    bool isTurnBlocked;
    void setPauseStatus();
    void startNewGame();
    void gameOver();
    void createFood();
public:
    GameField();
    void paintEvent(QPaintEvent *e) override;
private slots:
    void moveSnakeSlot();
    void keyPressEvent(QKeyEvent *e) override;
signals:
    void changeText(QString text);
    void showButtons(bool _isGameActive);
public slots:
    void startBtnPressedSlot();
};

class SnakeItem{
    friend Snake;
    friend GameField;
private:
    int x;
    int y;

public:
    SnakeItem(int _x, int _y);
};

class Snake{
    friend GameField;
private:
    int startItemsValue;
    QList<SnakeItem*>snakeBody;
    enum SnakeDirection{
        up,
        left,
        down,
        right
    };
    SnakeDirection snakeDirection;
    int fieldSize;
public:
    Snake();
};

#endif // GAME_H
