#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QPointer>
#include <QJsonObject>
#include <memory>
#include "Network.h"
#include "ModelManager.h"

class MarianInterface;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // Network temporaries until I figure out a better way
    void onResult(QJsonObject obj, QString err);
    void handleDownload(QString filename, QByteArray data , QString err);
    void downloadProgress(qint64 ist, qint64 max);

private slots:
    void on_translateButton_clicked();

    void on_modelDownload_clicked();

    void on_Models_activated(int index);

    void on_localModels_activated(int index);

private:
    Ui::MainWindow *ui;
    MarianInterface * translator_; // Initialised to nullptr. Can't use smart ptrs due to destructor needing to run
    void resetTranslator(QString dirname);

    // Keep track of the models
    QStringList urls_;
    QStringList codes_;
    QStringList names_;

    // Model and config manager
    ModelManager models_;

    // Network code:
    Network network_;
};
#endif // MAINWINDOW_H
