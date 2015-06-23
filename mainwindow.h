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
    void start_input();
    void end_input();
    void on_question_triggered();

    void on_solution_triggered();

    void on_pushButton_clicked();

    void on_start_triggered();

private:
    Ui::MainWindow *ui;
    bool question;
};

#endif // MAINWINDOW_H
