#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QFileDialog>
#include <QStandardPaths>
#include <QRandomGenerator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString names_file = "./data/coco.names";
    QString cfg_file = "./cfg/yolov4.cfg";
    QString weights_file = "./model/yolov4.weights";
    m_pDetector = new QDetector(cfg_file, weights_file, names_file, 0, this);
    connect(m_pDetector, &QDetector::initCompleted, this, [=](){setDetectedImage("person.jpg");});
    ui->graphicsView->setScene(new QGraphicsScene(this));
}

MainWindow::~MainWindow()
{
    delete m_pDetector;
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,tr("Open Image"), QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).first(), tr("Image Files (*.png *.jpg *.bmp)"));
    setDetectedImage(file_name);
}

void MainWindow::setDetectedImage(const QString &file)
{
    if(!file.isEmpty() && m_pDetector != nullptr){
        ui->graphicsView->scene()->clear();
        ui->graphicsView->scene()->addPixmap(QPixmap(file));

        QJsonObject json_results = m_pDetector->detect(QImage(file), ui->doubleSpinBox_Thresh->value(), ui->checkBox_UseMean->isChecked());
        qDebug() << "json_results" << json_results;
        int cost_time = json_results.value("costTime").toInt();
        ui->label_FilePath->setText(file);
        ui->spinBox_CostTime->setValue(cost_time);

        QJsonArray json_arr_results = json_results.value("results").toArray();

        for(auto r : json_arr_results){
            QColor color = QColor::fromRgb(QRandomGenerator::global()->generate());
            QJsonObject json_result = r.toObject();

            QRectF rect = QRectF(json_result.value("x").toInt(),json_result.value("y").toInt(),
                                 json_result.value("width").toInt(),json_result.value("height").toInt());
            QString label = QString("%1: %2").arg(json_result.value("objectName").toString()).arg(json_result.value("probability").toDouble());

            ui->graphicsView->scene()->addRect(rect, QPen(color), QBrush(color, Qt::Dense7Pattern));
            QGraphicsTextItem *text = ui->graphicsView->scene()->addText(label);
            QPointF top_left = rect.topLeft();
            text->setPos(top_left.x(), top_left.y() - 18);
            text->setDefaultTextColor(color);
        }
    }
}

void MainWindow::on_pushButton_Detect_clicked()
{
    setDetectedImage(ui->label_FilePath->text());
}


void MainWindow::on_pushButton_ZoomIn_clicked()
{
    ui->graphicsView->scale(1.1, 1.1);
}

void MainWindow::on_pushButton_ZoomOut_clicked()
{
    ui->graphicsView->scale(0.9, 0.9);
}
