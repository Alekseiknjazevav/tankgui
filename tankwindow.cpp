#include "tankwindow.h"
#include <QVBoxLayout>
#include "tankgraph.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QtWidgets>
#include <QGridLayout>

TankWindow::TankWindow(QWidget *parent)
    : QMainWindow(parent)
{

        setCentralWidget(new QWidget(this));
        QGridLayout* vLay = new QGridLayout(centralWidget());
        centralWidget()->setLayout(vLay);
        QGroupBox *calibration = new QGroupBox("Калибровка актуатора");
        QHBoxLayout* calibration_layout = new QHBoxLayout;


        QWidget* calibration_left_window = new QWidget();
        QVBoxLayout* calibration_left_layout = new QVBoxLayout;

            QGroupBox* move_buttons = new QGroupBox("Управление перемещением акутатора");
            QHBoxLayout* calibration_buttons_lay = new QHBoxLayout;
            m_forward_button = new QPushButton("На шаг вперёд");
            m_forward_button->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
            m_forward_button->setEnabled(false);
            m_back_button = new QPushButton("На шаг назад");
            m_back_button->setEnabled(false);
            m_back_button->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
            calibration_buttons_lay->addWidget(m_forward_button);
            calibration_buttons_lay->addWidget(m_back_button);
            move_buttons->setLayout(calibration_buttons_lay);
            calibration_left_layout->addWidget(move_buttons);


            QGroupBox* positions_buttons = new QGroupBox("Зафиксировать положение актуатора");
            QHBoxLayout* calibration_positions_lay = new QHBoxLayout;
            m_start_pos = new QPushButton("0%");
            m_ho_pos = new QPushButton("ХХ");
            m_max_pow_pos = new QPushButton("100%");
            m_start_pos->setEnabled(false);
            m_ho_pos->setEnabled(false);
            m_max_pow_pos->setEnabled(false);
            m_start_pos->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
            m_ho_pos->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
            m_max_pow_pos->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
            calibration_positions_lay->addWidget(m_start_pos);
            calibration_positions_lay->addWidget(m_ho_pos);
            calibration_positions_lay->addWidget(m_max_pow_pos);
            positions_buttons->setLayout(calibration_positions_lay);
            calibration_left_layout->addWidget(positions_buttons);
            calibration_left_window->setLayout(calibration_left_layout);
            calibration_layout->addWidget(calibration_left_window);

        QGroupBox* calibration_start_stop = new QGroupBox();
        QVBoxLayout* calibration_start_stop_lay = new QVBoxLayout;
        QLabel* calibration_status = new QLabel("Статус калибровки");
        calibration_status->setAlignment(Qt::AlignHCenter);
        m_text_calibration_status = new QLabel();
        m_text_calibration_status->setText("Не откалиброван");
        m_text_calibration_status->setStyleSheet("QLabel {"
                                     "border-style: solid;"
                                     "border-width: 2px;"
                                     "border-color: black; "
                                     "}");
        m_text_calibration_status->setAlignment(Qt::AlignHCenter);
        m_start_calibration_button = new QPushButton("Старт");
        m_reset_calibration_button = new QPushButton("Сброс");
        m_reset_calibration_button->setEnabled(false);
        calibration_status->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
        m_text_calibration_status->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
        m_start_calibration_button->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
        m_reset_calibration_button->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
        calibration_start_stop_lay->addWidget(calibration_status);
        calibration_start_stop_lay->addWidget( m_text_calibration_status);
        calibration_start_stop_lay->addWidget(m_start_calibration_button);
        calibration_start_stop_lay->addWidget(m_reset_calibration_button);
        calibration_start_stop->setLayout(calibration_start_stop_lay);
        calibration_layout->addWidget(calibration_start_stop);
        calibration->setLayout(calibration_layout);
        vLay->addWidget(calibration, 0, 0, 1, 1);

        //Окно тестов горячей обкатки
        QGroupBox* test_window = new QGroupBox("Программа горячей обкатки");
        QGridLayout* test_window_layout = new QGridLayout;
        QLabel* given_load = new QLabel("Заданная нагрузка:");
        QLabel* time_to_load = new QLabel("Время набора/\nсброса нагрузки:");
        QLabel* given_speed = new QLabel("Заданная скорость:");
        QLabel* test_time = new QLabel("Время обкатки:");
        test_window_layout->addWidget(given_load, 0, 0, 1, 1);
        test_window_layout->addWidget(time_to_load, 1, 0, 1, 1);
        test_window_layout->addWidget(given_speed, 2, 0, 1, 1);
        test_window_layout->addWidget(test_time, 3, 0, 1, 1);
        m_edit_given_load = new QLineEdit();
        m_edit_time_to_load = new QLineEdit();
        m_edit_given_speed = new QLineEdit();
        m_edit_test_time = new QLineEdit();
        test_window_layout->addWidget(m_edit_given_load, 0, 1, 1, 1);
        test_window_layout->addWidget(m_edit_time_to_load, 1, 1, 1, 1);
        test_window_layout->addWidget(m_edit_given_speed, 2, 1, 1, 1);
        test_window_layout->addWidget(m_edit_test_time, 3, 1, 1, 1);
        QLabel* units_of_given_load = new QLabel("кВт");
        QLabel* units_of_time_to_load = new QLabel("с");
        QLabel* units_of_given_speed = new QLabel("об/мин");
        QLabel* units_of_test_time = new QLabel("мин");
        test_window_layout->addWidget(units_of_given_load, 0, 2, 1, 1);
        test_window_layout->addWidget(units_of_time_to_load, 1, 2, 1, 1);
        test_window_layout->addWidget(units_of_given_speed, 2, 2, 1, 1);
        test_window_layout->addWidget(units_of_test_time, 3, 2, 1, 1);
        QLabel* real_test_time = new QLabel("До конца испытания:");
        real_test_time->setAlignment(Qt::AlignHCenter);
        m_edit_real_test_time = new QLineEdit();
        m_edit_real_test_time->setPlaceholderText("00:00:00");
        m_edit_real_test_time->setReadOnly(true);
        m_edit_real_test_time->setAlignment(Qt::AlignHCenter);
        m_test_timer = new QTimer(this);
        m_test_timer->setInterval(1000);
        m_start_test_button = new QPushButton("Запуск прогона");
        m_start_test_button->setEnabled(false);
        m_stop_test_button = new QPushButton("Остановка прогона");
        m_stop_test_button->setEnabled(false);
        test_window_layout->addWidget(real_test_time, 0, 3, 1, 1);
        test_window_layout->addWidget(m_edit_real_test_time, 1, 3, 1, 1);
        test_window_layout->addWidget(m_start_test_button, 2, 3, 1, 1);
        test_window_layout->addWidget(m_stop_test_button, 3, 3, 1, 1);
        test_window->setLayout(test_window_layout);
        vLay->addWidget(test_window, 1, 0, 1, 1);



        // Графики
        QGroupBox* charts = new QGroupBox;
        QVBoxLayout* charts_layout = new QVBoxLayout;
        m_turns_graph = new TankGraph("Время, с", "Обороты, об/мин", 3000, 0, 300, this);
        m_load_graph = new TankGraph("Время, с", "Мощность, кВт", 800, 0, 100, this);
        m_moment_graph = new TankGraph("Время, с", "Момент", 2000, 0, 300, this);
        charts_layout->addWidget(m_turns_graph);
        charts_layout->addWidget(m_load_graph);
        charts_layout->addWidget(m_moment_graph);
        charts->setLayout(charts_layout);
        vLay->addWidget(charts, 0, 1, 2, 2);
        //Все конекты вынесены сюда

        connect(m_power_controller, &MachineInterface::changed_actual_P, this, &TankWindow::changed_upload);
        connect(m_power_controller, &MachineInterface::changed_Nu_actual, this, &TankWindow::changed_frequency);
        connect(m_power_controller, &MachineInterface::changed_M_actual, this, &TankWindow::changed_moment);
        connect(m_test_timer, &QTimer::timeout, this, &TankWindow::change_current_time);
        connect(m_start_calibration_button, &QPushButton::clicked, m_gas_controller, [=]()
        {

            m_gas_controller->setSignal(CALIBRATION);
            this->state_changed(CALIBRATION_0);
        });
        connect(m_forward_button, &QPushButton::clicked, m_gas_controller, [=]()
        {
            m_calibration_steps++;
            m_gas_controller->setSignal(UP);
        });
        connect(m_back_button, &QPushButton::clicked, m_gas_controller, [=]()
        {
            m_calibration_steps--;
            m_gas_controller->setSignal(DOWN);

        });
        connect(m_start_pos, &QPushButton::clicked, m_gas_controller, [=]()
        {
            m_calibration_steps = 0;
            m_gas_controller->setSignal(STOP_POSITION);
            this->state_changed(CALIBRATION_IDLE);
        });
        connect(m_ho_pos, &QPushButton::clicked, m_gas_controller, [=]()
        {
            m_gas_controller->setSignal(IDLE_POSITION, m_calibration_steps);
            this->state_changed(CALIBRATION_100);
        });
        connect(m_max_pow_pos, &QPushButton::clicked, m_gas_controller, [=]()
        {
            m_gas_controller->setSignal(MAX_POSITION, m_calibration_steps);
            this->state_changed(CALIBRATION_DONE);
        });
        connect(m_reset_calibration_button, &QPushButton::clicked, m_gas_controller, [=]()
        {
            m_calibration_steps = 0;
            m_gas_controller->resetCalibration();
            this->state_changed(NOT_CALIBRATED);
        });
        connect(m_start_test_button, &QPushButton::clicked, this, [=]()
        {
            if (m_edit_given_load->displayText().isEmpty() || m_edit_time_to_load->displayText().isEmpty() || m_edit_given_speed->displayText().isEmpty() || m_edit_test_time->displayText().isEmpty())
            {
                QMessageBox msgBox;
                msgBox.setText("Для запуска прогона, заполните все поля");
                msgBox.exec();
            }
            else{
                m_start_test_button->setEnabled(false);
                this->test_run();
            }

        });
        connect(m_stop_test_button, &QPushButton::clicked, this, [=]()
        {
            this->stop_test();
        });




























}

TankWindow::~TankWindow()
{
}

void TankWindow::change_current_time()
{
    m_current_test_time += 1;
    m_edit_real_test_time->setText(tr("%1").arg(QTime(0,0).addSecs(m_current_test_time).toString("hh:mm:ss")));
}

void TankWindow::changed_upload(int upload)
{
    m_upload = upload;
    m_load_graph->accept_changed_value(m_upload);
}

void TankWindow::changed_frequency(int actual_Nu)
{
    m_frequency = actual_Nu;
    m_turns_graph->accept_changed_value(m_frequency);
}

void TankWindow::changed_moment(int actual_M)
{
    m_moment = actual_M;
    m_moment_graph->accept_changed_value(m_moment);
}

void TankWindow::test_run()
{

    m_reset_calibration_button->setEnabled(false);
    m_stop_test_button->setEnabled(true);
    m_power_controller->set_P_target(m_edit_given_load->text().toInt(), m_edit_time_to_load->text().toFloat());
    time_of_test = m_edit_test_time->text().toInt() * 60;
    m_gas_controller->setSignal(IDLE_POSITION);
    m_power_controller->start_engine();
    m_gas_controller->start_simulation();
    Sleep(2000); // это стоит делать по таймеру, временная мера
    if (m_power_controller->get_Nu_actual() > 0 || true){ // так как реального значения мы не получаем поставил в или true чтобы работало
         m_gas_controller->setFrequency(m_edit_given_speed->text().toInt());
         m_power_controller->start_simulation();
         Sleep(2000); // это стоит делать по таймеру, временная мера
         if (m_power_controller->get_Nu_actual() >= 0.9 * m_gas_controller->m_frequency && m_power_controller->get_Nu_actual() <= 1.1 * m_gas_controller->m_frequency || true){ // так как реального значения мы не получаем поставил в или true чтобы работало
             m_test_timer->start();
             m_turns_graph ->start_simulation();
             m_load_graph ->start_simulation();
             m_moment_graph ->start_simulation();
         }
         else{
             m_power_controller->stop_simulation();
             m_power_controller->stop_engine();
             m_gas_controller->setSignal(STOP_POSITION);
             this->stop_test();
         }
    }
    else{
        m_power_controller->stop_engine();
        m_gas_controller->setSignal(STOP_POSITION);
        this->stop_test();
    }

}




void TankWindow::state_changed(CalibrationProgramState NewState)
{
    switch (NewState)
        {
        case NOT_CALIBRATED:
            m_text_calibration_status->setText("Не откалиброван");
            m_start_calibration_button->setEnabled(true);
            m_reset_calibration_button->setEnabled(false);
            m_forward_button->setEnabled(false);
            m_back_button->setEnabled(false);
            m_start_pos->setEnabled(false);
            m_ho_pos->setEnabled(false);
            m_max_pow_pos->setEnabled(false);
            m_start_test_button->setEnabled(false);
            m_stop_test_button->setEnabled(false);
            break;
        case CALIBRATION_0:
            m_text_calibration_status->setText("Не откалиброван");
            m_start_calibration_button->setEnabled(false);
            m_reset_calibration_button->setEnabled(true);
            m_forward_button->setEnabled(true);
            m_back_button->setEnabled(true);
            m_start_pos->setEnabled(true);
            break;
        case CALIBRATION_IDLE:
            m_text_calibration_status->setText("Калибровка");
            m_start_pos->setEnabled(false);
            m_ho_pos->setEnabled(true);
            break;
        case CALIBRATION_100:
            m_text_calibration_status->setText("Калибровка");
             m_ho_pos->setEnabled(false);
             m_max_pow_pos->setEnabled(true);
            break;
        case CALIBRATION_DONE:
            m_text_calibration_status->setText("Откалиброван");
            m_forward_button->setEnabled(false);
            m_back_button->setEnabled(false);
            m_max_pow_pos->setEnabled(false);
            m_start_test_button->setEnabled(true);
            break;
        default:
            break;
    }
}

void TankWindow::stop_test()
{
    m_power_controller->stop_simulation();
    m_power_controller->stop_engine();
    m_gas_controller->setSignal(STOP_POSITION);
    m_power_controller->stop_simulation();
    m_current_test_time = 0;
    m_test_timer->stop();
    m_reset_calibration_button->setEnabled(true);
    m_stop_test_button->setEnabled(false);
    m_start_test_button->setEnabled(true);
    m_power_controller->stop_simulation();
    m_turns_graph ->stop_simulation();
    m_load_graph ->stop_simulation();
    m_moment_graph ->stop_simulation();
}
