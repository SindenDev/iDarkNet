#include "qdetector.h"
#include <QStandardPaths>
#include <QtConcurrent>
#include <QDateTime>
#include <QImage>
#include <QFile>
QDetector::QDetector(const QString &cfgFileName, const QString &weightFileName, const QString &namesFile, int gpuID, QObject *parent) : QObject(parent)
{
    QDateTime start = QDateTime::currentDateTime();
    QFile names_file(namesFile);
    if(names_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!names_file.atEnd()) {
             m_strNamesList.append(names_file.readLine().trimmed());
         }
    }
    QtConcurrent::run(QThreadPool::globalInstance(),[=](){
        qDebug() << "Start Init Detector";
        this->m_pDetector = new Detector(cfgFileName.toStdString(), weightFileName.toStdString(), gpuID);
        emit initCompleted();
        qDebug() << "Init Completed, Cost:" << start.msecsTo(QDateTime::currentDateTime()) << "ms";
    });
}

QDetector::~QDetector()
{
    if(this->m_pDetector != nullptr){
        delete this->m_pDetector;
    }
}

QJsonObject QDetector::detect(const QString &file, float thresh, bool useMean)
{
    QDateTime start = QDateTime::currentDateTime();
    QJsonObject json_results;
    QJsonArray json_arr_results;
    if(m_pDetector != nullptr){
        QEventLoop loop;
        QtConcurrent::run(QThreadPool::globalInstance(),[=, &loop, &json_arr_results](){
            auto results = this->m_pDetector->detect(file.toStdString(), thresh, useMean);

            for(auto r : results){
                QJsonObject json_result;
                json_result.insert("x", (int)r.x);
                json_result.insert("y", (int)r.y);
                json_result.insert("width", (int)r.w);
                json_result.insert("height", (int)r.h);
                json_result.insert("objectID", (int)r.obj_id);
                json_result.insert("objectName", m_strNamesList.at(r.obj_id));
                json_result.insert("probability", r.prob);
                json_result.insert("trackID", (int)r.track_id);
                json_result.insert("frames_counter", (int)r.frames_counter);
//                json_result.insert("x3D", r.x_3d);
//                json_result.insert("y3D", r.y_3d);
//                json_result.insert("z3D", r.z_3d);
                json_arr_results.append(json_result);
            }
            loop.quit();
        });
        loop.exec();
    }
    int cost_time = start.msecsTo(QDateTime::currentDateTime());
    json_results.insert("costTime", cost_time);
    json_results.insert("results", json_arr_results);
    return json_results;
}

QJsonObject QDetector::detect(const QImage &image, float thresh, bool useMean)
{
    QDateTime start = QDateTime::currentDateTime();
    QJsonObject json_results;
    QJsonArray json_arr_results;
    if(m_pDetector != nullptr){
        QEventLoop loop;
        QtConcurrent::run(QThreadPool::globalInstance(),[=, &loop, &json_arr_results](){
            QString file = QString("%1/darknet_detecting.png").arg(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
            image.save(file);

            auto results = this->m_pDetector->detect(file.toStdString(), thresh, useMean);

            for(auto r : results){
                QJsonObject json_result;
                json_result.insert("x", (int)r.x);
                json_result.insert("y", (int)r.y);
                json_result.insert("width", (int)r.w);
                json_result.insert("height", (int)r.h);
                json_result.insert("objectID", (int)r.obj_id);
                json_result.insert("objectName", m_strNamesList.at(r.obj_id));
                json_result.insert("probability", r.prob);
                json_result.insert("trackID", (int)r.track_id);
                json_result.insert("frames_counter", (int)r.frames_counter);
//                json_result.insert("x3D", r.x_3d);
//                json_result.insert("y3D", r.y_3d);
//                json_result.insert("z3D", r.z_3d);
                json_arr_results.append(json_result);
            }
            loop.quit();
        });
        loop.exec();
    }
    int cost_time = start.msecsTo(QDateTime::currentDateTime());
    json_results.insert("costTime", cost_time);
    json_results.insert("results", json_arr_results);
    return json_results;
}

const QString QDetector::getNameByID(int id) &
{
    return id  < m_strNamesList.length() ? m_strNamesList.at(id) : QString();
}
