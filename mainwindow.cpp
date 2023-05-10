#include "mainwindow.h"

#include <iostream>
#include <string>
#include <sstream>

#include <ui_map.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Form)
{
    ui->setupUi(this);
    setWindowTitle("Find Path!");

    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadData()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(findPath()));

    // @TODO: write your code here
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    // @TODO: write your code here
}

void MainWindow::loadData() {
    QFile file;
    file.setFileName(QFileDialog::getOpenFileName(this, tr("从文件导入"), QCoreApplication::applicationDirPath(), tr("数据文件(*.txt)")));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray data = file.readAll();
    QTextStream ts(data);

    int m, n;
    ts >> m >> n;
    field.initField(m, n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            ts >> field[i][j];

    layout = new QGridLayout();
    layout->setSpacing(2);
    layout->setMargin(4);

    QPalette pa;
    label = new QLabel**[m];
    for (int i = 0; i < m; i++) {
        label[i] = new QLabel*[n];
        for (int j = 0; j < n; j++) {
            QLabel *lb = new QLabel();
            pa.setColor(QPalette::Window, field[i][j] ? hasCandy : noCandy);
            lb->setAutoFillBackground(true);
            lb->setPalette(pa);
            lb->setText(tr("%1").arg(field[i][j]));
            label[i][j] = lb;
            layout->addWidget(lb, i, j);
        }
    }

    ui->widget->setLayout(layout);

    file.close();
}

void MainWindow::findPath(){
    // @TODO: write your code here
    // You can add parameters to this method as needed
    field.findPath();
    showResult();
}

void MainWindow::showResult(){
    // @TODO: write your code here
    QPalette pa;
    pa.setColor(QPalette::Window, pathColor);
    for (int i = 0; i < field.m; i++)
        for (int j = 0; j < field.n; j++)
            if (field[i][j] == -3)
                label[i][j]->setPalette(pa);
}

void MainWindow::paintEvent(QPaintEvent *){
    // @TODO: write your code here
}
