#ifndef CONVERTER_H
#define CONVERTER_H
#pragma once
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>



class JsonManager {
public:

    //Чтение файла конфигурации JSON
    QJsonObject readConfig();

    //Чтение файла с запросами JSON
    QJsonObject readRequest();

    //Запись в файл с ответами на запросы JSON
    void writeResponse(QJsonObject responseObject);
};

#endif // CONVERTER_H
