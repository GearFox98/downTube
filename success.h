#ifndef SUCCESS_H
#define SUCCESS_H

#include <QDialog>

namespace Ui {
class Success;
}

class Success : public QDialog
{
    Q_OBJECT

public:
    explicit Success(QWidget *parent = nullptr);
    ~Success();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Success *ui;
};

#endif // SUCCESS_H
