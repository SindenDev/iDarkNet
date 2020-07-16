#ifndef QDETECTOR_H
#define QDETECTOR_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include "yolo_v2_class.hpp"

class QDetector : public QObject
{
    Q_OBJECT
public:
    explicit QDetector(const QString &cfgFileName, const QString &weightFileName, const QString &namesFile, int gpuID = 0, QObject *parent = nullptr);
    ~QDetector();
    QJsonObject detect(const QString &file, float thresh = 0.25, bool useMean = false);
    QJsonObject detect(const QImage &image, float thresh = 0.25, bool useMean = false);
    const QString getNameByID(int id) &;

Q_SIGNALS:
    void initCompleted();

private:
    QStringList m_strNamesList;
    Detector *m_pDetector = nullptr;
};

#endif // QDETECTOR_H
