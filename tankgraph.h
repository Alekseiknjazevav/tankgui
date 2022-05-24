#ifndef TANKGRAPH_H
#define TANKGRAPH_H

#include <QWidget>

class TankGraph: public QWidget
{
    Q_OBJECT

public:
    explicit TankGraph(std::string x_axis_name, std::string y_axis_name, int upper_bound, int lower_bound, int graph_step, QWidget *parrent = nullptr);
    virtual ~TankGraph();
    void start_simulation();
    void set_colibration_status_ho();
    void set_colibration_status_maxload();
private:
    void drawGraph(std::vector<double> graph, QPen pen, QPainter& painter, std::function<double(double)> mapY);
    void update_status();
    int get_random_number();
    QTimer* m_updTimer = nullptr;
    std::vector<double> m_load_points = {};
    bool m_start_simulation = false;
    std::string m_x_axis_name;
    std::string m_y_axis_name;
    int m_upper_bound;
    int m_lower_bound;
    int m_graph_step;
protected:
    void paintEvent(QPaintEvent *event) final;
};

#endif // TANKGRAPH_H
