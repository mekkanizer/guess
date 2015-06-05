#include "question.h"
#include "ui_question.h"

Question::Question(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Question)
{
    ui->setupUi(this);
}

Question::~Question()
{
    delete ui;
}
