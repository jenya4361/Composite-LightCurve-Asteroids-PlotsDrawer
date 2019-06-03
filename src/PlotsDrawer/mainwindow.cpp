#include "MainIncludes.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "App.h"
#include "ManagersController.h"

#include "managers/PlotsManager.h"

#include "ui/LogsImpl.h"
#include "ui/AxisLimitsImpl.h"
#include "ui/AddPlotImpl.h"
#include "ui/CustomPlotImpl.h"
#include "ui/PlotsImpl.h"
#include "ui/CurrentPlotImpl.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initUI();
    initManagers();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_logs;
    delete m_axisLimits;
    delete m_addPlot;
    delete m_customPlot;
    delete m_plots;
    delete m_currentPlot;
}

void MainWindow::initUI()
{
    // Plot init
    ui->widgetPlot->xAxis->setLabel("Ph");
    ui->widgetPlot->yAxis->setLabel("R(1, al)");

    // Logs
    m_logs = new LogsImpl();
    m_logs->assignUI( this );

    // Axis Limits
    m_axisLimits = new AxisLimitsImpl();
    m_axisLimits->assignUI( this );
    m_axisLimits->setCallbackRange(
       [this]( double xMin, double yMin, double xMax, double yMax )
    {
        ui->widgetPlot->xAxis->setRange( xMin, xMax );
        ui->widgetPlot->yAxis->setRange( yMin, yMax );
        ui->widgetPlot->replot();

        PLog( "Axis Limits updated." );
    });

    // Add Plot
    m_addPlot = new AddPlotImpl();
    m_addPlot->assignUI( this );

    // Custom Plot
    m_customPlot = new CustomPlotImpl();
    m_customPlot->assignUI( this );

    // Plots
    m_plots = new PlotsImpl();
    m_plots->assignUI( this );

    // Current Plot
    m_currentPlot = new CurrentPlotImpl();
    m_currentPlot->assignUI( this );
}

void MainWindow::initManagers()
{
    // Logs
    const LogManagerPtr& logMng = App::getMC()->getLogManager();

    logMng->setLogCallback(
       [this]( const std::string& str )
    {
        if( m_logs )
            m_logs->addLog( QString( str.c_str() ) );
    } );

    // Plots Manager
    const PlotsManagerPtr& plotsMng = App::getMC()->getPlotsManager();

    plotsMng->setCallbackAddPlot(
       [this]( const Plot& plot )
    {
        m_customPlot->addPlot( plot );
        m_addPlot->clearFields();
        m_plots->addPlotButton( plot );
        PLog( "New plot added!" );
    });

    plotsMng->setCallbackSetCurrentPlot(
       [this]( const Plot& plot )
    {
        m_currentPlot->setCurrentPlot( plot );
    });

    plotsMng->setCallbackUpdatePlot(
       [this]( const Plot& plot )
    {
        m_customPlot->updatePlot( plot );
        m_currentPlot->showOffsetX( plot.offsetX );
        m_currentPlot->showOffsetY( plot.offsetY );
        m_currentPlot->showOffsetP( plot.offsetPeriod );

        PLog( "Plot updated!" );
    });

    plotsMng->setCallbackFlipX(
       [this]()
    {
        m_customPlot->flipXAxis();
    });

    plotsMng->setCallbackFlipY(
       [this]()
    {
        m_customPlot->flipYAxis();
    });

    plotsMng->setCallbackDeletePlot(
       [this]( const Plot& plot )
    {
        m_plots->deletePlot( plot );
        m_customPlot->deletePlot( plot );
    });

    plotsMng->setCallbackSavePlotInFile(
       [this]( const Plot& plot )
    {
        const QVector< Axis >& resultData = plot.resultData;
        std::ofstream fout( "modified_" + plot.filename.toStdString() );

        fout << "Ph\t" << "R(1,al)\t" << "RError\n";
        for( const Axis& data : resultData )
        {
            fout << data.x << "\t" << data.y << "\t" << data.yError << "\n";
        }

        fout.close();

        PLog( "Successfully saved in file!" );
    });
}















