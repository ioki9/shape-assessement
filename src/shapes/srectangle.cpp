
#include "srectangle.h"
#include <QPainter>
#include <QMouseEvent>
#include "ishapevisitor.h"

SRectangle::SRectangle(int id,QWidget *parent) : IShape(id,parent)
{

}

SRectangle::~SRectangle()
{

}

void SRectangle::accept(IShapeVisitor *visitor)
{
    visitor->visit(this);
}

void SRectangle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    m_path.clear();
    m_path.addRect(this->rect());
    m_path.closeSubpath();
    painter.drawPath(m_path);
}





