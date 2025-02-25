#ifndef LANG_CONTROL_H
#define LANG_CONTROL_H


#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QCborMap>
#include <QFile>
#include <QFileInfo>

#include <QDebug>

#include <opencv2/core.hpp>
using namespace cv;

class lang_control
{
public:
    lang_control();
    lang_control(int lang_type);
    QJsonObject ToJson();
    void FromJson(QJsonObject json);
    int lang_curr;
};

#endif // LANG_CONTROL_H
