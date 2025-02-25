#include "SystemConfig.h"

SystemConfig::SystemConfig(StRobot robot_config, StRobot camera_config, StRobot vibrating_plate_config, StRobot fx_plc_config, StDhrConfig dhr_config, StLastState last_state) {
    RobotConfig = robot_config;
    VibratingPlateConfig = vibrating_plate_config;
    CameraConfig =camera_config;
    FxPlcConfig = fx_plc_config;
    DhrConfig = dhr_config;
    LastState = last_state;
}

QJsonObject SystemConfig::ToJson() {
    QJsonObject json;
    json["Robot"] = PointToJson(RobotConfig);
    json["Camera"] = PointToJson(CameraConfig);
    json["Vibrating_Plate"] = PointToJson(VibratingPlateConfig);
    json["Dhr_Device"] = PointToJsonDhr(DhrConfig);
    json["Fx_Plc"] = PointToJson(FxPlcConfig);
    json["Last_State"] = PointToJsonLastState(LastState);
    return json;
}

void SystemConfig::FromJson(QJsonObject json) {
    if (const QJsonValue jsonVal = json["Robot"]; jsonVal.isObject()) {
        JsonToPoint(jsonVal, RobotConfig);
    }
    if (const QJsonValue jsonVal = json["Camera"]; jsonVal.isObject()) {
        JsonToPoint(jsonVal, CameraConfig);
    }
    if (const QJsonValue jsonVal = json["Vibrating_Plate"]; jsonVal.isObject()) {
        JsonToPoint(jsonVal, VibratingPlateConfig);
    }
    if (const QJsonValue jsonVal = json["Dhr_Device"]; jsonVal.isObject()) {
        JsonToPointDhr(jsonVal, DhrConfig);
    }
    if (const QJsonValue jsonVal = json["Fx_Plc"]; jsonVal.isObject()) {
        JsonToPoint(jsonVal, FxPlcConfig);
    }
    if (const QJsonValue jsonVal = json["Last_State"]; jsonVal.isObject()) {
        JsonToPointLastState(jsonVal, LastState);
    }
}

QJsonObject SystemConfig::PointToJson(StRobot jPoint) {
    QJsonObject json;
    json["Ip_Address"] = jPoint.ipAddress;
    json["Port"] = jPoint.port;
    return json;
}

void SystemConfig::JsonToPoint(const QJsonValue &json, StRobot &point) {
    point.ipAddress = json["Ip_Address"].toString();
    point.port = json["Port"].toInt();
}

QJsonObject SystemConfig::PointToJsonDhr(StDhrConfig jPoint) {
    QJsonObject json;
    json["Baud_Rate"] = jPoint.baudRate;
    json["Port"] = jPoint.serialPort;
    json["Data_Bit"] = jPoint.dataBit;
    json["Stop_Bit"] = jPoint.stopBit;
    return json;
}

void SystemConfig::JsonToPointDhr(const QJsonValue &json, StDhrConfig &point) {
    point.baudRate = json["Baud_Rate"].toInt();
    point.serialPort = json["Port"].toInt();
    point.dataBit = json["Data_Bit"].toInt();
    point.stopBit = json["Stop_Bit"].toInt();
}

QJsonObject SystemConfig::PointToJsonLastState(StLastState jPoint) {
    QJsonObject json;
    json["Total_Object_Picked"] = jPoint.totalObjectPicked;
    return json;
}

void SystemConfig::JsonToPointLastState(const QJsonValue &json, StLastState &point) {
    point.totalObjectPicked = json["Total_Object_Picked"].toInt();
}
