#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void getWeatherJson(QNetworkReply *reply);

    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<QNetworkAccessManager> m_networkManager;
    std::unique_ptr<QUrl> m_url;
    QString m_city;
};
#endif // MAINWINDOW_H
