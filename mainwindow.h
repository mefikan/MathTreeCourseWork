#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_But_ready_clicked();

    void on_But_LKP_clicked();



    void on_But_KLP_clicked();

    void on_But_LPK_clicked();

    void on_But_justtree_clicked();

    void on_But_calctree_clicked();



    void on_BFS_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
