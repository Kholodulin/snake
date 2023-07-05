#include "mainwindow.h"
#include "settings.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setFixedSize(320,360);
    gameField = new GameField();
    scoreField = new ScoreField();
    centralWidget  = new QWidget();
    gridLayout = new  QGridLayout();
    gridLayout->addWidget(gameField,0,0);
    settings = Settings::getInstance();
    settings->hide();
    gridLayout->addWidget(settings,1,0);
    gridLayout->addWidget(scoreField,2,0);
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);
    connect(gameField,&GameField::changeText,scoreField,&ScoreField::changeTextSlot);
    connect(gameField,&GameField::showButtons,scoreField,&ScoreField::showButtons);
    connect(scoreField,&ScoreField::startGame,gameField,&GameField::startBtnPressedSlot);
    connect(scoreField,&ScoreField::openSettings,this,&MainWindow::settingsBtnPressedSlot);
}

MainWindow::~MainWindow(){}

void MainWindow::settingsBtnPressedSlot(bool settingsOpen)
{
    if(settingsOpen){
        gameField->hide();
        settings->show();
    }
    else{
        settings->hide();
        gameField->show();
    }
}
