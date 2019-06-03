#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class LogsImpl;
class AxisLimitsImpl;
class AddPlotImpl;
class CustomPlotImpl;
class PlotsImpl;
class CurrentPlotImpl;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    void initUI();
    void initManagers();

private:
    Ui::MainWindow* ui;

    // UI
    LogsImpl* m_logs;
    AxisLimitsImpl* m_axisLimits;
    AddPlotImpl* m_addPlot;
    CustomPlotImpl* m_customPlot;
    PlotsImpl* m_plots;
    CurrentPlotImpl* m_currentPlot;
};

#endif // MAINWINDOW_H
