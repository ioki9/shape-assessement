
#include "striangle.h"
#include <QPainter>
#include <QMouseEvent>
#include "ishapevisitor.h"
STriangle::STriangle(int id,QWidget *parent) : IShape(id,parent)
{

}

STriangle::~STriangle()
{

}

void STriangle::accept(IShapeVisitor *visitor)
{
    visitor->visit(this);
}

void STriangle::draw(const QPoint &start, const QSize &bound_rect)
{
    IShape::draw(start,bound_rect);
    if(bound_rect.height() < 0)
    {
        m_upwards = true;
    }
    else
        m_upwards = false;
}

void STriangle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);
    m_path.clear();

    if(!m_upwards)
    {
        m_path.moveTo(QPoint(m_bound_rect.width()/2,0));
        m_path.lineTo(QPoint(0,m_bound_rect.height()));
        m_path.lineTo(QPoint(m_bound_rect.width(),m_bound_rect.height()));
        m_path.closeSubpath();
    }
    else
    {
        m_path.moveTo(QPoint(m_bound_rect.width()/2,m_bound_rect.height()));
        m_path.lineTo(QPoint(0,0));
        m_path.lineTo(QPoint(m_bound_rect.width(),0));
        m_path.closeSubpath();
    }
    painter.drawPath(m_path);

}



