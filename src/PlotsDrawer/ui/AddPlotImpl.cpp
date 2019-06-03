#include "AddPlotImpl.h"
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>


#include "managers/PlotsManager.h"
#include "MainIncludes.h"

AddPlotImpl::AddPlotImpl()
{
}

AddPlotImpl::~AddPlotImpl()
{

}

void AddPlotImpl::assignUI( const QMainWindow* ui )
{
    m_editBoxAddPlotName = FindUIElementInWindow<QLineEdit*>( ui, "editBoxAddPlotName" );
    m_editBoxAddPlotJD0 = FindUIElementInWindow<QLineEdit*>( ui, "editBoxAddPlotJD0" );
    m_editBoxAddPlotFilename = FindUIElementInWindow<QLineEdit*>( ui, "editBoxAddPlotFilename" );
    m_editBoxAddPlotPeriod = FindUIElementInWindow<QLineEdit*>( ui, "editBoxAddPlotPeriod" );

    m_addPlotBtn = FindUIElementInWindow<QPushButton*>( ui, "addPlotBtn" );
    m_checkBoxShowError = FindUIElementInWindow<QCheckBox*>( ui, "checkBoxShowError" );

    QObject::connect(m_addPlotBtn, &QPushButton::clicked, [this]()
    {
        const PlotsManagerPtr& pm = App::getMC()->getPlotsManager();
        QString plotName = m_editBoxAddPlotName->text();
        QString JD0Str = m_editBoxAddPlotJD0->text();
        QString filename = m_editBoxAddPlotFilename->text();
        QString periodStr = m_editBoxAddPlotPeriod->text();

        LOG_RETURN_IF( !plotName.size(), "Name field is empty!" );
        LOG_RETURN_IF( !JD0Str.size(), "JD0 field is empty!" );
        LOG_RETURN_IF( !filename.size(), "Filename field is empty!" );
        LOG_RETURN_IF( !periodStr.size(), "Period field is empty!" );

        LOG_RETURN_IF( !IsFloat( std::string( JD0Str.toLocal8Bit() ) ), "JD0 should be a number!" );
        LOG_RETURN_IF( !IsFloat( std::string( periodStr.toLocal8Bit() ) ), "y max should be a number!" );

        double JD0 = JD0Str.toDouble();
        double period = periodStr.toDouble();

        pm->addPlot( plotName, JD0, period, filename, m_checkBoxShowError->isChecked() );
    });
}

void AddPlotImpl::clearFields()
{
    m_editBoxAddPlotName->clear();
    m_editBoxAddPlotJD0->clear();
    m_editBoxAddPlotFilename->clear();
    m_editBoxAddPlotPeriod->clear();
}
