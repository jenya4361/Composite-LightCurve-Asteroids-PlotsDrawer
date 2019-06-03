#ifndef AddPlotImpl_H
#define AddPlotImpl_H

#include <QMainWindow>

class QLineEdit;
class QPushButton;
class QCheckBox;

class AddPlotImpl
{
public:
    AddPlotImpl();
    ~AddPlotImpl();

    void assignUI( const QMainWindow* ui );

    void clearFields();

private:

    QLineEdit* m_editBoxAddPlotName;
    QLineEdit* m_editBoxAddPlotJD0;
    QLineEdit* m_editBoxAddPlotFilename;
    QLineEdit* m_editBoxAddPlotPeriod;

    QPushButton* m_addPlotBtn;


    QCheckBox* m_checkBoxShowError;
};

#endif // AddPlotImpl_H
