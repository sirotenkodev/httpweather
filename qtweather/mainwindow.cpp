#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QUrl>
#include <QPixmap>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_networkManager{std::make_unique<QNetworkAccessManager>()},
    m_url{std::make_unique<QUrl>("http://localhost:3000/getjsondata")},
    m_city{"Moscow"}

{
    ui->setupUi(this);
    QUrlQuery q;
    q.addQueryItem("city", m_city);
    m_url->setQuery(q);
    connect(m_networkManager.get(), &QNetworkAccessManager::finished, this, &MainWindow::getWeatherJson);
    m_networkManager->get(
                QNetworkRequest(m_url->url())
                );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getWeatherJson(QNetworkReply *reply)
{
    if(!reply->error()){
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = document.object();
        ui->cityLabel->setText(root.value("citydata").toString());
        ui->weatherLabel->setText(QString::number(root.value("tempdata").toDouble()) + "°C");
        ui->descriptionLabel->setText(root.value("descriptiondata").toString());
        QPixmap pixmap("icons/" + root.value("imgdata").toString() + ".png");
        ui->imageLabel->setPixmap(pixmap);
    }

    reply->deleteLater();
}


void MainWindow::on_searchButton_clicked()
{
    if(!ui->cityInput->text().isEmpty()) {
        m_city = ui->cityInput->text();
        QUrlQuery q;
        q.addQueryItem("city", m_city);
        m_url->setQuery(q);
        m_networkManager->get(
                    QNetworkRequest(m_url->url())
                    );
    }

}

