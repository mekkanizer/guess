#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void input();
    void on_question_triggered();

    void on_solution_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool question;
};

#endif // MAINWINDOW_H
