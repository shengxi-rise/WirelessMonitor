//
// Created by xtx on 2022/9/15.
//

#ifndef QT_REPEATERWIDGET_H
#define QT_REPEATERWIDGET_H


#include <QFrame>
#include <QtWidgets/QPushButton>
#include <QSettings>

typedef struct DataNode{
    double *DataBuff;
    bool flag;//判断是否画图
}Datanode;

namespace Ui {
class Charts;
}

typedef std::map<std::string, QPushButton> QPushButtonMap;
enum WindowsType
{
    None,
    ChannelConfiguration,
    XCOM,
    MainChart,

};
struct RequestNewWidget {
    WindowsType widgetType;
    int DeviceNum;
};
class RepeaterWidget : public QWidget {
public:
//    QPushButtonMap Button;
    explicit RepeaterWidget(QWidget *parent = nullptr);
    ~RepeaterWidget();
    virtual void GetObjectFromUI(QPushButtonMap &result);
    virtual void GetConstructConfig();
    virtual void SaveConstructConfig();
    virtual Ui::Charts *GetChartUi();
    virtual QHash<QString,Datanode> GetChartDataMap();


    QString GroupName;
    QString ConfigFilePath;
    QSettings *cfg;

    bool isRequestNewWidget=false;
    RequestNewWidget NewWidget;

};


#endif //QT_REPEATERWIDGET_H
