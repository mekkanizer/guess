#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "question.h"
#include "QWidget"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->hide();
    ui->plainTextEdit->hide();
    ui->pushButton->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::input()
{
    ui->label->show();
    ui->plainTextEdit->show();
    ui->pushButton->show();
}

void MainWindow::on_question_triggered()
{
    input();
    question = true;
}

void MainWindow::on_solution_triggered()
{
    input();
    question = false;
}

void MainWindow::on_pushButton_clicked()
{
    if (question)
    {

    }
    else
    {

    }
}
