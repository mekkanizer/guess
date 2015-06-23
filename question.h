#ifndef QUESTION_H
#define QUESTION_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Question;
}

class Question : public QDialog
{
    Q_OBJECT

public:
    explicit Question(QWidget *parent = 0);
    ~Question();

private slots:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    void answer_click(int answer);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Question *ui;
};

#endif // QUESTION_H
