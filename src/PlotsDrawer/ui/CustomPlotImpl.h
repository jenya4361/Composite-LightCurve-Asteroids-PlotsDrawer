#ifndef CustomPlotImpl_H
#define CustomPlotImpl_H

class QCustomPlot;

#include "managers/PlotsManager.h"

class CustomPlotImpl
{
public:
    CustomPlotImpl();
    ~CustomPlotImpl();

    void assignUI( const QMainWindow* ui );

    void addPlot( const Plot& plot );
    void addErrors( const Plot& plot );
    void deletePlot( const Plot& plot );

    void updatePlot( const Plot& plot );

    void flipXAxis();
    void flipYAxis();

private:

    QCustomPlot* m_plot;

};

#endif // CustomPlotImpl_H
