#include "machineinterface.h"

//machineinterface::machineinterface()
//{

//}

MachineInterface::MachineInterface(float timeInterval, QObject *parent)
{
    m_update_timer = new QTimer(this);
    m_update_timer->setInterval(100);
    connect(m_update_timer, &QTimer::timeout, this, &MachineInterface::update_all_info);
}

void MachineInterface::start_engine()
{
    qDebug() << "Завели двс";
    return;
}

void MachineInterface::stop_engine()
{
    qDebug() << "Астанаавить двигатель";
}

void MachineInterface::set_P_target(int PTarget, float PChangeTime)
{
    qDebug() << "установили нагрузку и время ее достижения";
}

void MachineInterface::start_simulation()
{
    m_update_timer->start();
}

void MachineInterface::stop_simulation()
{
    m_update_timer->stop();
}

const int MachineInterface::get_P_actual() const
{
    return qrand() % 800;
}

const int MachineInterface::get_Nu_actual() const
{
    return qrand() % 3000;
}

const int MachineInterface::get_M_actual() const
{
    return qrand() % 1500;
}

void MachineInterface::update_all_info()
{
    emit changed_actual_P(this->get_P_actual());
    emit changed_Nu_actual(this->get_Nu_actual());
    emit changed_M_actual(this->get_M_actual());
}
