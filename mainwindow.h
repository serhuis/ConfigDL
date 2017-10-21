#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QProgressBar>
#include <QTimer>

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
    QSerialPort * mPort;
    QByteArray mInBuffer;
    QProgressBar *statusProgBar;
    QTimer *mTimer;
    int mCnt;

private slots:
    void readyRead();
    void timerSlot();


private:
    void serialParser(QByteArray &);


};

#endif // MAINWINDOW_H
