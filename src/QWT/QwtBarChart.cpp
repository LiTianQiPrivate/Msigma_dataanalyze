#include "QwtBarChart.h"
#include "qwt_scale_draw.h"

QwtBarChart::QwtBarChart(QWidget *parent,QString className):
    QwtPlotBase(parent,className)
{
    //setAutoFillBackground(false);
}

QwtBarChart::~QwtBarChart()
{
    if(cruve)
    {
        delete cruve;
        cruve = NULL;
    }
}

void QwtBarChart::setModelBases(std::vector<ModelBase *> modelObjects, int index)
{
    clearModelBase();
    for(int i = 0; i < modelObjects.size(); i++)
    {
            modelBases.push_back(modelObjects[i]);
    }
    double xMin = 10000000, xMax = -10000000;
    double yMin = 10000000, yMax = -10000000;
    for(int i = 0; i < modelBases.size(); i++)
    {
        ModelBase* object = modelBases[i];
        std::vector<Point2D> points = object->getPoint2D();
        for(int j = 0; j < points.size(); j++)
        {
            Point2D p = points[j];
            double x = p.x, y = p.y;

            if(xMin > x)
            {
                xMin = x;
            }
            if(xMax < x)
            {
                xMax = x;
            }
            if(yMin > y)
            {
                yMin = y;
            }
            if(yMax < y)
            {
                yMax = y;
            }
        }
    }
    //setAxisScale(QwtPlot::xBottom,-180,180,30);
    setAxisScale(QwtPlot::yLeft,yMax,yMin);
    cruve = new QwtPlotMultiBarChart;
    cruve->setLayoutPolicy(QwtPlotMultiBarChart::AutoAdjustSamples);
    QVector<QVector<double>> samples;
    for(int i=0;i<12;i++)
    {
        QVector<double>values;
        for(int j=0;j<modelBases.size();j++)
        {

            if(modelBases[j]->getShowHideFlag())
            {
                std::vector<Point2D> points = modelBases[j]->getPoint2D();
                values.push_back(points[12*i+(points.size()/12)].y);
            }
        }
        samples.push_back(values);
    }
    for(int i=0;i<modelBases.size();i++)
    {
        QwtColumnSymbol *symbol = new QwtColumnSymbol(QwtColumnSymbol::Box);
        symbol->setLineWidth(2);
        symbol->setFrameStyle( QwtColumnSymbol::Raised );
        symbol->setPalette(modelBases[i]->getColor());
        cruve->setSymbol(i,symbol);
    }
    cruve->setSamples(samples);
    //cruve->setStyle(QwtPlotMultiBarChart::Grouped);
    cruve->setSpacing(20);
    cruve->setMargin(2);
    cruve->attach(this);
    cruve->setOrientation(Qt::Vertical);
    setAxisScale(QwtPlot::xBottom,-0.5,12,1);
    setAxisAutoScale(QwtPlot::yLeft);
    this->replot();
}

void QwtBarChart::addModelBase(ModelBase *modelObject)
{
    //-----------??????x???y???????????????--------------//

//    QwtScaleDraw *scaleDraw1 = axisScaleDraw(QwtPlot::xBottom);
//    scaleDraw1->enableComponent(QwtScaleDraw::Backbone,false);
//    scaleDraw1->enableComponent(QwtScaleDraw::Ticks,false);
//    QwtScaleDraw *scaleDraw2 = axisScaleDraw(QwtPlot::yLeft);
//    scaleDraw2->enableComponent(QwtScaleDraw::Backbone,true);
//    scaleDraw2->enableComponent(QwtScaleDraw::Ticks,true);
//    plotLayout()->setAlignCanvasToScale(QwtPlot::xBottom,true);
//    plotLayout()->setAlignCanvasToScale(QwtPlot::yLeft,false);
//    plotLayout()->setCanvasMargin(0);
//    updateCanvasMargins();

}

void QwtBarChart::clearModelBase()
{
    if(cruve)
    {
        delete cruve;
        cruve = NULL;
    }
    modelBases.clear();
}

void QwtBarChart::showModelBase(int index)
{
    if(cruve->dataSize() > index)
    {
        modelBases[index]->setShowHideFlag(true);
    }
}

void QwtBarChart::hideModelBase(int index)
{
    if(cruve->dataSize() > index)
    {
        modelBases[index]->setShowHideFlag(false);
    }
}

void QwtBarChart::removeModelBase(int index)
{
    if(cruve->dataSize() > index)
    {
        modelBases.erase(modelBases.begin() + index);
    }
}

bool QwtBarChart::isVisible(int index)
{
    if(cruve->dataSize() > index)
    {
        return cruve->isVisible();
    }
    return false;
}

void QwtBarChart::getStandIndex(int index)
{
    if(this->modelBases.empty())
    {
        //QMessageBox::information(this, QString::fromLocal8Bit("?????????????????????"), QString::fromLocal8Bit("??????????????????!"));
        return ;
    }
    if(index == 0)   //  ???????????????
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(0);
        update();
    }
    else if(index == 1)   //  ???????????????
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(1);
        update();
    }
    else if(index == 2)   //   ???????????????
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(2);
        update();
    }
    else if(index == 3) //  ?????????????????????
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(3);
        update();
    }
    else if(index == 4)   //  ???????????????
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(4);
        update();
    }
    else if(index == 5)    // ?????????
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(5);
        update();
    }
    else if(index == 6)   // ????????????
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(6);
        update();
    }
    else if(index == 7)   // ???????????????
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        drawLineFlag = true;
        this->replot();
        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(7);
        update();
    }
    else if(index == 10)    // ????????????
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        drawLineFlag = false;

        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(7);
        this->replot();
        update();
    }
    else if(index == 11)   //  ????????????
    {
        zoomer = new QwtPlotZoomer( canvas() );
        zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
            Qt::LeftButton ,Qt::ControlModifier );
        const QColor c( Qt::darkBlue );
        zoomer->setRubberBandPen(QColor(Qt::blue));
        zoomer->setTrackerPen(QColor(Qt::black));
        this->replot();
        picker->setDrawShapeType(9);
        picker->setRubberBand(QwtPicker::CrossRubberBand);
        update();
    }
    else if(index == 12)    // ????????????
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        drawLineFlag = false;

        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(12);
        this->replot();
        update();
    }
    else if(index == 13)
    {
        if(zoomer)
        {
            delete zoomer;
            zoomer = NULL;
        }
        drawLineFlag = false;

        picker->setRubberBand(QwtPicker::NoRubberBand);
        picker->setDrawShapeType(13);
        this->replot();
        update();
    }
    else if(index == 8)    // ????????????
    {
        this->removeItem(getLastDrawBase());
        this->replot();
        if(drawBases.size() > 0)
        {
            drawBases.pop_back();
        }
        picker->setRubberBand(QwtPicker::CrossRubberBand);
        picker->setDrawShapeType(8);
        update();
    }
    else if(index == 9)    //  ??????????????????
    {
        for(int i=0;i<drawBases.size();i++)
        {
            this->removeItem(drawBases[i]);
            delete drawBases[i];
        }
        drawBases.clear();
        zoomer = new QwtPlotZoomer( canvas() );
        zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
            Qt::LeftButton ,Qt::ControlModifier );
        const QColor c( Qt::darkBlue );
        zoomer->setRubberBandPen(QColor(Qt::blue));
        zoomer->setTrackerPen(QColor(Qt::black));
        this->replot();
        picker->setRubberBand(QwtPicker::CrossRubberBand);
        picker->setDrawShapeType(9);
        update();
    }
}
