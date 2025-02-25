#include "MatchingROI.h"

MatchingROI::MatchingROI(Point topleft, Point bottomright) {
    TopLeft = topleft;
    BottomRight = bottomright;
}

QJsonObject MatchingROI::ToJson() {
    QJsonObject json;
    json["Top_Left"] = PointToJson(TopLeft);
    json["Bottom_Right"] = PointToJson(BottomRight);
    return json;
}

void MatchingROI::FromJson(QJsonObject json) {
    if (const QJsonValue jsonVal = json["Top_Left"]; jsonVal.isObject()) {
        JsonToPoint(jsonVal, TopLeft);
    }
    if (const QJsonValue jsonVal = json["Bottom_Right"]; jsonVal.isObject()) {
        JsonToPoint(jsonVal, BottomRight);
    }
}

QJsonObject MatchingROI::PointToJson(Point jPoint) {
    QJsonObject json;
    json["X"] = jPoint.x;
    json["Y"] = jPoint.y;
    return json;
}

void MatchingROI::JsonToPoint(const QJsonValue &json, Point &point) {
    point.x = json["X"].toInt();
    point.y = json["Y"].toInt();
}
