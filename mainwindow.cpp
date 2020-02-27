#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "error.h"
#include <QProcess>
#include <QtWidgets>

using namespace std;

static QString destiny;
static QProcess *process(new QProcess);

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

        query = "-o "+dUrl+"/%(title)s.%(ext)s -f "+format+" "+url;
        QString Query = query.data();

        process->setProgram("youtube-dl");
        connect(process, &QProcess::readyReadStandardError, this, &MainWindow::onReadyReadStandardError);
        connect(process, &QProcess::readyReadStandardOutput, this, &MainWindow::readyReadStandardOutput);
        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MainWindow::onFinished);
        process->setArguments(Query.split(" "));
        process->start();
        ui->downloadButton->setEnabled(false);
        ui->stopDownload->setEnabled(true);
    }
}

void MainWindow::onReadyReadStandardError(){
    ui->consoleBox->appendPlainText(process->readAllStandardError().constData());
}

void MainWindow::readyReadStandardOutput(){
    ui->consoleBox->appendPlainText(process->readAllStandardOutput().constData());
}

void MainWindow::onFinished(){
    ui->downloadButton->setEnabled(true);
    ui->stopDownload->setEnabled(false);
}

void MainWindow::on_optionsButton_clicked()
{
    destiny = QFileDialog::getExistingDirectoryUrl().toString();
    ui->destinationBox->setText(destiny.remove(0,7)); //file:// = 7
}

void MainWindow::on_stopDownload_clicked()
{
    process->kill();
    ui->downloadButton->setEnabled(true);
}
