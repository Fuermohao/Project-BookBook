#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include <QTableWidgetItem>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BookBook");
    connect(ui->add,SIGNAL(clicked()),this,SLOT(AddSlot()));
    connect(ui->Del,SIGNAL(clicked()),this,SLOT(DelSlot()));
    connect(ui->save,SIGNAL(clicked()),this,SLOT(SaveSlot()));
    connect(ui->open,SIGNAL(clicked()),this,SLOT(OpenSlot()));
    connect(ui->pushButton_ok,SIGNAL(clicked()),this,SLOT(OpenNew()));
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(AddSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddSlot()
{
    QListWidgetItem *item=new QListWidgetItem;
    item->setText(ui->lineEdit->text());
    ui->listWidget->addItem(item);
    ui->lineEdit->clear();
     TableView();
}

void MainWindow::DelSlot()
{
    QListWidgetItem *item=ui->listWidget->currentItem();
    delete item;
     TableView();
}

void MainWindow::SaveSlot()
{


        int count=ui->listWidget->count();
        QString list;
        for(int i=0;i<count;i++)
        {
            list+=ui->listWidget->item(i)->text()+"\n";
        }
        QFile *file=new QFile;
        QString fileName=QFileDialog::getSaveFileName(this,"保存");
        file->setFileName(fileName);
        file->open(QIODevice::WriteOnly);
        QTextStream in(file);
        in<<list;
        file->close();
}

void MainWindow::OpenSlot()
{

    QFile *file=new QFile;
    QStringList files=QFileDialog::getOpenFileNames(this,"打开",QDir::homePath(),"*.txt");
    for(int i=0;i<files.length();i++)
    {
        file->setFileName(files.at(i));
        file->open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream in(file);
        while(!in.atEnd())
        {
            QListWidgetItem *item=new QListWidgetItem;
            item->setText(in.readLine());
            ui->listWidget_2->addItem(item);
        }
    }
    file->close();

}

void MainWindow::TableView()
{
    ui->tableWidget->setRowCount(40);
    ui->tableWidget->setColumnCount(ui->listWidget->count());


    for(int i=0;i<ui->listWidget->count();i++)
    {
        QTableWidgetItem *headerH=new QTableWidgetItem(ui->listWidget->item(i)->text());
        ui->tableWidget->setHorizontalHeaderItem(i,headerH);
    }
}

void MainWindow::OpenNew()
{
    ui->listWidget->clear();
    QFile *file=new QFile;
    QStringList files=QFileDialog::getOpenFileNames(this,"打开",QDir::homePath(),"*.txt");
    for(int i=0;i<files.length();i++)
    {
        file->setFileName(files.at(i));
        file->open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream in(file);
        while(!in.atEnd())
        {
            QListWidgetItem *item=new QListWidgetItem;
            item->setText(in.readLine());
            ui->listWidget->addItem(item);
        }
    }
    file->close();
    TableView();

}
