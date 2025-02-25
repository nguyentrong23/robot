#ifndef LIST_TEMP_H
#define LIST_TEMP_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QCborMap>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include <unordered_map>
#include <opencv2/core.hpp>
#include "camera/GeoModel.h"
using namespace cv;

class ModelList2Save
{
public:
    /// para
    vector<ImageMatch::GeoModel> Listmodel;

    /// function
    ModelList2Sale() {
    }

    ModelList2Sale(vector<ImageMatch::GeoModel> listmodel) {
        Listmodel = listmodel;
    }

    QJsonObject ToJson() {
        QJsonObject json;
        for(int index =0;index < Listmodel.size();index++)
        {  QString label = QString::fromStdString(Listmodel[index].getNameofModel());
            json[label] = QString::fromStdString(Listmodel[index].getModelPath());
        }
        return json;
    }

    unordered_map<QString, QString> FromJson(QJsonObject json) {
        unordered_map<QString, QString> result;
        for (auto it = json.begin(); it != json.end(); ++it) {
            QString label = it.key();
            QString path = it.value().toString();
            result[label]=path;
        }
        return result;
    }

    unordered_map<QString, QString> Model_dic;
};


#endif // LIST_TEMP_H
