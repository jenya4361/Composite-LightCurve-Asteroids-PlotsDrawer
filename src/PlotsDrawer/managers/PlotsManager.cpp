#include "PlotsManager.h"
#include "MainIncludes.h"
#include <list>

PlotsManager::PlotsManager()
{
    defineAvailableScatterShapes();
}

PlotsManager::~PlotsManager()
{

}

// Axis Limits

void PlotsManager::setAxisLimitsMin( double x, double y )
{
    m_axisLimits.xMin = x;
    m_axisLimits.yMin = y;
}

void PlotsManager::setAxisLimitXMin( double x )
{
    m_axisLimits.xMin = x;
}

void PlotsManager::setAxisLimitYMin( double y )
{
    m_axisLimits.yMin = y;
}

void PlotsManager::setAxisLimitsMax( double x, double y )
{
    m_axisLimits.xMax = x;
    m_axisLimits.yMax = y;
}

void PlotsManager::setAxisLimitXMax( double x )
{
    m_axisLimits.xMax = x;
}

void PlotsManager::setAxisLimitYMax( double y )
{
    m_axisLimits.yMax = y;
}

void PlotsManager::setGraphToPlot( const QString& plotName, QCPGraph* graph )
{
    LOG_RETURN_IF( !m_plots.count( plotName.toStdString() ), "Plot " + plotName.toStdString() + "missing." );

    m_plots.at( plotName.toStdString() ).graph = graph;
}

const Plot& PlotsManager::getPlotByName( const QString& plotName )
{
    return m_plots[plotName.toStdString()];
}

void PlotsManager::flipXAxis()
{
    if( m_flipXCallback )
        m_flipXCallback();
}

void PlotsManager::flipYAxis()
{
    if( m_flipYCallback )
        m_flipYCallback();
}

// Current Plot
void PlotsManager::setCurrentPlotByName( const QString& name )
{
    LOG_RETURN_IF( !m_plots.count( name.toStdString() ), "Plot " + name.toStdString() + "missing." );

    m_currentPlot = m_plots.at( name.toStdString() );

    if( m_setCurrentPlotCallback )
        m_setCurrentPlotCallback( m_currentPlot );
    if( m_updatePlotCallback )
        m_updatePlotCallback( m_currentPlot );

    PLog( "Current plot = " + name.toStdString() );
}

void PlotsManager::moveCurrentPlotUp( double step )
{
    const QString& name = m_currentPlot.name;
    LOG_RETURN_IF( !name.size(), "Current plot is not chosen!" );
    LOG_RETURN_IF( !m_plots.count( name.toStdString() ), "Plot " + name.toStdString() + "missing." );

    Axis offset = m_currentPlot.offsetData;
    double offsetY = m_currentPlot.offsetY;

    offset.y += step;
    offsetY += step;

    Plot& plot = m_plots.at( name.toStdString() );

    plot.offsetData = offset;
    m_currentPlot.offsetData = offset;
    plot.offsetY = offsetY;
    m_currentPlot.offsetY = offsetY;

    updatePlot( plot );
    if( m_updatePlotCallback )
        m_updatePlotCallback( plot );
}

void PlotsManager::moveCurrentPlotDown( double step )
{
    const QString& name = m_currentPlot.name;
    LOG_RETURN_IF( !name.size(), "Current plot is not chosen!" );
    LOG_RETURN_IF( !m_plots.count( name.toStdString() ), "Plot " + name.toStdString() + "missing." );

    Axis offset = m_currentPlot.offsetData;
    double offsetY = m_currentPlot.offsetY;

    offset.y -= step;
    offsetY -= step;

    Plot& plot = m_plots.at( name.toStdString() );

    plot.offsetData = offset;
    m_currentPlot.offsetData = offset;
    plot.offsetY = offsetY;
    m_currentPlot.offsetY = offsetY;

    updatePlot( plot );
    if( m_updatePlotCallback )
        m_updatePlotCallback( plot );
}

void PlotsManager::moveCurrentPlotLeft( double step )
{
    const QString& name = m_currentPlot.name;
    LOG_RETURN_IF( !name.size(), "Current plot is not chosen!" );
    LOG_RETURN_IF( !m_plots.count( name.toStdString() ), "Plot " + name.toStdString() + "missing." );

    Axis offset = m_currentPlot.offsetData;
    double offsetX = m_currentPlot.offsetX;

    offset.x -= step;
    offsetX -= step;

    Plot& plot = m_plots.at( name.toStdString() );

    plot.offsetData = offset;
    m_currentPlot.offsetData = offset;
    plot.offsetX = offsetX;
    m_currentPlot.offsetX = offsetX;

    updatePlot( plot );
    if( m_updatePlotCallback )
        m_updatePlotCallback( plot );
}

void PlotsManager::moveCurrentPlotRight( double step )
{
    const QString& name = m_currentPlot.name;
    LOG_RETURN_IF( !name.size(), "Current plot is not chosen!" );
    LOG_RETURN_IF( !m_plots.count( name.toStdString() ), "Plot " + name.toStdString() + "missing." );

    Axis offset = m_currentPlot.offsetData;
    double offsetX = m_currentPlot.offsetX;

    offset.x += step;
    offsetX += step;

    Plot& plot = m_plots.at( name.toStdString() );

    plot.offsetData = offset;
    m_currentPlot.offsetData = offset;
    plot.offsetX = offsetX;
    m_currentPlot.offsetX = offsetX;

    updatePlot( plot );
    if( m_updatePlotCallback )
        m_updatePlotCallback( plot );
}

void PlotsManager::moveByPeriodLeft( double step )
{
    const QString& name = m_currentPlot.name;
    LOG_RETURN_IF( !name.size(), "Current plot is not chosen!" );
    LOG_RETURN_IF( !m_plots.count( name.toStdString() ), "Plot " + name.toStdString() + "missing." );

    double period = m_currentPlot.period;
    double offsetPeriod = m_currentPlot.offsetPeriod;

    period -= step;
    offsetPeriod -= step;
    LOG_RETURN_IF( period == 0.0, "Period in null. Formula error." )

    Plot& plot = m_plots.at( name.toStdString() );
    plot.period = period;
    m_currentPlot.period = period;
    plot.offsetPeriod = offsetPeriod;
    m_currentPlot.offsetPeriod = offsetPeriod;

    updatePlot( plot );
    if( m_updatePlotCallback )
        m_updatePlotCallback( plot );
}

void PlotsManager::moveByPeriodRight( double step )
{
    const QString& name = m_currentPlot.name;
    LOG_RETURN_IF( !name.size(), "Current plot is not chosen!" );
    LOG_RETURN_IF( !m_plots.count( name.toStdString() ), "Plot " + name.toStdString() + "missing." );

    double period = m_currentPlot.period;
    double offsetPeriod = m_currentPlot.offsetPeriod;

    period += step;
    offsetPeriod += step;
    LOG_RETURN_IF( period == 0.0, "Period in null. Formula error." )

    Plot& plot = m_plots.at( name.toStdString() );
    plot.period = period;
    m_currentPlot.period = period;
    plot.offsetPeriod = offsetPeriod;
    m_currentPlot.offsetPeriod = offsetPeriod;

    updatePlot( plot );
    if( m_updatePlotCallback )
        m_updatePlotCallback( plot );
}

void PlotsManager::deleteCurrentPlot()
{
    const QString& name = m_currentPlot.name;
    LOG_RETURN_IF( !name.size(), "Current plot is not chosen!" );

    if( m_deletePlotCallback )
        m_deletePlotCallback( m_currentPlot );

    m_plots.erase( name.toStdString() );
    m_currentPlot = Plot();
}

void PlotsManager::saveCurrentPlotInFile()
{
    const QString& name = m_currentPlot.name;
    LOG_RETURN_IF( !name.size(), "Current plot is not chosen!" );
    LOG_RETURN_IF( !m_plots.count( name.toStdString() ), "Plot " + name.toStdString() + "missing." );

    if( m_savePlotInFileCallback )
        m_savePlotInFileCallback( m_plots.at( name.toStdString() ) );
}

VariablesTable PlotsManager::readPlotFromFile( const QString& filename )
{
    VariablesTable table;
    std::ifstream fin( filename.toLocal8Bit() );

    if( fin.fail() )
    {
        PLog( "Cannot read file! Please recheck filename." );
        return VariablesTable();
    }

    while( !fin.eof() )
    {
        double JD, R, RError;
        fin >> JD >> R >> RError;

        table["JD"].push_back( JD );
        table["R"].push_back( R );
        table["RError"].push_back( RError );
    }

    fin.close();

    return table;
}

void PlotsManager::addPlot(
        const QString& name,
        double JD0,
        double period,
        const QString& filename,
        bool showError )
{
    LOG_RETURN_IF( m_plots.count( name.toStdString() ), "Such name is already exists." );
    LOG_RETURN_IF( !name.size(), "Field 'name' is empty." );
    LOG_RETURN_IF( !filename.size(), "Field 'filename' is empty." );
    LOG_RETURN_IF( period <= 0.0f, "Period cannot be negative or zero" );

    Plot newPlot;
    newPlot.name = name;
    newPlot.JD0 = JD0;
    newPlot.filename = filename;
    newPlot.period = period;
    newPlot.originData = readPlotFromFile( filename );
    newPlot.scatterShape = getAvailableScatterShape();
    newPlot.showError = showError;

    LOG_RETURN_IF( newPlot.originData.empty(), "File read error!" );

    const QVector< double >& JD = newPlot.originData["JD"];
    const QVector< double >& R = newPlot.originData["R"];
    const QVector< double >& RError = newPlot.originData["RError"];

    bool isSizesEqual = JD.size() == R.size() && JD.size() == RError.size();
    LOG_RETURN_IF( !isSizesEqual, "Columns data amount is different!" );

    updatePlot( newPlot );
    m_plots[name.toStdString()] = newPlot;

    if( m_addPlotCallback )
        m_addPlotCallback( newPlot );
}

QVector< Axis > PlotsManager::resolveFormulaData( const Plot& plot )
{
    QVector< Axis > result;
    const VariablesTable& originData = plot.originData;

    const QVector< double >& JDArray = originData.at( "JD" );
    const QVector< double >& RArray = originData.at( "R" );
    const QVector< double >& RErrorArray = originData.at( "RError" );
    double JD0 = plot.JD0;
    double period = plot.period;

    for( int i = 0; i < JDArray.size(); i++ )
    {
        Axis axis;

        const double& JD = JDArray[i];
        const double& R = RArray[i];
        const double& RError = RErrorArray[i];

        double formula = ( ( JD - JD0 ) / period ) - int( ( JD - JD0 ) / period );

        axis.x = formula;
        axis.y = R;
        axis.yError = RError;

        result.push_back( axis );
    }

    return result;
}

QVector< Axis > PlotsManager::resolveResultData( const Plot& plot )
{
    QVector< Axis > result;

    const QVector< Axis >& formulaData = plot.formulaData;
    const Axis& offsetData = plot.offsetData;

    for( int i = 0; i < formulaData.size(); i++ )
    {
        const Axis& fData = formulaData[i];

        Axis axis;
        axis.x = fData.x + offsetData.x;
        axis.y = fData.y + offsetData.y;
        axis.yError = fData.yError;

        result.push_back( axis );
    }


    return result;
}

void PlotsManager::updatePlot( Plot& plot )
{
    // VariablesTable originData = plot.originData;
    plot.formulaData = resolveFormulaData( plot );
    plot.resultData = resolveResultData( plot );
}

std::vector<QColor> getAvailableColors()
{
    QColor red = QColor::fromRgb( 255,0,0 );
    QColor blue = QColor::fromRgb( 0,0,255 );
    QColor black = QColor::fromRgb( 0,0,0 );
    QColor yellow = QColor::fromRgb( 255,80,0 );
    QColor green = QColor::fromRgb( 46,139,87 );
    QColor cyan = QColor::fromRgb( 0,255,255 );
    QColor orange = QColor::fromRgb( 255,160,0 );
    QColor pink = QColor::fromRgb( 255,0,110 );
    QColor violet = QColor::fromRgb( 72,0,124 );
    QColor br = QColor::fromRgb( 125,55,22 );
    QColor gray = QColor::fromRgb( 78,106,124 );

    std::vector<QColor> availbableColors = {
        red,
        blue,
        black,
        yellow,
        green,
        cyan,
        orange,
        pink,
        violet,
        br,
        gray
    };

    return availbableColors;
}

std::list<size_t> getAvailableSizes()
{
    std::list<size_t> availbableSizes = {
        8, 12, 14, 16, 18, 20, 22
    };

    return availbableSizes;
}

std::list<QCPScatterStyle::ScatterShape> getAvailableShapes()
{
    std::list<QCPScatterStyle::ScatterShape> shapes = {
        QCPScatterStyle::ScatterShape::ssCircle,
        QCPScatterStyle::ScatterShape::ssTriangle,
        QCPScatterStyle::ScatterShape::ssStar,
        QCPScatterStyle::ScatterShape::ssCross,
        QCPScatterStyle::ScatterShape::ssPlus,
        QCPScatterStyle::ScatterShape::ssDisc,
        QCPScatterStyle::ScatterShape::ssSquare,
        QCPScatterStyle::ScatterShape::ssDiamond,
        QCPScatterStyle::ScatterShape::ssTriangleInverted,
        QCPScatterStyle::ScatterShape::ssCrossSquare,
        QCPScatterStyle::ScatterShape::ssPlusSquare,
        QCPScatterStyle::ScatterShape::ssCrossCircle,
        QCPScatterStyle::ScatterShape::ssPlusCircle,
        QCPScatterStyle::ScatterShape::ssPeace
    };

    return shapes;
}

void PlotsManager::defineAvailableScatterShapes()
{
    std::vector<QColor> availbableColors = getAvailableColors();
    std::list<size_t> availableSizes = getAvailableSizes();
    std::list<QCPScatterStyle::ScatterShape> availableShapes = getAvailableShapes();

    for( size_t size : availableSizes )
    {
        size_t color_index = 0;
        for( QCPScatterStyle::ScatterShape shape : availableShapes )
        {
            if( color_index >= availbableColors.size() )
                color_index = 0;

            QColor color = availbableColors[color_index];
            color_index++;

            PlotScatterShape pss;
            pss.size = size;
            pss.color = color;
            pss.shape = shape;

            m_availableShapes.push_back( pss );
        }
    }
}

PlotScatterShape PlotsManager::getAvailableScatterShape()
{
    if( m_availableShapes.empty() )
        defineAvailableScatterShapes();

    PlotScatterShape pss = m_availableShapes.front();
    m_availableShapes.pop_front();

    return pss;
}
