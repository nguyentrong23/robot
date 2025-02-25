#ifndef MODELLIST2SAVE_H
#define MODELLIST2SAVE_H

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
    ModelList2Save() ;
    ModelList2Save(vector<ImageMatch::GeoModel> listmodel) ;

    QJsonObject ToJson() ;
    void FromJson(QJsonObject json) ;
    unordered_map<QString, pair<QString, Point>> Model_dic;
};

#endif // MODELLIST2SAVE_H
