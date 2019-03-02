#ifndef SOLVE_H
#define SOLVE_H

#include <QMainWindow>

namespace Ui {
class Solve;
}

class Solve : public QMainWindow
{
    Q_OBJECT

public:
    explicit Solve(QWidget *parent = nullptr);
    ~Solve();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Solve *ui;
};

#endif // SOLVE_H
