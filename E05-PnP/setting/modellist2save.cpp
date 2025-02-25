#include "modellist2save.h"

ModelList2Save::ModelList2Save() {
}

ModelList2Save::ModelList2Save(vector<ImageMatch::GeoModel> listmodel)
{
    Listmodel = listmodel;
}

QJsonObject ModelList2Save::ToJson() {
    QJsonObject json;
    for(int index =0;index < Listmodel.size();index++)
    {   QJsonObject jtem;
        QString label = QString::fromStdString(Listmodel[index].getModelFileName());
        jtem[label] = QString::fromStdString(Listmodel[index].getPathOfModel());
        jtem["x"] =Listmodel[index].pickPosition.x;
        jtem["y"] =Listmodel[index].pickPosition.y;
        json[label] = jtem;
        qDebug()<<"label" << label<< Listmodel[index].pickPosition.x<<Listmodel[index].pickPosition.y;
    }
    return json;
}

void ModelList2Save::FromJson(QJsonObject json) {
    unordered_map<QString, pair<QString, Point>> result;
    for (auto it = json.begin(); it != json.end(); ++it) {
        QString label = it.key();
        QJsonObject modelData = it.value().toObject();
        QString path = modelData[label].toString(); // Truy cập và chuyển đổi thành QString
        int pickX = modelData["x"].toInt();
        int pickY = modelData["y"].toInt();
        Point demo(pickX, pickY);
        result[label] = make_pair(path, demo);
    }
    Model_dic = result;
}
