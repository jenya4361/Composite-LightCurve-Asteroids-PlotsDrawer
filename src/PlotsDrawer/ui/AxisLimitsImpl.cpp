#include "AxisLimitsImpl.h"
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>

#include "MainIncludes.h"

#include "managers/PlotsManager.h"

AxisLimitsImpl::AxisLimitsImpl()
{
}

AxisLimitsImpl::~AxisLimitsImpl()
{

}

void AxisLimitsImpl::assignUI( const QMainWindow* ui )
{
    m_xMin = FindUIElementInWindow<QLineEdit*>( ui, "xMin" );
    m_yMin = FindUIElementInWindow<QLineEdit*>( ui, "yMin" );
    m_xMax = FindUIElementInWindow<QLineEdit*>( ui, "xMax" );
    m_yMax = FindUIElementInWindow<QLineEdit*>( ui, "yMax" );
    m_flipXBtn = FindUIElementInWindow<QPushButton*>( ui, "flipXBtn" );
    m_flipYBtn = FindUIElementInWindow<QPushButton*>( ui, "flipYBtn" );

    QObject::connect(m_xMin, &QLineEdit::textChanged, [this]( const QString& text )
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();

        LOG_RETURN_IF( !text.size(), "x min field is empty!" );
        LOG_RETURN_IF( !IsFloat( std::string( text.toLocal8Bit() ) ), "x min should be a number!" );

        double xMin = text.toDouble();
        double yMin = pm->getAxisLimitYMin();
        double xMax = pm->getAxisLimitXMax();
        double yMax = pm->getAxisLimitYMax();

        pm->setAxisLimitXMin( xMin );
        if( m_callback )
            m_callback( xMin, yMin, xMax, yMax );
    });

    QObject::connect(m_yMin, &QLineEdit::textChanged, [this]( const QString& text )
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();

        LOG_RETURN_IF( !text.size(), "y min field is empty!" );
        LOG_RETURN_IF( !IsFloat( std::string( text.toLocal8Bit() ) ), "y min should be a number!" );

        double xMin = pm->getAxisLimitXMin();
        double yMin = text.toDouble();
        double xMax = pm->getAxisLimitXMax();
        double yMax = pm->getAxisLimitYMax();

        pm->setAxisLimitYMin( yMin );
        if( m_callback )
            m_callback( xMin, yMin, xMax, yMax );
    });

    QObject::connect(m_xMax, &QLineEdit::textChanged, [this]( const QString& text )
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();

        LOG_RETURN_IF( !text.size(), "x max field is empty!" );
        LOG_RETURN_IF( !IsFloat( std::string( text.toLocal8Bit() ) ), "x max should be a number!" );

        double xMin = pm->getAxisLimitXMin();
        double yMin = pm->getAxisLimitYMin();
        double xMax = text.toDouble();
        double yMax = pm->getAxisLimitYMax();

        pm->setAxisLimitXMax( xMax );
        if( m_callback )
            m_callback( xMin, yMin, xMax, yMax );
    });

    QObject::connect(m_yMax, &QLineEdit::textChanged, [this]( const QString& text )
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();

        LOG_RETURN_IF( !text.size(), "y max field is empty!" );
        LOG_RETURN_IF( !IsFloat( std::string( text.toLocal8Bit() ) ), "y max should be a number!" );

        double xMin = pm->getAxisLimitXMin();
        double yMin = pm->getAxisLimitYMin();
        double xMax = pm->getAxisLimitXMax();
        double yMax = text.toDouble();

        pm->setAxisLimitYMax( yMax );
        if( m_callback )
            m_callback( xMin, yMin, xMax, yMax );
    });

    QObject::connect(m_flipXBtn, &QPushButton::clicked, [this]()
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();
        pm->flipXAxis();
    });

    QObject::connect(m_flipYBtn, &QPushButton::clicked, [this]()
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();
        pm->flipYAxis();
    });

}

void AxisLimitsImpl::setCallbackRange( AxisLimitsCallback callback )
{
    m_callback = callback;
}
