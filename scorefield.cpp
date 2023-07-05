#include "scorefield.h"

ScoreField::ScoreField()
{
    isGameActive = false;
    score = "счет : 0\nпауза - ПРОБЕЛ";
    startGameBtn = new QPushButton("Играть");
    settingsBtn = new QPushButton("Настройки");
    QHBoxLayout *hBox = new QHBoxLayout(this);
    hBox->addWidget(startGameBtn);
    hBox->addWidget(settingsBtn);
    connect(startGameBtn,&QPushButton::clicked, this, &ScoreField::startBtnPressed);
    connect(settingsBtn,&QPushButton::clicked, this, &ScoreField::settingsBtnPressed);
}

void ScoreField::paintEvent(QPaintEvent *e){
    if(isGameActive){
        QPainter painter;
        painter.begin(this);
        painter.drawRect(1,0,width()-1,height()-1);
        painter.setFont(QFont("Arial",10,700));
        painter.drawText(QRect(0,0,width()-1,height()),Qt::AlignCenter,score);
        painter.end();
    }
}

void ScoreField::changeTextSlot(QString text)
{
    score = text;
    repaint();
}

void ScoreField::showButtons(bool _isGameActive)
{
    isGameActive = _isGameActive;
    if(!isGameActive){
        startGameBtn->show();
        settingsBtn->show();
    }
    else{
        startGameBtn->hide();
        settingsBtn->hide();
    }
}

void ScoreField::startBtnPressed()
{
    isGameActive = true;
    emit startGame();
}

void ScoreField::settingsBtnPressed()
{
    if(settingsBtn->text()=="Настройки"){
        startGameBtn->setDisabled(true);
        settingsBtn->setText("Ок");
        emit openSettings(true);
    }
    else{
        startGameBtn->setDisabled(false);
        settingsBtn->setText("Настройки");
        emit openSettings(false);
    }
}
