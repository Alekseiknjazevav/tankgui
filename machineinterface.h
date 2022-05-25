#ifndef MACHINEINTERFACE_H
#define MACHINEINTERFACE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
//class InternalCombustionEngine;
//class ElectricMotor;
//class FrequencyConverter;

class MachineInterface : public QObject
{
    Q_OBJECT
public:
    explicit MachineInterface ( float timeInterval = 0.1, QObject * parent = nullptr );

    void start_engine();             // завести ДВС
    void stop_engine();              // остановить ДВС (при этом отключается электро-двигатель?)
    void set_angle( int angle );     // задать угол положения дросселя (в градусах, от 0 до 90)

    void set_P_target( int PTarget, float PChangeTime = 0 ); //
                         //задать уставку по нагрузке (в кВТ) и время ее достижения (в секундах)
    //void manual_control();           // включить ручное управление уровнем нагрузки (?)
    //void automatic_control();        // включить ручное управление уровнем нагрузки (?)
    void start_simulation();
    void stop_simulation();
    const int get_P_actual() const;  // получить текущее значение нагрузки (в кВТ)
    const int get_Nu_actual() const; // получить текущее значение частоты оборотов (в Об / мин)
    const int get_M_actual() const;  // получить текущее значение момента (в кВТ/мин)


signals:
    void changed_actual_P(int upload);
    void changed_Nu_actual(int actual_Nu);
    void changed_M_actual(int actual_M);
private:
    QTimer* m_update_timer = nullptr;
private slots:
    void update_all_info();
    //void engine_stalled(); // СИГНАЛ. двигатель заглох (наверное не нужен?)

//private:
//	InternalCombustionEngine ICE;   // двигатель внутреннего сгорания
//	ElectricMotor EM;               // электро-двигатель
//	FrequencyConverter FC;          // преобразователь частот
                    // общий таймер ДВС и ЭД
};
#endif // MACHINEINTERFACE_H
