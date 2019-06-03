#ifndef CurrentPlotImpl_H
#define CurrentPlotImpl_H

#include "managers/PlotsManager.h"

class QLabel;
class QPushButton;
class QLineEdit;

class CurrentPlotImpl
{
public:
    CurrentPlotImpl();
    ~CurrentPlotImpl();

    void assignUI( const QMainWindow* ui );

    void initUI();
    void setCurrentPlot( const Plot& plot );

    void showOffsetX( double value );
    void showOffsetY( double value );
    void showOffsetP( double value );

private:

    QLabel* m_plotName;
    QLabel* m_shapeName;

    QLabel* m_offsetXLabel;
    QLabel* m_offsetYLabel;
    QLabel* m_offsetPLabel;

    QPushButton* m_deletePlotBtn;
    QPushButton* m_saveInFileBtn;

    QPushButton* m_movePlotLeft;
    QPushButton* m_movePlotRight;
    QPushButton* m_movePlotUp;
    QPushButton* m_movePlotDown;

    QPushButton* m_movePeriodLeft;
    QPushButton* m_movePeriodRight;

    QLineEdit* m_editBoxPeriodStep;
    QLineEdit* m_editBoxStepX;
    QLineEdit* m_editBoxStepY;

};

#endif // CurrentPlotImpl_H
