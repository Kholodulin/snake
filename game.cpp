#include "game.h"

GameField::GameField(){
    setFixedSize(300,300);
    setFocusPolicy(Qt::StrongFocus);
    snakeItemSize = 10;
    score = 0;
    fieldSize = width()/snakeItemSize;
    isBtnStartPressed = false;
}
void GameField::setPauseStatus()
{
    QString text;
    isPause ? moveSnakeTimer->stop() : moveSnakeTimer->start(100);
    isPause ? text="\nпродолжить - ПРОБЕЛ" : text="\nпауза - ПРОБЕЛ";
    emit changeText("счет : "+ QString::number(score)+ text);
}

void GameField::startNewGame()
{
    isGameOver = false;
    score = 0;
    snake = new Snake();
    food = new SnakeItem(fieldSize/2,fieldSize/2);
    isPause = false;
    isGameOver = false;
    isTurnBlocked = false;
    moveSnakeTimer = new QTimer();
    connect(moveSnakeTimer, &QTimer::timeout, this, &GameField::moveSnakeSlot);
    int timerValue = 200 - Settings::getInstance()->getSpeed();
    moveSnakeTimer->start(timerValue);
    emit changeText("счет : "+ QString::number(score)+ "\nпауза - ПРОБЕЛ");
    emit showButtons(true);
}

void GameField::gameOver()
{
    isGameOver = true;
    emit changeText("Начать заново - ПРОБЕЛ");
    moveSnakeTimer->stop();
    emit showButtons(false);
}

void GameField::createFood()
{
    food->x = QRandomGenerator::global()->bounded(0,fieldSize-1);
    food->y = QRandomGenerator::global()->bounded(0,fieldSize-1);
    for(int i = 0; i<snake->snakeBody.size(); i++){
        if(food->x == snake->snakeBody[i]->x && food->y == snake->snakeBody[i]->y){
            return createFood();
        }
    }
}

void GameField::paintEvent(QPaintEvent *e){
    if(!isBtnStartPressed){
        return;
    }
    QPainter painter;
    painter.begin(this);
    if(isGameOver){
        painter.setFont(QFont("Arial",10,700));
        painter.drawText(QRect(0,0,width(),height()),Qt::AlignCenter,"Игра проиграна\nсчет : "+QString::number(score));
        painter.end();
        return;
    }
    painter.drawRect(1,0,width()-1,height()-6);
    //отрисовка змейки
    for(int i = 0; i < snake->snakeBody.size(); i++ ){
        painter.setBrush(QBrush(QColor(Qt::green),Qt::BrushStyle::SolidPattern));
        painter.drawEllipse(snake->snakeBody[i]->x*snakeItemSize, snake->snakeBody[i]->y*snakeItemSize, snakeItemSize, snakeItemSize);
    }
    //отрисовка еды
    painter.drawEllipse(food->x*snakeItemSize, food->y*snakeItemSize, snakeItemSize, snakeItemSize);
    painter.end();
    isTurnBlocked = false;
}

void GameField::moveSnakeSlot(){
    SnakeItem *newSnakeItem;
    if(snake->snakeDirection == Snake::SnakeDirection::right){
        newSnakeItem = new SnakeItem(snake->snakeBody[0]->x+1, snake->snakeBody[0]->y);
    }
    else if(snake->snakeDirection == Snake::SnakeDirection::left){
        newSnakeItem = new SnakeItem(snake->snakeBody[0]->x-1, snake->snakeBody[0]->y);
    }
    else if(snake->snakeDirection == Snake::SnakeDirection::up){
        newSnakeItem = new SnakeItem(snake->snakeBody[0]->x, snake->snakeBody[0]->y-1);
    }
    else{
        newSnakeItem = new SnakeItem(snake->snakeBody[0]->x, snake->snakeBody[0]->y+1);
    }

    //ограничение игрового поля
    if(newSnakeItem->x > fieldSize-1 || newSnakeItem->x < 0
        || newSnakeItem->y < 0 || newSnakeItem->y > fieldSize-2)
    {
        gameOver();
    }

    //проигрыш
    for(int i = 0; i<snake->snakeBody.size();++i){
        if(newSnakeItem->x == snake->snakeBody[i]->x && newSnakeItem->y == snake->snakeBody[i]->y){
            gameOver();
        }
    }
    //получение еды
    if(newSnakeItem->x == food->x && newSnakeItem->y == food->y){
        score++;
        createFood();
        emit changeText("счет : "+ QString::number(score)+ "\nпауза - ПРОБЕЛ");
    }else{
        snake->snakeBody.removeLast();
    }
    snake->snakeBody.insert(0,newSnakeItem);
    repaint();
}

void GameField::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Space){
        if(isGameOver){
            startNewGame();
            return;
        }
        isPause = !isPause;
        setPauseStatus();
    }
    if(isTurnBlocked || isPause || !isBtnStartPressed){
        return;
    }
        if(e->key() == Qt::Key_Left && snake->snakeDirection != Snake::SnakeDirection::right ){
            snake->snakeDirection = Snake::SnakeDirection::left;
        }
        if(e->key() == Qt::Key_Right && snake->snakeDirection != Snake::SnakeDirection::left ){
            snake->snakeDirection = Snake::SnakeDirection::right;
        }
        if(e->key() == Qt::Key_Down && snake->snakeDirection != Snake::SnakeDirection::up ){
            snake->snakeDirection = Snake::SnakeDirection::down;
        }
        if(e->key() == Qt::Key_Up && snake->snakeDirection != Snake::SnakeDirection::down ){
            snake->snakeDirection = Snake::SnakeDirection::up;
        }
        isTurnBlocked = true;
}

void GameField::startBtnPressedSlot()
{
    isBtnStartPressed = true;
    startNewGame();
}

SnakeItem::SnakeItem(int _x, int _y){
    x=_x;
    y=_y;
}

Snake::Snake(){
    startItemsValue = Settings::getInstance()->getLenght();
    snakeDirection = SnakeDirection::right;
    for(int i =0; i<startItemsValue;i++){
        snakeBody.insert(0, new SnakeItem(i,0));
    }
}
