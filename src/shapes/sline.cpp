
#include "sline.h"
#include <QPainter>
#include <cmath>
#include "ishapevisitor.h"

SLine::SLine(int id,QWidget *parent) : IShape(id,parent)
{
    this->setStyleSheet(".SLine { border-width: 0px; }");

    this->setAttribute(Qt::WA_TransparentForMouseEvents);
}

SLine::~SLine()
{

}
void SLine::accept(IShapeVisitor* visitor)
{
    visitor->visit(this);
}

void SLine::draw(const QPoint &start, const QSize &bound_rect)
{
    IShape::draw(start,bound_rect);
    if((bound_rect.width() < 0 && bound_rect.height() > 0) || (bound_rect.width() > 0 && bound_rect.height() < 0))
        m_mirrored = true;
    else
        m_mirrored = false;

}

void SLine::draw(const QPoint &start, const QPoint &end)
{
    this->draw(start,QSize( end.x() - start.x() ,end.y() - start.y()));
}

QPoint SLine::center() const
{
    return m_center;
}
//we need to check if distance(start_point,point) + distance(point,end_point) == distance(start,end_point)
bool SLine::contains_shape(const QPointF &point) const
{

    QPoint local = {static_cast<int>(point.x() - this->pos().x()),static_cast<int>(point.y() - this->pos().y())};

    if(m_mirrored)
    {
        return (std::sqrt(this->rect().width() - local.x()) + std::sqrt(local.y())) +
               (std::sqrt(local.x()) + std::sqrt(this->rect().height() - local.y()))
               == (std::sqrt(this->rect().width()) + std::sqrt(this->rect().height()));
    }
    else
    {
        return (std::sqrt(local.x()) + std::sqrt(local.y())) +
               (std::sqrt(this->rect().width() - local.x()) + std::sqrt(this->rect().height() - local.y()))
               == (std::sqrt(this->rect().width()) + std::sqrt(this->rect().height()));

    }

}

void SLine::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);

    if(m_mirrored)
        painter.drawLine(QPoint(this->rect().width(),0),QPoint(0,this->rect().height()));
    else
        painter.drawLine(QPoint(0,0),QPoint(this->rect().width(),this->rect().height()));
}

