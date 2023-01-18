#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 8080);

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    nextBlockSize = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::SendToServer(QString str){

    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_4);
    if(in.status() == QDataStream::Ok){
        for(;;){
            if(nextBlockSize == 0){
                if(socket->bytesAvailable() < 2)
                    break;
                in >> nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
                break;
            QString str;
            in >> str;
            nextBlockSize = 0;
            ui->responsesField->append(str);

        }
    }
    else{
        ui->responsesField->append("Read error");
    }
}



////////
void MainWindow::on_sendMessage_clicked()
{
    SendToServer(ui->requestsField->toPlainText());
    ui->requestsField->clear();
}



void MainWindow::on_requestsField_textChanged()
{

}


void MainWindow::on_responsesField_historyChanged()
{

}
