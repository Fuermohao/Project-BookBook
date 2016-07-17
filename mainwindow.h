#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void AddSlot();
    void DelSlot();
    void SaveSlot();
    void OpenSlot();
    void TableView();
    void OpenNew();
};

#endif // MAINWINDOW_H
