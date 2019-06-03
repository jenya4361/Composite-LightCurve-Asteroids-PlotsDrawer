#ifndef PlotsImpl_H
#define PlotsImpl_H

#include "managers/PlotsManager.h"

#include <unordered_map>

class QScrollArea;
class QLayout;
class QRadioButton;

class PlotsImpl
{
public:
    PlotsImpl();
    ~PlotsImpl();

    void assignUI( const QMainWindow* ui );

    void addPlotButton( const Plot& plot );
    void deletePlot( const Plot& plot );

private:

    QScrollArea* m_scrollAreaPlots;
    QLayout* m_widgetInsideScrollArea;

    std::unordered_map< std::string, QRadioButton* > m_buttons;

};

#endif // PlotsImpl_H
