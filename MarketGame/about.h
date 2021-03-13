#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}

class About : public QDialog{
    Q_OBJECT
public:
    explicit About(QWidget *parent = nullptr);
    About() =delete;
    About(const About &assignThis) =delete;
    About & operator = (const About & assignThis) =delete;
    ~About();
private:
    Ui::About *ui;
};

#endif // ABOUT_H
