#include "Network.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include <mainwindow.h>

Network::Network(QObject *parent)
    : QObject(parent)
    , nam_(new QNetworkAccessManager(this)) {}

void  Network::downloadFile(QString& urlstr) {
    auto processDownload = [&]() {
        QNetworkReply * reply = qobject_cast<QNetworkReply *>(sender());
        QByteArray result;
        QString filename = reply->url().fileName();
        QString err("");
        if (reply->error() == QNetworkReply::NoError) { // Success
            result = reply->readAll();
         } else {
            err = reply->errorString();
        }
        emit downloadComplete(filename, result, err);
        reply->deleteLater();
    };

    QNetworkReply *reply = nam_->get(QNetworkRequest(QUrl(urlstr)));
    connect(reply, &QNetworkReply::downloadProgress, this, &Network::progressBar);
    connect(reply, &QNetworkReply::finished, this, processDownload);
}

void  Network::downloadJson(QString& urlstr) {
    auto processJson = [&]() {
        QNetworkReply * reply = qobject_cast<QNetworkReply *>(sender());
        QJsonObject obj;
        QString err("");
        if (reply->error() == QNetworkReply::NoError) { // Success
            QByteArray result = reply->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(result);
            obj = jsonResponse.object();
        } else {
            err = reply->errorString();
        }
        emit getJson(obj, err);
        reply->deleteLater();
    };
    QUrl url(urlstr);
    QNetworkRequest req = QNetworkRequest(url);
    QNetworkReply * reply = nam_->get(req);
    connect(reply, &QNetworkReply::finished, this, processJson);
}
