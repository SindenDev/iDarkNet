#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include "qdetector.h"

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
    void on_actionOpen_triggered();

    void on_pushButton_Detect_clicked();

private:
    Ui::MainWindow *ui;
    QDetector *m_pDetector = nullptr;

    void setDetectedImage(const QString &file);
};
#endif // MAINWINDOW_H
