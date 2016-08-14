#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QSqlQuery>
#include <QtConcurrent/QtConcurrent>
#include <QtConcurrent/QtConcurrentRun>
#include <QThreadPool>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    Scene(new QGraphicsScene),
    Project(new Helix),
    ProjectProxyModel(new QSortFilterProxyModel)
{
    ui->setupUi(this);


    ProjectProxyModel->setSourceModel(Project->getProjectModel());
    ui->tableView->setModel(ProjectProxyModel);

    //    ui->jsonFilenameEdit->setText("/home/refaqtor/CODE/WORK/helix/citylots-small.json"); // JUST FOR TESTING
    //    ui->jsonFilenameEdit->setText("/home/r2d2/Downloads/node-v0.10.28/deps/npm/node_modules/read-package-json/node_modules/normalize-package-data/test/fixtures/http-server.json"); // JUST FOR TESTING

    ui->jsonFilenameEdit->setFocus();
    //    Project->setQuery("SELECT * FROM helix");
    //    setTableViewColumnWidths();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSave_triggered()
{
    Project->saveToDisk(QFileDialog::getSaveFileName(this, tr("Save File"),
                                                     QDir::homePath(),
                                                     tr("Helix (*.helix)")));
}

void MainWindow::on_actionImport_triggered()
{
    importJSONFile(QFileDialog::getOpenFileName(this,
                                                tr("Import JSON"),
                                                QDir::homePath(),
                                                tr("JSON data (*.idfx *.json)")));
}


void MainWindow::submitEditQuery()
{
    QString query_txt(ui->tableQuery->text());
    Project->setModelQuery(query_txt);
    setTableViewColumnWidths();
    qDebug() << query_txt;
}

void MainWindow::on_tableQuery_editingFinished()
{
    submitEditQuery();
}

void MainWindow::importJSONFile(QString filename)
{
    QFile file(filename);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        Project->importJSON(QString(file.readAll()), file.fileName());
        ui->jsonFileList->addItem(filename);
        updateViewSelector();
        resetTableQuery();
    }
}

void MainWindow::on_jsonFilenameEdit_editingFinished()
{
    QStringList files(QString(ui->jsonFilenameEdit->text()).split("file://"));
    foreach (QString file, files) {
        importJSONFile(file.trimmed());
    }



    //    QtConcurrent::map(filenames, importJSONFile);
    ui->jsonFilenameEdit->clear();
}

void MainWindow::setTableViewColumnWidths()
{
    //    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);
    ui->tableView->resizeColumnToContents(4);
    ui->tableView->setColumnWidth(3,350);
}

void MainWindow::updateViewSelector()
{
    ui->tableViewSelect->clear();
    ui->tableViewSelect->insertItem(
                ui->tableViewSelect->count(),
                "SELECT * FROM helix WHERE property NOT LIKE \"~%\";");
    foreach (QString view_name, Project->getViewOptions()) {
        if (!view_name.isEmpty()) {
            QString new_view =
                    QString("SELECT * FROM '%1_view'")
                    .arg(view_name);
            ui->tableViewSelect->insertItem(
                        ui->tableViewSelect->count(),
                        new_view);
        }
    }
    resetTableQuery();
}

void MainWindow::on_pushButton_clicked()
{
    importJSONFile(":/resources/idd8-2-0.json");
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString item_name = ProjectProxyModel->data(index).toString();
    QString column_name = ProjectProxyModel->headerData(index.column(),
                                                        Qt::Horizontal)
            .toString();
    ui->tableQuery->setText(QString("SELECT * FROM helix "
                                    "WHERE %1 like '%2'; ")
                            .arg(column_name)
                            .arg(item_name));
    ui->tableQuery->setFocus();
}

void MainWindow::resetTableQuery()
{
    ui->tableQuery->setText("SELECT * FROM helix WHERE property NOT LIKE \"~%\";");
    submitEditQuery();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}


void MainWindow::on_tableViewSelect_currentIndexChanged(const QString &selection)
{
    ui->tableQuery->setText(selection);
    submitEditQuery();
}


void MainWindow::on_graphDrawButton_clicked()
{
    quint32 loop_count = 0;

    int red = 50;
    int green = 100;
    int blue = 20;
    int alpha = 255;
    QList<Helix::Node> all_nodes = Project->getAllNodes();
    QPen pen(QColor(red,green,blue,alpha));
    foreach (Helix::Node node, all_nodes) {
        loop_count++;
        QRectF rect(QPoint(loop_count *50, loop_count * 50),QSize(550,50));
        QGraphicsRectItem *rectem = new QGraphicsRectItem(rect);
qDebug() <<node.getHelixId();
      //buggered  QGraphicsTextItem textem(node.getHelixId(), rectem);

        Scene->addItem(rectem);
    }
}

void MainWindow::on_jsonFilenameEdit_textChanged(const QString &arg1)
{
    on_jsonFilenameEdit_editingFinished();
}
