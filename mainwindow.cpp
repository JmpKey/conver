#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_add_triggered()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(tr("Video (*.mp4 *.avi *.mov *.mkv);;All (*)"));

    if (dialog.exec()) {
        QStringList selectedFiles = dialog.selectedFiles();

        for (const QString &file : selectedFiles) {
            ui->lw_pointer->addItem(file);
        }
    }

    save_catalog = QFileDialog::getExistingDirectory(nullptr, "Save catalog", QDir::homePath());
    if (!save_catalog.isEmpty()) {}
}

void MainWindow::on_action_del_triggered()
{
    ui->lw_pointer->clear();
}

void MainWindow::on_action_del_list_triggered()
{
    QList<QListWidgetItem*> selectedItems = ui->lw_pointer->selectedItems();

    for (QListWidgetItem* item : selectedItems)
    {
        QListWidgetItem* removedItem = ui->lw_pointer->takeItem(ui->lw_pointer->row(item));
        if (removedItem) {
            delete removedItem;
        }
    }
}

void MainWindow::on_action_op_pattern_triggered()
{
    fo_conf = QFileDialog::getOpenFileName(this, tr("Open pattern"), QDir::homePath(), tr("Config (*.conf *.config *.txt);;All (*)")).toStdString();
    //if (!fo_conf.isEmpty()) {}
}

void MainWindow::on_action_save_pattern_triggered()
{
    std::string fc_save = QFileDialog::getSaveFileName(this, tr("Save pattern"), QDir::homePath(), tr("Config (*.conf *.config *.txt);;All (*)")).toStdString();
    fmenager savef;
    savef.createConfigFile(fc_save, "bV", ui->cb_quality_v->currentText().toStdString());
    savef.createConfigFile(fc_save, "bA", ui->cb_quality_a->currentText().toStdString());
}

void MainWindow::on_action_convert_triggered()
{
    fmenager ffmpegf;
    QString ffmpegPath = ffmpegf.readPathFile();

    for(int i = 0; i < ui->lw_pointer->count(); i++) {
        QListWidgetItem *itemf = ui->lw_pointer->item(i);

        // creating an FFmpeg Converter object and passing the path to ffmpeg
        collector converter(ffmpegPath);

        // path to the original video file
        QString inputFile = itemf->text();

        // path to save the converted video file
        QFileInfo fileInfo(itemf->text());
        QString stExpansion = "." + ui->cb_format->currentText();
        QString adds = fileInfo.baseName() + stExpansion;
        QString outputFile = save_catalog + "/" + adds;

        // input file
        converter.setInputFile(inputFile);

        // output file
        converter.setOutputFile(outputFile);

        // setting the quality
        if(fo_conf != "") {
            fmenager conf_pars;
            std::vector<int> conf_data = conf_pars.parseConfigFile(fo_conf);
            converter.setQuality(conf_data[1], conf_data[0]);
        }
        else
        {
            converter.setQuality(ui->cb_quality_v->currentText().toInt(), ui->cb_quality_a->currentText().toInt());
        }

        // launching the conversion
        converter.startConversion();
    }
}


void MainWindow::on_action_stop_triggered()
{
    fmenager ffmpegf;
    collector task_stop(ffmpegf.readPathFile());
    task_stop.stopConversion();
}

