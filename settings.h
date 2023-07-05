#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT
private:
    static Settings *instance;
    explicit Settings(QWidget *parent = nullptr);
    int speed;
    int startLenght;

public:
    static Settings *getInstance(){
        if(instance==nullptr){
            instance = new Settings();
        }
        return instance;
    }
    Settings(const Settings&)=delete;
    Settings &operator=(const Settings&)=delete;
    ~Settings();
    int getSpeed();
    int getLenght();

private slots:
    void on_speedSlider_valueChanged(int value);
    void on_lenghtSlider_valueChanged(int value);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
