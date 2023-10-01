
#include "mainwindow.h"
#include <QGridLayout>
#include <QFileDialog>
#include <QApplication>
#include "settings.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize({640,480});
    m_central_widget = new QWidget(this);

    this->setCentralWidget(m_central_widget);
    m_button_frame = new QFrame(m_central_widget);
    m_canvas = new ShapeCanvas(ShapeCanvas::Mode::DrawTriangle,m_central_widget);

    m_button_frame->setFixedHeight(33);
    m_button_frame->setContentsMargins(0,0,0,0);
    m_button_frame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    m_main_window_layout = new QVBoxLayout(m_central_widget);
    m_central_widget->setLayout(m_main_window_layout);
    m_main_window_layout->addWidget(m_button_frame);
    m_main_window_layout->addWidget(m_canvas);
    m_canvas->show();

    m_triangle_button = new QPushButton(QIcon(":/triangle.svg"),{},m_button_frame);
    m_triangle_button->setIconSize({24,24});
    m_triangle_button->setCheckable(true);
    m_triangle_button->setChecked(true);

    m_rectangle_button = new QPushButton(QIcon(":/rectangle.svg"),{},m_button_frame);
    m_rectangle_button->setIconSize({24,24});
    m_rectangle_button->setCheckable(true);

    m_ellipse_button = new QPushButton(QIcon(":/circle.svg"),{},m_button_frame);
    m_ellipse_button->setIconSize({24,24});
    m_ellipse_button->setCheckable(true);

    m_connect_button = new QPushButton(QIcon(":/line.svg"),{},m_button_frame);
    m_connect_button->setIconSize({27,27});
    m_connect_button->setCheckable(true);

    m_move_button = new QPushButton(QIcon(":/move.svg"),{},m_button_frame);
    m_move_button->setIconSize({22,22});
    m_move_button->setCheckable(true);

    m_delete_button = new QPushButton(QIcon(":/delete.svg"),{},m_button_frame);
    m_delete_button->setIconSize({24,24});
    m_delete_button->setCheckable(true);

    m_save_button = new QPushButton(QIcon(":/save.svg"),{},m_button_frame);
    m_save_button->setIconSize({24,24});

    m_load_button = new QPushButton(QIcon(":/load.svg"),{},m_button_frame);
    m_load_button->setIconSize({24,24});

    m_button_group = new QButtonGroup(m_button_frame);
    m_button_group->addButton(m_triangle_button);
    m_button_group->addButton(m_rectangle_button);
    m_button_group->addButton(m_ellipse_button);
    m_button_group->addButton(m_connect_button);
    m_button_group->addButton(m_move_button);
    m_button_group->addButton(m_delete_button);


    m_button_layout = new QHBoxLayout(m_button_frame);
    m_button_layout->setContentsMargins(4,2,2,2);
    m_button_layout->setSpacing(3);
    m_button_layout->addWidget(m_triangle_button,0,Qt::AlignLeft);
    m_button_layout->addWidget(m_rectangle_button,0,Qt::AlignLeft);
    m_button_layout->addWidget(m_ellipse_button,0,Qt::AlignLeft);
    m_button_layout->addWidget(m_connect_button,0,Qt::AlignLeft);
    m_button_layout->addWidget(m_move_button,0,Qt::AlignLeft);
    m_button_layout->addWidget(m_delete_button,0,Qt::AlignLeft);
    m_button_layout->addWidget(m_save_button,0,Qt::AlignLeft);
    m_button_layout->addWidget(m_load_button,0,Qt::AlignLeft);
    m_button_layout->addStretch();
    m_button_frame->setLayout(m_button_layout);
    connect(m_button_group,&QButtonGroup::buttonClicked,this,[this](QAbstractButton *button){
        if(button == m_triangle_button)
            m_canvas->set_mode(ShapeCanvas::Mode::DrawTriangle);
        else if(button == m_rectangle_button)
            m_canvas->set_mode(ShapeCanvas::Mode::DrawRectangle);
        else if(button == m_ellipse_button)
            m_canvas->set_mode(ShapeCanvas::Mode::DrawEllipse);
        else if(button == m_connect_button)
            m_canvas->set_mode(ShapeCanvas::Mode::Connect);
        else if(button == m_delete_button)
            m_canvas->set_mode(ShapeCanvas::Mode::Delete);
        else if(button == m_move_button)
            m_canvas->set_mode(ShapeCanvas::Mode::Move);
    });
    connect(m_save_button,&QPushButton::clicked,this,[this](bool checked){
        QString file_name = QFileDialog::getSaveFileName(this,QStringLiteral("Save File"), qApp->applicationDirPath(),QStringLiteral("*.ini"));
        if(file_name.isNull())
            return;
        if(!file_name.endsWith(QStringLiteral(".ini")))
            file_name.append(QStringLiteral(".ini"));
        Settings::get_instance()->set_settings_file(file_name);
        Settings::get_instance()->save_shapes(m_canvas->get_shapes());
        Settings::get_instance()->save_connections(m_canvas->get_connections());

    });
    connect(m_load_button,&QPushButton::clicked,this,[this](bool checked){
        QString file_name = QFileDialog::getOpenFileName(this,QStringLiteral("Open File"), qApp->applicationDirPath(),QStringLiteral("*.ini"));
        if(file_name.isNull())
            return;
        Settings::get_instance()->set_settings_file(file_name);
        m_canvas->load_shapes(Settings::get_instance()->get_shapes(),Settings::get_instance()->get_connections());
    });
    this->show();
    this->update();

}

MainWindow::~MainWindow()
{
    //    delete ui;
}

void MainWindow::rectangle_toggled()
{

}



