
#include "shapecanvas.h"
#include "shapes/Shapes.h"
#include <QPainter>
#include <cmath>
#include <algorithm>
ShapeCanvas::ShapeCanvas(Mode active_mode, QWidget *parent)
    : QFrame{parent}, m_mode{active_mode}, m_connection_manager{this}
{
    this->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    this->setStyleSheet(".ShapeCanvas { background-color:white; }");
}
//need not to create the object if mouse is pressed but haven't moved
void ShapeCanvas::mousePressEvent(QMouseEvent *event)
{
    setFocus();
    if(event->buttons() & Qt::RightButton )
    {
        if(this->in_draw_mode())
            this->cancel_drawing();
        else if(m_mode == Mode::Connect && m_connection_manager.in_selection_mode())
            m_connection_manager.cancel_selection();
        else if(m_mode == Mode::Move && (event->buttons() & Qt::LeftButton))
            this->cancel_move();
    }
    else if(event->buttons() & Qt::LeftButton )
    {
        switch(m_mode)
        {
        case Mode::DrawRectangle:
            m_draw_start = event->pos();
            m_active_shape = new SRectangle(-1,this);
            this->setMouseTracking(true);
            break;
        case Mode::DrawEllipse:
            m_draw_start = event->pos();
            m_active_shape = new SEllipse(-1,this);
            this->setMouseTracking(true);
            break;
        case Mode::DrawTriangle:
            m_draw_start = event->pos();
            m_active_shape = new STriangle(-1,this);
            this->setMouseTracking(true);
            break;
        case Mode::Connect:
            this->handle_connect_press_event(event->pos());
            break;
        case Mode::Move:
            m_active_shape = this->select_shape(event->pos());
            if(m_active_shape)
            {
                this->setMouseTracking(true);
                m_mouse_old_pos = event->pos();
                QWidget::setCursor(QCursor(Qt::OpenHandCursor));
            }
            break;
        case Mode::Delete:
            m_active_shape = this->select_shape(event->pos());
            if(m_active_shape)
            {
                remove_shape(m_active_shape);
            }

            break;
        }
    }
}

void ShapeCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && this->in_draw_mode() && m_draw_start != event->pos())
    {
        if(m_active_shape)
        {
            QSize shape_size = {event->pos().x() - m_draw_start.x() , event->pos().y() - m_draw_start.y()};
            m_active_shape->draw(m_draw_start,shape_size);
            if(m_active_shape->isHidden())
                m_active_shape->show();
        }
    }
    else if(m_mode == Mode::Connect|| m_mode == Mode::Delete)
    {
        if(m_connection_manager.in_selection_mode())
            m_connection_manager.update_selection_line(event->pos());
    }
    else if(m_mode == Mode::Move && (event->buttons() & Qt::LeftButton))
    {
        if(m_active_shape)
        {
            QPoint delta_pos = event->pos() - m_mouse_old_pos;
            m_mouse_old_pos = event->pos();
            m_active_shape->move(m_active_shape->pos() + delta_pos);
            m_connection_manager.update_shape(m_active_shape);
        }
    }
}

void ShapeCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    m_draw_start = {0,0};
    if(this->in_draw_mode())
    {
        if(m_draw_start == event->pos())
        {
            this->cancel_drawing();
            return;
        }
        this->setMouseTracking(false);
        m_shapes.push_back(m_active_shape);
        m_active_shape = nullptr;
    }
    else if(m_mode == Mode::Move)
    {
        this->cancel_move();
    }
}

void ShapeCanvas::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        if(this->in_draw_mode())
        {
            this->cancel_drawing();
        }
        else if(m_mode == Mode::Connect && m_connection_manager.in_selection_mode())
        {

            m_connection_manager.cancel_selection();
        }
        else if(m_mode == Mode::Move)
        {
            this->cancel_move();
        }
        this->setMouseTracking(false);
    }

}

void ShapeCanvas::load_shapes(QList<IShape *> shapes, QList<QPair<int,int>> connections)
{
    this->delete_all_shapes();
    QPair<QPoint,QSize> draw_params;
    //draw shapes frist
    for(auto it : shapes)
    {
        it->setParent(this);
        draw_params = it->get_draw_params();
        it->draw(draw_params.first,draw_params.second);
        it->show();
    }
    m_shapes = shapes;
    m_connection_manager.clear_connections();
    //then add connections back to them
    for(auto conn : connections)
    {
        auto first = std::find_if(m_shapes.begin(),m_shapes.end(),[this,&conn](IShape* a){return a->id() == conn.first;});
        if(first == m_shapes.end())
            continue;

        auto second = std::find_if(m_shapes.begin(),m_shapes.end(),[this,&conn](IShape* a){return a->id() == conn.second;});
        if(second == m_shapes.end())
            continue;

        m_connection_manager.connect(*first,*second);
    }
}

void ShapeCanvas::delete_all_shapes()
{
    for(auto it : m_shapes)
    {
        it->hide();
        it->deleteLater();
    }
    m_shapes.clear();
}

void ShapeCanvas::set_mode(Mode mode)
{
    m_mode = mode;
}

QList<ConnectionManager::Connection> ShapeCanvas::get_connections()
{
    return m_connection_manager.get_connections();
}

QList<IShape *> ShapeCanvas::get_shapes()
{
    return m_shapes;
}

bool ShapeCanvas::in_draw_mode() const
{
    switch (m_mode) {
    case Mode::DrawEllipse:
    case Mode::DrawRectangle:
    case Mode::DrawTriangle:
        return true;
    default:
        return false;
    }
}

void ShapeCanvas::handle_connect_press_event(const QPoint& mouse_pos)
{
    if(m_connection_manager.in_selection_mode())
    {
        IShape* selected_shape = this->select_shape(mouse_pos);
        if(!selected_shape || selected_shape == m_active_shape)
        {
            m_connection_manager.cancel_selection();
        }
        else
            m_connection_manager.connect(selected_shape);
    }
    else
    {
        m_active_shape = select_shape(mouse_pos);
        if(m_active_shape)
        {
            this->setMouseTracking(true);
            m_connection_manager.start_connection(m_active_shape);
        }
    }
}
//select the shape which center is closest to the cursor
IShape *ShapeCanvas::select_shape(const QPoint &point)
{
    int min{INT_MAX};
    IShape* result = nullptr;
    //can be optimzed to select overlaping shape aside from already connected in Connect mode
    for(const auto shape : m_shapes)
    {
        if(shape->contains_shape(point))
        {
            int distance = std::pow(point.x() - shape->center().x(),2) + std::pow(point.y() - shape->center().y(),2);
            if(distance < min)
            {
                result = shape;
                min = distance;
            }
        }
    }
    return result;
}

void ShapeCanvas::cancel_drawing()
{
    if(!m_active_shape)
        return;
    m_active_shape->hide();
    m_active_shape->deleteLater();
    m_active_shape = nullptr;
}

void ShapeCanvas::cancel_move()
{
    this->setMouseTracking(false);
    m_active_shape = nullptr;
    QWidget::setCursor(QCursor(Qt::ArrowCursor));

}

void ShapeCanvas::remove_shape(IShape *shape)
{
    auto found = std::find_if(m_shapes.begin(),m_shapes.end(),[shape](IShape* a){return a == shape;});
    m_active_shape = nullptr;
    if(found != m_shapes.end())
    {
        IShape* sh = *found;
        m_connection_manager.disconnect_all(sh);
        sh->hide();
        sh->deleteLater();
        *found = nullptr;
        m_shapes.erase({found});
    }
}


