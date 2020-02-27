#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <iostream>
#include <string.h>
#include <syscall.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_downloadButton_clicked();

    void on_optionsButton_clicked();

    void onReadyReadStandardError();

    void readyReadStandardOutput();

    void onFinished();

    void on_stopDownload_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
