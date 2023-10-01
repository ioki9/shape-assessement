#pragma once
#include <QFrame>
#include "shapes/Shapes.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include "connectionmanager.h"
class ShapeCanvas : public QFrame
{
    Q_OBJECT
public:
    enum class Mode{
        DrawRectangle,
        DrawEllipse,
        DrawTriangle,
        Move,
        Connect,
        Delete
    };
    explicit ShapeCanvas(Mode active_mode,QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void load_shapes(QList<IShape*> shapes,QList<QPair<int,int>> connections);
    void delete_all_shapes();
    void set_mode(Mode mode);
    [[nodiscard]] QList<ConnectionManager::Connection> get_connections();
    [[nodiscard]] QList<IShape*> get_shapes();
    [[nodiscard]] bool in_draw_mode() const;
private:
    void handle_connect_press_event(const QPoint& mouse_pos);
    IShape* select_shape(const QPoint& point);
    void cancel_drawing();
    void cancel_move();
    void remove_shape(IShape* shape);
    QList<IShape*> m_shapes{};
    Mode m_mode;
    //shape we are working on in different modes.
    IShape* m_active_shape = nullptr;
    QPoint m_draw_start;
    QPoint m_mouse_old_pos;
    ConnectionManager m_connection_manager;
signals:

};

