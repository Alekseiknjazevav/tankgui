#include "tankgraph.h"
#include <QTimer>
#include <QPainter>
#include <QTime>
#include <iostream>
#include <string>
#include <QDebug>

constexpr int topMargin = 60;///размер верхнего поля
constexpr int botoomMargin = 30;///размер нижнего поля


TankGraph::TankGraph(std::string x_axis_name, std::string y_axis_name, int upper_bound, int lower_bound, int graph_step, QWidget *parent) : QWidget(parent),
    m_x_axis_name(x_axis_name), m_y_axis_name(y_axis_name), m_upper_bound(upper_bound), m_lower_bound(lower_bound), m_graph_step(graph_step)
{
    m_updTimer = new QTimer(this);
    m_updTimer->setInterval(1000);
    connect(m_updTimer, &QTimer::timeout, this, &TankGraph::update_status);
    setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    setMaximumSize(640, 300);
    setMinimumSize(640, 300);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    ///The sizeHint() is minimal, and sufficient. The widget can make use of extra space,
    ///so it should get as much space as possible (e.g. the horizontal direction of a horizontal slider).
}

TankGraph::~TankGraph()
{

}


void TankGraph::accept_changed_value(int number)
{
    if (!m_start_simulation)
            return;
        m_load_points.push_back(number);
        update();
}

void TankGraph::stop_simulation()
{
     m_load_points = {};
     m_start_simulation = false;
     m_updTimer->stop();
}

void TankGraph::start_simulation()
{
    m_start_simulation = true;
    m_updTimer->start();



}



void TankGraph::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    const auto bottomEnd = height()-botoomMargin;
    const double kvert = (m_upper_bound - m_lower_bound) / double((bottomEnd-topMargin));
    auto map_y = [bottomEnd, tempMin = m_lower_bound, kvert](double iy){return bottomEnd-(iy-tempMin)/kvert;};
    ///Нарисуем горизонтальные линии шкалы
    for(auto i = 0; i<=m_upper_bound; i+=m_graph_step)
    {
        if(i%m_graph_step)
            painter.setPen(QPen(QColor(128,128,128)));
        else
            painter.setPen(QPen(QColor(0,0,0)));
        auto y = map_y(i);
        painter.drawLine(0, y, width(), y);
        painter.drawText(5,y-1,QString::number(i));
    }
    auto pen = QPen(QColor(255,0,0));
    drawGraph(m_load_points, pen, painter, map_y);
    painter.drawText(280, height() - 1, tr(m_x_axis_name.data()));
    painter.drawText(10, 20, tr(m_y_axis_name.data()));
}
void TankGraph::drawGraph(std::vector<double> graph, QPen pen, QPainter& painter, std::function<double(double)> mapY)
{
    if(graph.size()>1)
    {

        pen.setWidth(3);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        int shift = std::max( int(graph.size()-width()) ,0);
        for(int i = 0; i<width()-1; ++i)
        {
            if(i+shift+1>=(int)graph.size())
                break;
            painter.drawLine(i, mapY(graph[i+shift]), i+1, mapY(graph[i+shift+1]));
        }
    }
}

void TankGraph::update_status()
{
    if (!m_start_simulation)
            return;
    update();
}
