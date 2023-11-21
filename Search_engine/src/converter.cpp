#include "include/converter.h"


//Метод получения содержимого файлов
//Возвращает список с содержимым файлов перечисленных в config.json
std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::vector<std::string> textDocuments;
    QFile file("config.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject obj = doc.object();
        QJsonArray files = obj["files"].toArray();
        for (const auto& file : files) {
            textDocuments.push_back(file.toString().toStdString());
         }
     }
   return textDocuments;
}

//Метод считывает поле max_responses для определения предельного количества ответов на один запрос
int ConverterJSON::GetResponsesLimit()
{
    int limit = 0;
    QFile file("config.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject obj = doc.object();
        limit = obj["max_responses"].toInt();
    }
    return limit;
}


//Метод получения запросов из файла requests.json
//Возвращает список запросов из файла requests.json

std::vector<std::string> ConverterJSON::GetRequests()
{
    std::vector<std::string> requests;
    QFile file("requests.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
       QJsonArray arr = doc.array();
       for (const auto& request : arr) {
           requests.push_back(request.toString().toStdString());
       }
    }
    return requests;
}

//Положить в файл answers.json результаты поисковых запросов
void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{
    QJsonArray mainArray;
    for (const auto& ans : answers) {
         QJsonArray subArray;
         for (const auto& pair : ans) {
             QJsonObject obj;
             obj["doc_id"] = pair.first;
             obj["score"] = pair.second;
             subArray.append(obj);
         }
         mainArray.append(subArray);
    }
    QFile file("answers.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonDocument doc(mainArray);
        file.write(doc.toJson());
    }
}
