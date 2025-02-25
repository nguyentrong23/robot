#ifndef SETTINGHANDLER_H
#define SETTINGHANDLER_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QCborMap>
#include <QFile>
#include <QFileInfo>

#include <QDebug>

#include "MatchingROI.h"
#include "SystemConfig.h"
#include "modellist2save.h"
#include "lang_control.h""
class SettingHandler
{
public:
    enum FileType : int {
        Json,
        Dat
    };

    SettingHandler();

    void setFileName(QString name);
    void setFileType(FileType type);
    bool load(QString fullPath);
    bool save(QString fullPath);

private:
    void readValue(QJsonObject json);

public:
    MatchingROI matchingROI;
    SystemConfig systemConfig;
    ModelList2Save mlist;
    lang_control lang_control;

private:
    QFileInfo fileName;
    FileType fileType = Json;
};

#endif // SETTINGHANDLER_H
