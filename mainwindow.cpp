#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    customPlot = new QCustomPlot(this);
    customPlot->resize(600, 600);

    // add two new graphs and set their look:
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
// generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(251), y0(251), y1(251);
    for (int i=0; i<251; ++i)
    {
        x[i] = i;
        y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
        y1[i] = qExp(-i/150.0);              // exponential envelope
    }
// configure right and top axis to show ticks but no labels:
// (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
// make left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
// pass data points to graphs:
    customPlot->graph(0)->setData(x, y0);
    customPlot->graph(1)->setData(x, y1);
// let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    customPlot->graph(0)->rescaleAxes();
// same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    customPlot->graph(1)->rescaleAxes(true);
// Note: we could have also just called customPlot->rescaleAxes(); instead
// Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    connect(customPlot,SIGNAL(mouseMove(QMouseEvent *)),this,SLOT(myMoveEvent(QMouseEvent *)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myMoveEvent(QMouseEvent *event)
{
    //获取鼠标坐标，相对父窗体坐标
    int x_pos = event->pos().x();
    int y_pos = event->pos().y();
    qDebug()<<"event->pos()"<<event->pos();

    //鼠标坐标转化为CustomPlot内部坐标
    float x_val = customPlot->xAxis->pixelToCoord(x_pos);
    float y_val = customPlot->yAxis->pixelToCoord(y_pos);
    float line_y_val=0;
    //获得x轴坐标位置对应的曲线上y的值
    for (int i = 0; i < customPlot->graphCount(); ++i)
    {
        QCPGraph * graph = customPlot->graph(i);
        if (graph ->selected()) {
            line_y_val= customPlot->graph(i)->data()->at(x_val)->value;
        }
    }

    //曲线的上点坐标位置，用来显示QToolTip提示框
    float out_x = customPlot->xAxis->coordToPixel(x_val);
    float out_y = customPlot->yAxis->coordToPixel(line_y_val);

    QString str,strToolTip;
    str = QString::number(x_val,10,3);
    strToolTip += "x: ";
    strToolTip += str;
    strToolTip += "\n";

    str = QString::number(line_y_val,10,3);
    strToolTip += "y: ";
    strToolTip += str;
    strToolTip += "\n";

    QToolTip::showText(mapToGlobal(QPoint(out_x,out_y)),strToolTip,customPlot);

}
