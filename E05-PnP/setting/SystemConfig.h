#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QCborMap>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

class SystemConfig
{
public:

    struct StRobot
    {
        QString ipAddress = "";
        int port = 1;
    };

    struct StDhrConfig
    {
        int baudRate = 115200;
        int serialPort = 4;
        int dataBit = 8;
        int stopBit = 1;
    };

    struct StLastState
    {
        int totalObjectPicked = 0;
    };


    SystemConfig(){}
    SystemConfig(StRobot robot_config, StRobot camera_config, StRobot vibrating_plate_config,
                 StRobot fx_plc_config, StDhrConfig dhr_config, StLastState last_state);

    StRobot RobotConfig;
    StRobot VibratingPlateConfig;
    StRobot CameraConfig;
    StRobot FxPlcConfig;
    StDhrConfig DhrConfig;
    StLastState LastState;

    QJsonObject ToJson();
    void FromJson(QJsonObject json);
    static QJsonObject PointToJson(StRobot jPoint);
    static void JsonToPoint(const QJsonValue &json, StRobot &point);
    static QJsonObject PointToJsonDhr(StDhrConfig jPoint);
    static void JsonToPointDhr(const QJsonValue &json, StDhrConfig &point);
    static QJsonObject PointToJsonLastState(StLastState jPoint);
    static void JsonToPointLastState(const QJsonValue &json, StLastState &point);

};

#endif // SYSTEMCONFIG_H
