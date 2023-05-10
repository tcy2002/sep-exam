#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QPlainTextEdit>
#include <QWidget>
#include <QtWidgets>

#include "field.h"

namespace Ui {
class Form;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void loadData();
    void findPath();

private:
    Ui::Form *ui;
    QColor noCandy = QColor("yellow");
    QColor hasCandy = QColor("lightGreen");
    QColor pathColor = QColor("lightBlue");

    Field field{};

    QGridLayout *layout;
    QLabel ***label;

    void showResult();
};

#endif // MAINWINDOW_H
