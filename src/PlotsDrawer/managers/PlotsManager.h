#ifndef PlotsManager_H
#define PlotsManager_H

#include <QString>
#include <unordered_map>
#include <fstream>
#include <functional>

#include "qcustomplot.h"

using VariablesTable = std::unordered_map< std::string, QVector< double > >;

struct PlotScatterShape
{
    PlotScatterShape()
        : shape( QCPScatterStyle::ScatterShape::ssNone )
        , size( 5u )
        , color( QColor::fromRgb( 255,0,0 ) )
    {}

    QCPScatterStyle::ScatterShape shape;
    QColor color;
    size_t size;

    std::string getShapeName() const
    {
        switch( shape )
        {
            case QCPScatterStyle::ScatterShape::ssNone: return "None, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssDot: return "Dot, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssCross: return "Cross, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssPlus: return "Plus, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssCircle: return "Circle, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssDisc: return "Disc, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssSquare: return "Square, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssDiamond: return "Diamond, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssStar: return "Star, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssTriangle: return "Triangle, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssTriangleInverted: return "TriangleInverted, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssCrossSquare: return "CrossSquare, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssPlusSquare: return "PlusSquare, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssCrossCircle: return "CrossCircle, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssPlusCircle: return "PlusCircle, Size = " + std::to_string( size );
            case QCPScatterStyle::ScatterShape::ssPeace: return "Peace, Size = " + std::to_string( size );
        }

        return std::string();
    }
};

struct Axis
{
    Axis()
        : x( 0.0f )
        , y( 0.0f )
        , yError( 0.0f )
    {}

    double x;
    double y;
    double yError;
};

struct Plot
{
    Plot()
        : graph( NULL )
        , showError( false )
        , offsetPeriod( 0.0f )
        , offsetX( 0.0f )
        , offsetY( 0.0f )
    {}

    QString name;
    QString filename;

    PlotScatterShape scatterShape;
    double JD0;
    double period;

    double offsetPeriod;
    double offsetX;
    double offsetY;

    VariablesTable originData;
    QVector< Axis > formulaData;
    Axis offsetData;
    QVector< Axis > resultData;

    QCPGraph* graph;
    bool showError;
};

struct AxisLimits
{
    AxisLimits()
        : xMin( 0.0f )
        , yMin( 0.0f )
        , xMax( 5.0f )
        , yMax( 5.0f )
    {}

    double xMin;
    double yMin;
    double xMax;
    double yMax;
};

struct CurrentPlot
{
    QString name;
};

// Callbacks
using AddPlotCallback = std::function< void( const Plot& plot ) >;
using SetCurrentPlotCallback = std::function< void( const Plot& plot ) >;
using UpdatePlotCallback = std::function< void( const Plot& plot ) >;
using DeletePlotCallback = std::function< void( const Plot& plot ) >;
using FlipXCallback = std::function< void() >;
using FlipYCallback = std::function< void() >;
using SavePlotInFileCallback = std::function< void( const Plot& plot ) >;

using Plots = std::unordered_map< std::string, Plot >;

class PlotsManager
{
public:
    PlotsManager();
    ~PlotsManager();

    // Axis Limits
    void setAxisLimitsMin( double x, double y );
    void setAxisLimitXMin( double x );
    void setAxisLimitYMin( double y );
    double getAxisLimitXMin() const { return m_axisLimits.xMin; }
    double getAxisLimitYMin() const { return m_axisLimits.yMin; }

    void setAxisLimitsMax( double x, double y );
    void setAxisLimitXMax( double x );
    void setAxisLimitYMax( double y );
    double getAxisLimitXMax() const { return m_axisLimits.xMax; }
    double getAxisLimitYMax() const { return m_axisLimits.yMax; }

    void flipXAxis();
    void flipYAxis();

    // Current Plot
    void setCurrentPlotByName( const QString& name );

    void moveCurrentPlotUp( double step );
    void moveCurrentPlotDown( double step );
    void moveCurrentPlotLeft( double step );
    void moveCurrentPlotRight( double step );

    void moveByPeriodLeft( double step );
    void moveByPeriodRight( double step );

    void deleteCurrentPlot();
    void saveCurrentPlotInFile();

    // Add Plot
    VariablesTable readPlotFromFile( const QString& filename );

    void addPlot(
            const QString& name,
            double JD0,
            double period,
            const QString& filename,
            bool showError );

    QVector< Axis > resolveResultData( const Plot& plot );
    QVector< Axis > resolveFormulaData( const Plot& plot );

    void setCallbackAddPlot( AddPlotCallback callback ) { m_addPlotCallback = callback; }
    void setCallbackSetCurrentPlot( SetCurrentPlotCallback callback ) { m_setCurrentPlotCallback = callback; }
    void setCallbackUpdatePlot( UpdatePlotCallback callback ) { m_updatePlotCallback = callback; }
    void setCallbackDeletePlot( DeletePlotCallback callback ) { m_deletePlotCallback = callback; }
    void setCallbackFlipX( FlipXCallback callback ) { m_flipXCallback = callback; }
    void setCallbackFlipY( FlipYCallback callback ) { m_flipYCallback = callback; }
    void setCallbackSavePlotInFile( SavePlotInFileCallback callback ) { m_savePlotInFileCallback = callback; }


    void updatePlot( Plot& plot );

    // Other

    // Available scatter shapes and sizes
    void defineAvailableScatterShapes();

    PlotScatterShape getAvailableScatterShape();
    void setGraphToPlot( const QString& plotName, QCPGraph* graph );
    const Plot& getPlotByName( const QString& plotName );

    // Getters
    inline const Plots& getPlots() const { return m_plots; }

private:

    // Axis Limits
    AxisLimits m_axisLimits;

    // Current Plot
    Plot m_currentPlot;

    // Add Plot // Plots
    Plots m_plots;
    AddPlotCallback m_addPlotCallback;
    SetCurrentPlotCallback m_setCurrentPlotCallback;
    UpdatePlotCallback m_updatePlotCallback;
    DeletePlotCallback m_deletePlotCallback;
    FlipXCallback m_flipXCallback;
    FlipYCallback m_flipYCallback;
    SavePlotInFileCallback m_savePlotInFileCallback;

    // Other

    // Available scatter shapes and sizes
    std::list<PlotScatterShape> m_availableShapes;
};

#endif // PlotsManager_H
