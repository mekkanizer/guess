#ifndef QUESTION_H
#define QUESTION_H

#include <QDialog>

namespace Ui {
class Question;
}

class Question : public QDialog
{
    Q_OBJECT

public:
    explicit Question(QWidget *parent = 0);
    ~Question();

private:
    Ui::Question *ui;
};

#endif // QUESTION_H
