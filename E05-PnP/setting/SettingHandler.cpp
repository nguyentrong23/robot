#include "SettingHandler.h"

SettingHandler::SettingHandler()
{

}

void SettingHandler::setFileName(QString name) {
    fileName.setFile(name);
}

void SettingHandler::setFileType(FileType type) {
    fileType = type;
}



bool SettingHandler::save(QString fullPath) {
    fileName.setFile(fullPath);

    QString fileExtension = fileName.suffix();
    if( ((fileType == Json) && (fileExtension != "json")) ||
        ((fileType == Dat) && (fileExtension != "dat"))) {
        return false;
    }

    QFile saveFile(fileName.absoluteFilePath());

    if (!saveFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    QJsonObject MatchRoi;
    MatchRoi["Matching_ROI"] = matchingROI.ToJson();

    QJsonObject SystemConfig;
    SystemConfig["System_Config"] = systemConfig.ToJson();

    QJsonObject listOfModel;
    listOfModel["list_path"] =  mlist.ToJson();

    QJsonObject lang;
    lang["lang"] =  lang_control.ToJson();

    QJsonObject combinedObject;
    combinedObject["Matching_ROI"] = MatchRoi["Matching_ROI"].toObject();
    combinedObject["System_Config"] = SystemConfig["System_Config"].toObject();
    combinedObject["list_path"] = listOfModel["list_path"].toObject();
    combinedObject["lang"] = lang["lang"].toObject();

    saveFile.write((fileType == Json) ? QJsonDocument(combinedObject).toJson()
                                      : QCborValue::fromJsonValue(combinedObject).toCbor());
    return true;
}

bool SettingHandler::load(QString fullPath) {
    fileName.setFile(fullPath);

    QString fileExtension = fileName.suffix();
    if( ((fileType == Json) && (fileExtension != "json")) ||
        ((fileType == Dat) && (fileExtension != "dat"))) {
        return false;
    }

    QFile loadFile(fileName.absoluteFilePath());
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << loadFile.errorString();
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc((fileType == Json) ? QJsonDocument::fromJson(saveData)
                                             : QJsonDocument(QCborValue::fromCbor(saveData).toMap().toJsonObject()));

     readValue(loadDoc.object());
    return true;
}

void SettingHandler::readValue(const QJsonObject json) {
    if (json.contains("Matching_ROI")) {
        QJsonObject matchingROIObject = json["Matching_ROI"].toObject();
        matchingROI.FromJson(matchingROIObject);
    }

    if (json.contains("System_Config")) {
        QJsonObject systemConfigObject = json["System_Config"].toObject();
        systemConfig.FromJson(systemConfigObject);
    }

    if (json.contains("list_path"))
    {
        QJsonObject listPathObject = json["list_path"].toObject();
        mlist.FromJson(listPathObject);
    }

    if (json.contains("lang"))
    {
        QJsonValue langVal = json["lang"];
        if (langVal.isObject()) {
            QJsonObject clang = langVal.toObject();
            lang_control.FromJson(clang);
        }
    }

}




//        qDebug() << "Top left: " << matchingROI.TopLeft.x << " - " << matchingROI.TopLeft.y;
//        qDebug() << "Bottom right: " << matchingROI.BottomRight.x << " - " << matchingROI.BottomRight.y;
