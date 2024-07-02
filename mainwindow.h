#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include "collector.h"
#include "fmenager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:    
    void on_action_op_pattern_triggered();
    void on_action_save_pattern_triggered();
    void on_action_del_triggered();
    void on_action_del_list_triggered();
    void on_action_add_triggered();
    void on_action_convert_triggered();
    void on_action_stop_triggered();

private:
    Ui::MainWindow* ui;
    QString save_catalog;
    std::string fo_conf;
};
#endif // MAINWINDOW_H
