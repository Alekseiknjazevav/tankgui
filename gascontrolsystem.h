#ifndef GASCONTROLSYSTEM_H
#define GASCONTROLSYSTEM_H

#define QT 1        //режим работы: 1 - в QT, 0 - в консоли
#if QT
#include <QObject>
#endif

#define DEBUG 0     //вывод отладочных сообщений: 1- да, 0 - нет
#define STEP 1  //минимальный шаг актуатора, в секундах
#include <QDebug>
enum GON_SIGNALS {
    UP,             //сдвинуть актуатор ->, приоткрыть заслонку
    DOWN,           //сдвинуть актуатор <-, закрыть заслонку
    RUN,            //режим обкатки
    CALIBRATION,    //режим калибровки
    STOP_POSITION,  //RUN: утсановить в 0 положение;
                    //CALIBRATION: сигнал "заслонка в нулевом положении", угол = 0
    IDLE_POSITION,  //RUN: утсановить в положение ХХ;
                    //CALIBRATION: сигнал "заслонка положении ХХ"
    MAX_POSITION,   //RUN: утсановить в максимально открытое положение;
                    //CALIBRATION: сигнал "заслонка максимально открыта", угол = 90
    ENGINE_ERROR    //сигнал неисправности двигателя
};



class GasControlSystem
#if QT
        : public QObject
#endif

{

#if QT
Q_OBJECT
#endif

private:
    //Actuator m_actuator;
    volatile GON_SIGNALS m_signal;
    volatile int m_currentFrequency;        //частота с датчика вращения, об./мин. ???
    const int m_moveStep = STEP;            //шаг актуатора, секунды
    int m_fromIdleToZeroTime = -1;
    int m_fromIdleToMaxTime = -1;
    int m_currentPosition = -1;
    int m_stopPosition = -1;
    int m_idlePosition = -1;
    int m_maxPosition = -1;
    //int m_stepsCount = 0;
    bool m_isCalibration = false;           //режим работы:
                                            //true - калибровка; false - обкатка
    volatile bool m_error = false;
    bool m_isCalibrated = false;            //осуществлена ли калибровка
    void startCalibration();                //входим в режим калибровки
    void setStopPosition();
    void setIdlePosition(const int t = 0);
    void setMaxPosition(const int t);
    void moveUp();                          //нажимаем газ
    void moveDown();

//    void startCalibration();                //входим в режим калибровки
//    void setStopPosition();
//    void setIdlePosition(const int t);
//    void setMaxPosition(const int t);
//    void moveUp();                          //нажимаем газ
//    void moveDown();                        //отпускаем газ
//    void breakIn();                         //режим обкатки
      void calibrationWarning();              //предпреждение об отсутствии калибровки

public:
    GasControlSystem();
    volatile int m_frequency;               //целевая уставка частоты, об./мин.
    void start_simulation();
    void stop_simulation();
    void setFrequency(const int f);
//    GasControlSystem(Actuator actuator)
//        : m_actuator {actuator} {

//    };

//    void run();                             //запуск системы контроля

//    //ВХОДНЫЕ ПОТОКИ ДАННЫХ (IN)
//    void setFrequency(const int f);         //принимаем целевую уставку частоты
//    void setSignal(const GON_SIGNALS s);    //принимаем сигнал => устанавливаем режим работы
//    void recieveFrequency(const int f);     //принимаем частоту от датчика



    //ВЫХОДНЫЕ ПОТОКИ ДАННЫХ (OUT)
    double getValveAngle();                 //выдаем для GUI угол заслонки
    GON_SIGNALS getSignal();                //принимаем сигнал от GUI
    bool isOK();                            //сигнал нормального режима работы

#if DEBUG
    void info();                            //вывод данных об актуаторе
#endif

#if QT
signals:
    void engineFailed();

public slots:
    void resetCalibration();//отпускаем газ
    void breakIn();
             //принимаем целевую уставку частоты
    void setSignal(const GON_SIGNALS s, int time = 0);    //принимаем сигнал => устанавливаем режим работы
    void recieveFrequency(const int f);     //принимаем частоту от датчика
    void run();
#endif

};

#endif // GASCONTROLSYSTEM_H
