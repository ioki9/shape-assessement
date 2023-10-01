
#include "sellipse.h"
#include <QPainter>
#include "ishapevisitor.h"
SEllipse::SEllipse(int id, QWidget *parent) : IShape(id,parent)
{

}

SEllipse::~SEllipse()
{

}

void SEllipse::accept(IShapeVisitor* visitor)
{
    visitor->visit(this);
}

void SEllipse::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);
    m_path.clear();
    m_path.addEllipse(this->rect());
    m_path.closeSubpath();
    painter.drawPath(m_path);

}

