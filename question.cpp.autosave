#include "question.h"
#include "ui_question.h"
#include "mainwindow.h"
#include "database.h"

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

void Question::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->show();
}

void Question::showEvent(QShowEvent *event)
{
    ui->label->setText(db->get_question());
    ui->groupBox->hide();
}

void Question::answer_click(int answer)
{
    db->add_answer(answer);
    if (db->get_solution() == "nope")
        ui->label->setText(db->get_question());
    else
        ui->groupBox->hide();
}

void Question::on_pushButton_clicked()
{
    answer_click(1);
}

void Question::on_pushButton_2_clicked()
{
    answer_click(2);
}

void Question::on_pushButton_3_clicked()
{
    answer_click(3);
}

void Question::on_pushButton_4_clicked()
{
    answer_click(4);
}
