#include "PlotsImpl.h"
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QRadioButton>

#include "MainIncludes.h"

PlotsImpl::PlotsImpl()
{
}

PlotsImpl::~PlotsImpl()
{

}

void PlotsImpl::assignUI( const QMainWindow* ui )
{
    m_scrollAreaPlots = FindUIElementInWindow<QScrollArea*>( ui, "scrollAreaPlots" );
    m_widgetInsideScrollArea = FindUIElementInWindow<QLayout*>( ui, "gridLayout_2" );
}

void PlotsImpl::addPlotButton( const Plot& plot )
{
    const QString& plotName = plot.name;
    QRadioButton* radioButton = new QRadioButton();
    QString shapeName = QString( plot.scatterShape.getShapeName().c_str() );
    radioButton->setText( plot.name + " (" + shapeName + ")" );

    QObject::connect(radioButton, &QPushButton::clicked, [this, plotName]()
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();
        if( m_buttons.count( plotName.toStdString() ) )
        {
            pm->setCurrentPlotByName( plotName );
        }
    });

    m_buttons[plotName.toStdString()] = radioButton;
    m_widgetInsideScrollArea->addWidget( radioButton );
}

void PlotsImpl::deletePlot( const Plot& plot )
{
    LOG_RETURN_IF( !m_buttons.count( plot.name.toStdString() ), "There is no plot in UI = " + plot.name.toStdString() );

    m_widgetInsideScrollArea->removeWidget( m_buttons[plot.name.toStdString()] );
    delete m_buttons[plot.name.toStdString()];
    m_buttons.erase( plot.name.toStdString() );
}
