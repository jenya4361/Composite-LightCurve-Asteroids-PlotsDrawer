#ifndef AxisLimitsImpl_H
#define AxisLimitsImpl_H

#include <QMainWindow>
#include <functional>

class QLineEdit;
class QPushButton;

using AxisLimitsCallback = std::function<void( double xMin, double yMin, double xMax, double yMax )>;

class AxisLimitsImpl
{
public:
    AxisLimitsImpl( );
    ~AxisLimitsImpl();

    void assignUI( const QMainWindow* ui );
    void setCallbackRange( AxisLimitsCallback callback );

private:

    QPushButton* m_flipXBtn;
    QPushButton* m_flipYBtn;

    QLineEdit* m_xMin;
    QLineEdit* m_yMin;
    QLineEdit* m_xMax;
    QLineEdit* m_yMax;
    AxisLimitsCallback m_callback;

};

#endif // AxisLimitsImpl_H
