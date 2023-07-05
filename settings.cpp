#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->speedSlider->setMaximum(150);
    ui->speedSlider->setMinimum(50);
    ui->speedSlider->setSliderPosition(100);
    ui->lenghtSlider->setMaximum(20);
    ui->lenghtSlider->setMinimum(4);
    ui->lenghtSlider->setSliderPosition(10);
    speed = 100;
    startLenght = 10;
}

Settings::~Settings()
{
    delete ui;
}

int Settings::getSpeed(){return speed;}

int Settings::getLenght(){return startLenght;}

void Settings::on_speedSlider_valueChanged(int value)
{
    speed = value;
}
void Settings::on_lenghtSlider_valueChanged(int value)
{
    startLenght = value;
}

Settings* Settings::instance = nullptr;
