#include "lang_control.h"

lang_control::lang_control() {}

lang_control::lang_control(int lang) {
    lang_curr = lang;
}

QJsonObject lang_control::ToJson()
{
    QJsonObject json;
    json["lang_curr"] = lang_curr;
    qDebug() << "lang_curr in "<<lang_curr;
    return json;
}

void lang_control::FromJson(QJsonObject json) {
    QJsonValue jsonVal = json["lang_curr"];
    if (jsonVal.isDouble() || jsonVal.isString()) {
        lang_curr = jsonVal.toInt();
        // qDebug() << "lang_curr out" << lang_curr;
    }
}
