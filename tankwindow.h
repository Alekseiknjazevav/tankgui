#ifndef TANKWINDOW_H
#define TANKWINDOW_H
#include "gascontrolsystem.h"
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

enum CalibrationProgramState
{
    NOT_CALIBRATED   = 0,
    CALIBRATION_0    = 1,
    CALIBRATION_IDLE = 2,
    CALIBRATION_100  = 3,
    CALIBRATION_DONE = 4
};

class TankGraph;
class TankWindow : public QMainWindow
{
    Q_OBJECT

public:
    TankWindow(QWidget *parent = nullptr);
    ~TankWindow();

private:
    GasControlSystem* m_gas_controller = new GasControlSystem();
    QPushButton* m_start_calibration_button = nullptr;
    QPushButton* m_reset_calibration_button = nullptr;
    QLabel* m_text_calibration_status = nullptr;
    QPushButton* m_forward_button = nullptr;
    QPushButton* m_back_button = nullptr;
    QPushButton* m_start_pos = nullptr;
    QPushButton* m_ho_pos = nullptr;
    QPushButton* m_max_pow_pos = nullptr;
    CalibrationProgramState m_calibration_status = NOT_CALIBRATED;
    int m_calibration_steps = 0;


private:
    void state_changed(CalibrationProgramState NewState);


};
#endif // TANKWINDOW_H
