#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "error.h"

using namespace std;

static QString destiny;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_downloadButton_clicked()
{
    if(ui->urlBox->text().isEmpty() || ui->destinationBox->text().isEmpty()){
        Error e;
        e.show();
        e.exec();
    }
    else {
        string url, dUrl, format, query, queryName, name;
        int indexFormat;
        url = ui->urlBox->text().toStdString();
        dUrl = ui->destinationBox->text().toStdString();
        indexFormat = ui->formatBox->currentIndex();

        switch (indexFormat) {
            case 0:
                format = "best";
                break;
            case 1:
                format = "worse";
                break;
            case 2:
                format = "bestvideo";
                break;
            case 3:
                format = "worsevideo";
                break;
            case 4:
                format = "bestaudio";
                break;
            case 5:
                format = "worseaudio";
                break;
        }

        /*queryName = "youtube-dl --get-filename "+url;

        system(queryName.data());*/

        query = "youtube-dl -o "+dUrl+"/'%(title)s.%(ext)s' -f "+format+" "+url;

        system(query.data());
    }
}

void MainWindow::on_optionsButton_clicked()
{
    destiny = QFileDialog::getSaveFileUrl().toString();
    ui->destinationBox->setText(destiny.remove(0,7)); //file:// = 7
}