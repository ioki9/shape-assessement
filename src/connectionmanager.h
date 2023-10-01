#pragma once
#include <QObject>
#include "shapes/Shapes.h"


class ConnectionManager : public QObject
{

    Q_OBJECT
public:
    struct Connection{
        QPair<IShape*,IShape*> connection;
        SLine* line;
    };

    explicit ConnectionManager(QObject *parent = nullptr);
    ~ConnectionManager();
    void start_connection(IShape* shape_to_start);
    void connect(IShape* connect_to);
    void connect(IShape* a, IShape* b);
    bool disconnect(IShape* a,IShape* b);
    void disconnect_all(IShape* from_shape);
    void cancel_selection();
    void clear_connections();
    void load_connections(QList<Connection>& connections);
    [[nodiscard]] bool contains_connection(IShape* a, IShape* b) const;
    [[nodiscard]] bool in_selection_mode() const;
    [[nodiscard]] QList<Connection> get_connections();
    void update_all();
    void update_selection_line(const QPoint& pos);
    void update_shape(IShape* shape);
private:
    QList<Connection> m_connections;
    IShape* m_selected_shape;
    SLine* m_line;
    bool m_selection_mode{false};
};

