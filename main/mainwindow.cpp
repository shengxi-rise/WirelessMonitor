#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qcustomplot.h"
#include "qtmaterialappbar.h"
#include "qtmaterialdrawer.h"
#include "SideBarButton/SideBarButton.h"
#include "ChannelConfiguration/channelconfiguration.h"
#include "qtmaterialscrollbar.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
//    QVBoxLayout *layout = new QVBoxLayout;
//    this->setLayout(layout);
//    QWidget *widgetTmp = new QWidget;
//    layout->addWidget(widgetTmp);
//
//    QWidget *canvas = new QWidget;
//    canvas->setStyleSheet("QWidget { background: white; }");
//    layout->addWidget(canvas);
//
//    layout->setContentsMargins(20, 20, 20, 20);
//
//    layout = new QVBoxLayout;
//    canvas->setLayout(layout);
//    canvas->setMaximumHeight(300);
//
//
    m_drawer = new QtMaterialDrawer;
    MainCfg = new CfgClass;
    m_drawer->setParent(ui->centralwidget);
    m_drawer->setClickOutsideToClose(true);
    m_drawer->setOverlayMode(true);
    m_drawer->setDrawerWidth(250);

    auto *drawerLayout = new QVBoxLayout;
    m_drawer->setDrawerLayout(drawerLayout);

    DeviceSelect[0] = new SideBarButton();
    drawerLayout->addWidget(DeviceSelect[0]);

    QString Note = MainCfg->GetMainCfg(QString("/Device/Num"));
    if (Note != nullptr) {
        for (int i = 1; i <= Note.toInt(); i++) {
            DeviceSelect[i] = new SideBarButton(i, MainCfg);
            drawerLayout->addWidget(DeviceSelect[i]);
        }
    }

    QWidget *Function1 = new ChannelConfiguration(1, MainCfg);
    ui->FunctionWindow->addWidget(Function1);
//    connect(DeviceSelect[0], SIGNAL(clicked()), this, SLOT());

    connect(ui->settingButton, SIGNAL(pressed()), m_drawer, SLOT(openDrawer()));
//    ui->FunctionTab->addTab()


}

MainWindow::~MainWindow() {
    delete ui;
}
