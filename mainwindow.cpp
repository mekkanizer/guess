#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "question.h"
#include "QWidget"
#include "database.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //db->connect();
    end_input();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_input()
{
    ui->label->show();
    ui->plainTextEdit->show();
    ui->pushButton->show();
}

void MainWindow::end_input()
{
    ui->label->hide();
    ui->plainTextEdit->hide();
    ui->pushButton->hide();
}

void MainWindow::on_question_triggered()
{
    start_input();
    ui->label->setText("Введите текст вопроса");
    question = true;
}

void MainWindow::on_solution_triggered()
{
    start_input();
    ui->label->setText("Введите текст решения");
    question = false;
}

void MainWindow::on_pushButton_clicked()
{
    if (question)
        db->add_knowledge("question", ui->plainTextEdit->toPlainText());
    else
        db->add_knowledge("solution", ui->plainTextEdit->toPlainText());
    end_input();
}

void MainWindow::on_start_triggered()
{
    Question* q = new Question(this);
    q->show();
    this->hide();
}
