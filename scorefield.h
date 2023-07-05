#ifndef SCOREFIELD_H
#define SCOREFIELD_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QHBoxLayout>

class ScoreField : public QWidget
{
    Q_OBJECT
private:
    QString score;
    bool isGameActive;
    QPushButton *startGameBtn;
    QPushButton *settingsBtn;
public:
    ScoreField();
    void paintEvent(QPaintEvent *e) override;
public slots:
    void changeTextSlot(QString text);
    void showButtons(bool isGameActive);
    void startBtnPressed();
    void settingsBtnPressed();
signals:
    void startGame();
    void openSettings(bool settingsOpen);
};

#endif // SCOREFIELD_H
