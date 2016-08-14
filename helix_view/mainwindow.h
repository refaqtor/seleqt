#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QGraphicsScene>

#include "helix.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void importJSONFile(QString filename);

private slots:
    void on_actionSave_triggered();
    void on_actionImport_triggered();


    void submitEditQuery();
    void on_tableQuery_editingFinished();
    void setTableViewColumnWidths();

    void updateViewSelector();
    void resetTableQuery();



    void on_jsonFilenameEdit_editingFinished();

    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_actionQuit_triggered();


    void on_tableViewSelect_currentIndexChanged(const QString &arg1);

    void on_graphDrawButton_clicked();

    void on_jsonFilenameEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *Scene;


    Helix *Project;
    QSortFilterProxyModel *ProjectProxyModel;
};

#endif // MAINWINDOW_H
