#pragma once

#include <QMainWindow>
#include "shapecanvas.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QButtonGroup>


class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void rectangle_toggled();
private:
    QWidget* m_central_widget = nullptr;
    ShapeCanvas* m_canvas = nullptr;
    QFrame* m_button_frame = nullptr;
    QButtonGroup* m_button_group = nullptr;
    QHBoxLayout* m_button_layout = nullptr;
    QVBoxLayout* m_main_window_layout = nullptr;
    QPushButton* m_rectangle_button = nullptr;
    QPushButton* m_triangle_button = nullptr;
    QPushButton* m_ellipse_button = nullptr;
    QPushButton* m_connect_button = nullptr;
    QPushButton* m_move_button = nullptr;
    QPushButton* m_delete_button = nullptr;
    QPushButton* m_load_button = nullptr;
    QPushButton* m_save_button = nullptr;

};


