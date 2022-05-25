#ifndef TANKWINDOW_H
#define TANKWINDOW_H
#include "gascontrolsystem.h"
#include "machineinterface.h"
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
    MachineInterface* m_power_controller = new MachineInterface();
    TankGraph* m_turns_graph = nullptr;;
    TankGraph* m_load_graph = nullptr;;
    TankGraph* m_moment_graph = nullptr;;
    QPushButton* m_start_calibration_button = nullptr;
    QPushButton* m_reset_calibration_button = nullptr;
    QLabel* m_text_calibration_status = nullptr;
    QPushButton* m_forward_button = nullptr;
    QPushButton* m_back_button = nullptr;
    QPushButton* m_start_pos = nullptr;
    QPushButton* m_ho_pos = nullptr;
    QPushButton* m_max_pow_pos = nullptr;
    QLineEdit* m_edit_given_load = nullptr;
    QLineEdit* m_edit_time_to_load = nullptr;
    QLineEdit* m_edit_given_speed = nullptr;
    QLineEdit* m_edit_test_time = nullptr;
    QPushButton* m_start_test_button = nullptr;
    QPushButton* m_stop_test_button = nullptr;
    QLineEdit* m_edit_real_test_time = nullptr;
    CalibrationProgramState m_calibration_status = NOT_CALIBRATED;
    QTimer* m_test_timer = nullptr;
    int m_current_test_time = 0;
    int time_of_test;
    int m_calibration_steps = 0;
    int m_frequency;
    int m_upload;
    int m_moment;

private slots:
    void change_current_time();
    void changed_upload(int upload);
    void changed_frequency(int actual_Nu);
    void changed_moment(int actual_M);
    void test_run();

private:
    void state_changed(CalibrationProgramState NewState);
    void stop_test();


};
#endif // TANKWINDOW_H
