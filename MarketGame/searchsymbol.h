#ifndef SEARCHSYMBOL_H
#define SEARCHSYMBOL_H

#include <QDialog>

namespace Ui {
class SearchSymbol;
}

class SearchSymbol : public QDialog
{
    Q_OBJECT

public:
    explicit SearchSymbol(QWidget *parent = nullptr);
    ~SearchSymbol();

private slots:
    void on_symbolLineEdit_textChanged(const QString &arg1);

private:
    Ui::SearchSymbol *ui;
};

#endif // SEARCHSYMBOL_H
