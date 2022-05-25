#include "gascontrolsystem.h"
#include <windows.h>
#include <iostream>

void GasControlSystem::setSignal(const GON_SIGNALS signal, int time)
{
    m_signal = signal;
    run();
}

void GasControlSystem::recieveFrequency(const int f)
{
    m_currentFrequency = f;
}

void GasControlSystem::run()
{
        switch (m_signal) {
        case UP :
            moveUp();
            break;
        case DOWN :
            moveDown();
            break;
        case RUN :
            breakIn();
            break;
        case STOP_POSITION :
            setStopPosition();
            break;
        case IDLE_POSITION :
            setIdlePosition(m_currentPosition);
            break;
        case MAX_POSITION :
            setMaxPosition(m_currentPosition);
            break;
        case CALIBRATION :
            startCalibration();
            break;
        case ENGINE_ERROR :
            m_error = true;
            setStopPosition();  //а надо ли?? может надо ждать сигнал от GUI?
        }
}

double GasControlSystem::getValveAngle()
{
    if (m_isCalibrated) {
        return 90.0 * m_currentPosition / (m_maxPosition - m_stopPosition);
    } else {
        calibrationWarning();
        return -1 * 90.0 * m_currentPosition / (m_maxPosition - m_stopPosition);
    }
}

GON_SIGNALS GasControlSystem::getSignal()           //не очень нужная функция
{
    return m_signal;
}

void GasControlSystem::setFrequency(const int f)    //получение целевой частоты
{
    m_frequency = f;
#if DEBUG
        std::cout << "f_goal  = " << m_frequency << std::endl;
#endif
}

void GasControlSystem::startCalibration()
{
    m_isCalibration = true;
}

void GasControlSystem::resetCalibration()
{
    int m_fromIdleToZeroTime = -1;
    int m_fromIdleToMaxTime = -1;
    int m_currentPosition = -1;
    int m_stopPosition = -1;
    int m_idlePosition = -1;
    int m_maxPosition = -1;
    bool m_isCalibration = false;           //режим работы //true - калибровка; false - обкатка
    volatile bool m_error = false;
    bool m_isCalibrated = false;
}

void GasControlSystem::setStopPosition()
{
    if (m_isCalibration) {
        m_stopPosition = 0;
        m_currentPosition = 0;

#if DEBUG
        std::cout << "Start position = " << m_stopPosition << std::endl;
#endif
    } else {
        if (m_isCalibrated) {
            qDebug() << m_currentPosition << "тут мы";
            while(m_currentPosition > 0) {

                moveDown();
            }
#if DEBUG
            std::cout << "Zero position is set" << std::endl;
#endif
        } else {
            calibrationWarning();
        }
    }
}

void GasControlSystem::setIdlePosition(const int t)
{
    if (m_isCalibration) {
        m_idlePosition = t;
        qDebug() << m_idlePosition << "Время до холостого хода";
        m_fromIdleToZeroTime = m_idlePosition - m_stopPosition;
#if DEBUG
        std::cout << "Idle position = " << m_idlePosition << std::endl;
        std::cout << "Cur = " << m_currentPosition << std::endl;
#endif

    } else {
        if (m_isCalibrated) {
            if (m_currentPosition > m_idlePosition) {
                while(m_currentPosition > m_idlePosition) {
                    moveDown();

                }
            } else if (m_currentPosition < m_idlePosition) {
                while(m_currentPosition < m_idlePosition) {
                    moveUp();
                }
            } else {
#if DEBUG
                std::cout << "Idle position is set" << std::endl;
#endif
            }
        } else {
            calibrationWarning();
        }
    }
}

void GasControlSystem::setMaxPosition(const int t)
{
    if (m_isCalibration) {
        m_maxPosition = t;
        qDebug() << m_maxPosition << "Время до максимальной мощности";
        m_fromIdleToZeroTime = m_maxPosition - m_idlePosition;
        m_isCalibrated = true;
        m_isCalibration = false;
#if DEBUG
        std::cout << "Max position = " << m_maxPosition << std::endl;
        std::cout << "Cur = " << m_currentPosition << std::endl;
#endif
    } else {
        if (m_isCalibrated) {
            while (m_currentPosition < m_maxPosition) {
                moveUp();
            }
#if DEBUG
            std::cout << "Max position is set" << std::endl;
#endif
        } else {
            calibrationWarning();
        }
    }
}

void GasControlSystem::moveUp()
{
    Sleep(STEP * 1000);
    qDebug() << "Еду вперед";
    //m_stepsCount++;
    m_currentPosition++;
#if DEBUG
    std::cout << "Actuator moved forward: 1 step (" << m_currentPosition
              << ")" << std::endl;
#endif
//    m_actuator.up();
//    Sleep(STEP * 1000);
//    stepsCount++;
//    m_actuator.stop();
}

void GasControlSystem::moveDown()
{
    Sleep(STEP * 1000);
    qDebug() << "Еду назад";
    //m_stepsCount--;
    m_currentPosition--;
#if DEBUG
    std::cout << "Actuator moved backward: 1 step (" << m_currentPosition
              << ")" << std::endl;
#endif
//    m_actuator.down();
//    Sleep(STEP * 1000);
//    stepsCount--;
//    m_actuator.stop();
}

bool GasControlSystem::isOK()
{
    return !m_error;
}

//void GasControlSystem::info()
//{
//    std::cout << "-----------" << std::endl;
//    std::cout << "Cur = "<< m_currentPosition << std::endl;
//    std::cout << "Stop = " << m_stopPosition << std::endl;
//    std::cout << "Idle = " << m_idlePosition << std::endl;
//    std::cout << "Max = " << m_maxPosition << std::endl;
//    std::cout << "Angle = " << getValveAngle() << std::endl;
//    std::cout << "-----------" << std::endl;
//}

void GasControlSystem::breakIn()        //режим обкатки
{
    if (m_frequency > m_currentFrequency) {
        if (getValveAngle() < 90) {
            moveUp();
        }
        else {
            m_signal = GON_SIGNALS::ENGINE_ERROR;
            m_error = true;
            std::cout << "ENGINE ERROR!!!" << std::endl;
#if QT
            emit engineFailed();
#endif
        }
    } else if (m_frequency < m_currentFrequency) {
        if (getValveAngle() > 0 ) {
            moveDown();
        }
        else {
            std::cout << "Valve is closed!" << std::endl;
        }
    } else {
        std::cout << "Goal frequency is achieved" << std::endl;
    }
}

void GasControlSystem::calibrationWarning()
{
    std::cout << "Actuator wasn't calibrated!!!\nMovement is DANGEROUS!!!"
        << std::endl;
}

GasControlSystem::GasControlSystem()
{
}

void GasControlSystem::start_simulation()
{
    qDebug() << "Начало автономной работы";
}

void GasControlSystem::stop_simulation()
{
    qDebug() << "Конец автономной работы";
}


