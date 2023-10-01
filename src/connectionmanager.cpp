#include "connectionmanager.h"

ConnectionManager::ConnectionManager(QObject *parent)
    : QObject{parent}
{

}

ConnectionManager::~ConnectionManager()
{

}

void ConnectionManager::start_connection(IShape *shape_to_start)
{
    m_line = new SLine(-1,qobject_cast<QWidget*>(shape_to_start->parent()));
    m_selected_shape = shape_to_start;
    m_selection_mode = true;
}

void ConnectionManager::connect(IShape *connect_to)
{
    if(this->contains_connection(m_selected_shape,connect_to))
        this->cancel_selection();

    if(!this->in_selection_mode() || !m_selected_shape || !m_line)
        return;
    Connection new_connection{{m_selected_shape,connect_to},m_line};
    m_line->draw(m_selected_shape->center(),QPoint(connect_to->center().x() ,connect_to->center().y()));
    if(m_line->isHidden())
        m_line->show();
    m_connections.push_back(std::move(new_connection));
    m_line = nullptr;
    m_selected_shape = nullptr;
    m_selection_mode = false;
}

void ConnectionManager::connect(IShape *a, IShape *b)
{
    if(this->contains_connection(a,b))
        return;
    m_line = new SLine(-1,qobject_cast<QWidget*>(a->parent()));
    Connection new_connection{{a,b},m_line};
    m_connections.append(new_connection);
    this->update_all();
}

bool ConnectionManager::disconnect(IShape *a, IShape *b)
{
    auto result = std::find_if(m_connections.begin(),m_connections.end(),[this,a,b](Connection connection){
        return (connection.connection.first == a || connection.connection.first == b) && (connection.connection.second == a || connection.connection.second == b);
    });
    if(result == m_connections.end())
        return false;

    result->line->hide();
    result->line->deleteLater();
    result->line = nullptr;
    m_connections.erase({result});
    return true;
}

void ConnectionManager::disconnect_all(IShape *from_shape)
{
    auto iter = m_connections.begin();
    while(iter!=m_connections.end())
    {
        if(iter->connection.first == from_shape || iter->connection.second == from_shape)
        {
            iter->line->hide();
            iter->line->deleteLater();
            iter->line = nullptr;
            iter = m_connections.erase({iter});
            continue;
        }
        iter++;
    }
}

void ConnectionManager::cancel_selection()
{
    if(!m_selection_mode)
        return;
    if(m_line)
    {
        m_line->hide();
        m_line->deleteLater();
        m_line = nullptr;
    }
    m_selected_shape = nullptr;
    m_selection_mode = false;
}

void ConnectionManager::clear_connections()
{
    for(auto it: m_connections)
    {
        it.line->hide();
        it.line->deleteLater();
    }
    m_connections.clear();
}

void ConnectionManager::load_connections(QList<Connection> &connections)
{
    m_connections = connections;
    this->update_all();
}

bool ConnectionManager::contains_connection(IShape *a, IShape *b) const
{
    auto result = std::find_if(m_connections.constBegin(),m_connections.constEnd(),[a,b](Connection connection){
        return (connection.connection.first == a || connection.connection.first == b) && (connection.connection.second == a || connection.connection.second == b);
    });
    return result != m_connections.constEnd();
}

bool ConnectionManager::in_selection_mode() const
{
    return m_selection_mode;
}

QList<ConnectionManager::Connection> ConnectionManager::get_connections()
{
    return m_connections;
}

void ConnectionManager::update_all()
{
    for(auto& conn : m_connections)
    {
        conn.line->draw(conn.connection.first->center(),conn.connection.second->center());
        if(conn.line->isHidden())
            conn.line->show();
    }
}

void ConnectionManager::update_selection_line(const QPoint &pos)
{
    if(m_selection_mode)
    {
        QPoint shape_center = m_selected_shape->center();
        m_line->draw(shape_center,pos);
        if(m_line->isHidden())
            m_line->show();
    }
}

void ConnectionManager::update_shape(IShape *shape)
{
    for(auto& conn : m_connections)
    {
        if(conn.connection.first == shape || conn.connection.second == shape)
            conn.line->draw(conn.connection.first->center(),conn.connection.second->center());
    }
}
