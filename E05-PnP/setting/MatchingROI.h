#ifndef MATCHINGROI_H
#define MATCHINGROI_H

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

class MatchingROI
{
public:
    MatchingROI() {}
    MatchingROI(Point topleft, Point bottomright);

    Point TopLeft;
    Point BottomRight;

    QJsonObject ToJson();
    void FromJson(QJsonObject json);
    static QJsonObject PointToJson(Point jPoint);
    static void JsonToPoint(const QJsonValue &json, Point &point);
};
#endif // MATCHINGROI_H
