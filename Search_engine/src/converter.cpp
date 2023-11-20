#include "include/converter.h"


////Чтение файла конфигурации JSON
QJsonObject JsonManager::readConfig()
{
    QFile file("config.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open config file";
        return QJsonObject();
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    return doc.object();
}

//Чтение файла с запросами JSON
QJsonObject JsonManager::readRequest()
{
    QFile file("requests.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open requests file";
        return QJsonObject();
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    return doc.object();
}

//Запись в файл с ответами на запросы JSON
void JsonManager::writeResponse(QJsonObject responseObject)
{
    QJsonDocument doc(responseObject);
    QByteArray jsonData = doc.toJson();

    QFile file("answers.json");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open answers file";
        return;
    }

    file.write(jsonData);
}
