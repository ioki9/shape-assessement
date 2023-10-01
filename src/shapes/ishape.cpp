#include "ishape.h"

#include <QPainter>
std::atomic_int IShape::m_available_id = -2;
IShape::IShape(int id, QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
    if(id < 0)
    {
        m_id = m_available_id;
        m_available_id--;
    }
}

IShape::~IShape()
{

}

void IShape::draw(const QPoint &start, const QSize &bound_rect)
{
    if(m_start == start && m_bound_rect == bound_rect)
        return;
    m_draw_params.first = start;
    m_draw_params.second = bound_rect;
    m_bound_rect = bound_rect;
    m_start = start;
    //in case we want to draw shape upwards from the starting point
    if(bound_rect.width() < 0)
    {
        m_start.setX(start.x() + bound_rect.width());
        m_bound_rect.setWidth(-1 * bound_rect.width());
    }
    if(bound_rect.height() < 0)
    {
        m_start.setY(start.y() + bound_rect.height());
        m_bound_rect.setHeight(-1 * bound_rect.height());
    }
    this->setGeometry(m_start.x(),m_start.y(),m_bound_rect.width() + 1,m_bound_rect.height() + 1);
    m_center = {m_start.x() + m_bound_rect.width() / 2, m_start.y() + m_bound_rect.height() / 2};
    update();
}

QPoint IShape::center() const
{
    return m_center;
}

bool IShape::contains_shape(const QPointF &point) const
{
    return m_path.contains(point - this->pos());
}

void IShape::moveEvent(QMoveEvent *event)
{
    //qDebug()<<"oldPos:"<<event->oldPos()<<"newPos"<<event->pos();

    m_start = event->pos();
    m_center = {event->pos().x() + m_bound_rect.width()/2,event->pos().y() + m_bound_rect.height()/2};
    update();
}

void IShape::set_id(int id)
{
    m_id = id;
}

void IShape::set_draw_params(const QPair<QPoint, QSize> &params)
{
    m_draw_params = params;
}


int IShape::id()
{
    return m_id;
}

QPair<QPoint, QSize> IShape::get_draw_params() const
{
    return m_draw_params;
}

