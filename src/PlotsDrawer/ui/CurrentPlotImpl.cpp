#include "CurrentPlotImpl.h"
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "MainIncludes.h"

CurrentPlotImpl::CurrentPlotImpl()
{
}

CurrentPlotImpl::~CurrentPlotImpl()
{

}

void CurrentPlotImpl::assignUI( const QMainWindow* ui )
{
    m_plotName = FindUIElementInWindow<QLabel*>( ui, "plotName" );
    m_shapeName = FindUIElementInWindow<QLabel*>( ui, "shapeName" );
    m_offsetXLabel = FindUIElementInWindow<QLabel*>( ui, "offsetXLabel" );
    m_offsetYLabel = FindUIElementInWindow<QLabel*>( ui, "offsetYLabel" );
    m_offsetPLabel = FindUIElementInWindow<QLabel*>( ui, "offsetPLabel" );

    m_deletePlotBtn = FindUIElementInWindow<QPushButton*>( ui, "deletePlotBtn" );
    m_saveInFileBtn = FindUIElementInWindow<QPushButton*>( ui, "saveInFileBtn" );

    m_movePlotLeft = FindUIElementInWindow<QPushButton*>( ui, "movePlotLeft" );
    m_movePlotRight = FindUIElementInWindow<QPushButton*>( ui, "movePlotRight" );
    m_movePlotUp = FindUIElementInWindow<QPushButton*>( ui, "movePlotUp" );
    m_movePlotDown = FindUIElementInWindow<QPushButton*>( ui, "movePlotDown" );
    m_movePeriodLeft = FindUIElementInWindow<QPushButton*>( ui, "movePeriodLeft" );
    m_movePeriodRight = FindUIElementInWindow<QPushButton*>( ui, "movePeriodRight" );
    m_editBoxPeriodStep = FindUIElementInWindow<QLineEdit*>( ui, "editBoxPeriodStep" );
    m_editBoxStepX = FindUIElementInWindow<QLineEdit*>( ui, "editBoxStepX" );
    m_editBoxStepY = FindUIElementInWindow<QLineEdit*>( ui, "editBoxStepY" );

    initUI();
}

void CurrentPlotImpl::initUI()
{
    QObject::connect(m_deletePlotBtn, &QPushButton::clicked, [this]()
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();
        pm->deleteCurrentPlot();
        m_plotName->setText( "Not selected" );
        m_shapeName->setText( "Not selected" );
    });

    QObject::connect(m_saveInFileBtn, &QPushButton::clicked, [this]()
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();
        pm->saveCurrentPlotInFile();
    });

    // Move Plot
    QObject::connect(m_movePlotLeft, &QPushButton::clicked, [this]()
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();
        QString text = m_editBoxStepX->text();
        std::string ebText = text.toStdString();

        double step = 0.0;
        if( !ebText.empty() )
        {
            LOG_RETURN_IF( !IsFloat( ebText ), "Period should be a number!" );
            step = std::stod( ebText );
        }

        pm->moveCurrentPlotLeft( step );
    });

    QObject::connect(m_movePlotRight, &QPushButton::clicked, [this]()
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();
        QString text = m_editBoxStepX->text();
        std::string ebText = text.toStdString();

        double step = 0.0;
        if( !ebText.empty() )
        {
            LOG_RETURN_IF( !IsFloat( ebText ), "Period should be a number!" );
            step = std::stod( ebText );
        }

        pm->moveCurrentPlotRight( step );
    });

    QObject::connect(m_movePlotUp, &QPushButton::clicked, [this]()
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();
        QString text = m_editBoxStepY->text();
        std::string ebText = text.toStdString();

        double step = 0.0;
        if( !ebText.empty() )
        {
            LOG_RETURN_IF( !IsFloat( ebText ), "Period should be a number!" );
            step = std::stod( ebText );
        }

        pm->moveCurrentPlotUp( step );
    });

    QObject::connect(m_movePlotDown, &QPushButton::clicked, [this]()
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();
        QString text = m_editBoxStepY->text();
        std::string ebText = text.toStdString();

        double step = 0.0;
        if( !ebText.empty() )
        {
            LOG_RETURN_IF( !IsFloat( ebText ), "Period should be a number!" );
            step = std::stod( ebText );
        }

        pm->moveCurrentPlotDown( step );
    });


    // Period
    QObject::connect(m_movePeriodLeft, &QPushButton::clicked, [this]()
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();

        std::string ebText = m_editBoxPeriodStep->text().toStdString();

        double periodStep = 0.0;
        if( !ebText.empty() )
        {
            LOG_RETURN_IF( !IsFloat( ebText ), "Period should be a number!" );
            periodStep = std::stod( ebText );
            LOG_RETURN_IF( periodStep < 0.0f, "Period cannot be negative!" );
        }

        pm->moveByPeriodLeft( periodStep );
    });

    QObject::connect(m_movePeriodRight, &QPushButton::clicked, [this]()
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();

        std::string ebText = m_editBoxPeriodStep->text().toStdString();

        double periodStep = 0.0;
        if( !ebText.empty() )
        {
            LOG_RETURN_IF( !IsFloat( ebText ), "Period should be a number!" );
            periodStep = std::stod( ebText );
            LOG_RETURN_IF( periodStep < 0.0f, "Period cannot be negative!" );
        }

        pm->moveByPeriodRight( periodStep );
    });
}

void CurrentPlotImpl::setCurrentPlot( const Plot& plot )
{
    m_plotName->setText( plot.name );
    m_shapeName->setText( QString( plot.scatterShape.getShapeName().c_str() ) );
}

void CurrentPlotImpl::showOffsetX( double value )
{
    m_offsetXLabel->setText( QString( std::to_string( value ).c_str() ) );
}

void CurrentPlotImpl::showOffsetY( double value )
{
    m_offsetYLabel->setText( QString( std::to_string( value ).c_str() ) );
}

void CurrentPlotImpl::showOffsetP( double value )
{
    m_offsetPLabel->setText( QString( std::to_string( value ).c_str() ) );
}
