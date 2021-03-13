#ifndef TERMSOFSERVICE_H
#define TERMSOFSERVICE_H

#include <QDialog>

namespace Ui {
class TermsOfService;
}

class TermsOfService : public QDialog{
    Q_OBJECT

public:
    explicit TermsOfService(QWidget *parent = nullptr);
    TermsOfService() =delete;
    TermsOfService(const TermsOfService & assignThis) = delete;
    TermsOfService & operator = (const TermsOfService & assignThis) = delete;
    ~TermsOfService();

private:
    Ui::TermsOfService *ui;
};

#endif // TERMSOFSERVICE_H
