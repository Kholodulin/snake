#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "game.h"
#include "scorefield.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    GameField *gameField;
    ScoreField *scoreField;
    QWidget * centralWidget;
    QGridLayout *gridLayout;
    QWidget *settings;
public slots:
    void settingsBtnPressedSlot(bool settingsOpen);
};
#endif // MAINWINDOW_H
