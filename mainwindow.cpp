#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "question.h"
#include "QWidget"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect (ui->pushButton,SIGNAL(clicked()),this,SLOT(click()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::click()
{
    Question* q = new Question(this);
    q->show();
    this->hide();
}
