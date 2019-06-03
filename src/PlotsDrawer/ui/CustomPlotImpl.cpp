#include "CustomPlotImpl.h"

#include "MainIncludes.h"
#include "qcustomplot.h"

CustomPlotImpl::CustomPlotImpl()
{
}

CustomPlotImpl::~CustomPlotImpl()
{

}

void CustomPlotImpl::assignUI( const QMainWindow* ui )
{
    m_plot = FindUIElementInWindow<QCustomPlot*>( ui, "widgetPlot" );
    m_plot->yAxis->setRangeReversed( true );
}

void CustomPlotImpl::addPlot( const Plot& plot )
{
    const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();
    QCPGraph* graph = m_plot->addGraph();
    pm->setGraphToPlot( plot.name, graph );

    updatePlot( pm->getPlotByName( plot.name ) );
    addErrors( pm->getPlotByName( plot.name ) );
}

void CustomPlotImpl::addErrors( const Plot& plot )
{
    const QVector< Axis >& resultData = plot.resultData;

    QVector< double > yError;
    for( const Axis& axis : resultData )
        yError.push_back( axis.yError );

    if( plot.showError )
    {
        QCPErrorBars *errorBars = new QCPErrorBars( m_plot->xAxis, m_plot->yAxis );
        errorBars->removeFromLegend();
        errorBars->setDataPlottable( plot.graph );
        errorBars->setData( yError );
    }

    //m_plot->yAxis->setRangeReversed( true );

    m_plot->replot();
}

void CustomPlotImpl::updatePlot( const Plot& plot )
{
    const QVector< Axis >& resultData = plot.resultData;
    const PlotScatterShape& pss = plot.scatterShape;

    QVector< double > x, y;
    for( const Axis& axis : resultData )
    {
        x.push_back( axis.x );
        y.push_back( axis.y );
    }

    plot.graph->setData( x, y );
    plot.graph->setLineStyle( QCPGraph::lsNone );
    plot.graph->setScatterStyle( QCPScatterStyle( pss.shape, pss.color, pss.size ) );
    plot.graph->setName( plot.name );
    m_plot->legend->setVisible( true );

    m_plot->replot();
}

void CustomPlotImpl::deletePlot( const Plot& plot )
{
    m_plot->removeGraph( plot.graph );
    m_plot->replot();
}

void CustomPlotImpl::flipXAxis()
{
    m_plot->xAxis->setRangeReversed( !m_plot->xAxis->rangeReversed() );
    m_plot->replot();
}

void CustomPlotImpl::flipYAxis()
{
    m_plot->yAxis->setRangeReversed( !m_plot->yAxis->rangeReversed() );
    m_plot->replot();
}
