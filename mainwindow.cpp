#include "mainwindow.h"
#include "Treev4.h"
#include "ui_mainwindow.h"
using namespace std;
PNode tree1;
int GlobalFlag=0;
bool Letter_Check;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_But_ready_clicked()
{

    if (ui->Expression->text()!="")
        //GlobalFlag=1;
    {

    }
    else
    {
        ui->statusbar->showMessage("Что-то пошло не так...");
        return;
    }
    QString expr = ui->Expression->text();
    string sexpr = expr.toStdString();
    sexpr = deletewhitespaces(sexpr);
    Letter_Check = Check_on_Letters(sexpr);
    int ExprLenght= sexpr.length();
    if (Check_on_Brackets(sexpr) && Znak_Repeat_Test(sexpr) && Allowed_Signs(sexpr) && !Is_Sign(sexpr[-1])){
        GlobalFlag=1;
        tree1 = maketree(sexpr,0,ExprLenght);
        ui->statusbar->showMessage("Обработка дерева завершена!");
    }
    else
    {
        GlobalFlag=0;
        ui->statusbar->showMessage("В выражении ошибка, обработка не выполнена");
    }

}
void MainWindow::on_But_LKP_clicked()
{
    if (GlobalFlag==1){
        QFont newfont("Segoe UI", 16);
        ui->label_for_round->setFont(newfont);
        ui->label_for_round->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        string toshow = printLKP(tree1);
        QString qshow = QString::fromStdString(toshow);
        //ui->label_for_round->clear();
        ui->label_for_round->setText(qshow);
        ui->statusbar->showMessage("Дерево в виде Левое-Корень-Правое:");
    }
    else
    {
        ui->statusbar->showMessage("Что-то пошло не так...");
    }

}
void MainWindow::on_But_KLP_clicked()
{
    if (GlobalFlag==1){
        QFont newfont("Segoe UI", 16);
        ui->label_for_round->setFont(newfont);
        ui->label_for_round->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        string toshow = printKLP(tree1);
        QString qshow = QString::fromStdString(toshow);
        //ui->label_for_round->clear();
        ui->label_for_round->setText(qshow);
        ui->statusbar->showMessage("Дерево в виде Корень-Левое-Правое:");
    }
    else
    {
        ui->statusbar->showMessage("Что-то пошло не так...");
    }
}


void MainWindow::on_But_LPK_clicked()
{
    if (GlobalFlag==1){
        QFont newfont("Segoe UI", 16);
        ui->label_for_round->setFont(newfont);
        ui->label_for_round->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        string toshow = printLPK(tree1);
        QString qshow = QString::fromStdString(toshow);
        //ui->label_for_round->clear();
        ui->label_for_round->setText(qshow);
        ui->statusbar->showMessage("Дерево в виде Левое-Правое-Корень:");
    }
    else
    {
        ui->statusbar->showMessage("Что-то пошло не так...");
    }
}


void MainWindow::on_But_justtree_clicked()
{
    if (GlobalFlag==1){
        QFont newfont("Segoe UI", 8);
        ui->label_output->setFont(newfont);
        ui->label_output->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        string toshow = Print_Deep(tree1,10);
        QString qshow = QString::fromStdString(toshow);
        //ui->label_output->clear();
        ui->label_output->setText(qshow);
        ui->statusbar->showMessage("Стандартный вывод дерева: ");
    }
    else
    {
        ui->statusbar->showMessage("Что-то пошло не так...");
    }
}
void MainWindow::on_But_calctree_clicked()
{
    if (GlobalFlag==1 && Letter_Check)//поменять с поиска блэк листа на вайт лист
    {
        int res = calctree(tree1);
        QFont newfont("Segoe UI", 16);
        ui->label_for_round->setFont(newfont);
        ui->label_for_round->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->label_for_round->setNum(res);
        ui->statusbar->showMessage("Вычисление выполнено!");
    }
    /*
        else if (!Letter_Check){
        ui->statusbar->showMessage("Вычисление выражения невозможно, т. к. в нём есть буквы");
        }
    */
    else
    {
        ui->statusbar->showMessage("Что-то пошло не так...");
    }
}
void MainWindow::on_BFS_clicked()
{
    if (GlobalFlag==1){
        QFont newfont("Segoe UI", 16);
        ui->label_for_round->setFont(newfont);
        ui->label_for_round->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        string toshow = Print_Width(tree1);
        QString qshow = QString::fromStdString(toshow);
        //ui->label_for_round->clear();
        ui->label_for_round->setText(qshow);
        ui->statusbar->showMessage("Обход дерева в ширину:");
    }
    else
    {
        ui->statusbar->showMessage("Что-то пошло не так...");
    }
}

