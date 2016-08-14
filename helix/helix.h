#ifndef HELIX_H
#define HELIX_H

#include <QSqlDatabase>
#include <QSqlQueryModel>

#include "cJSON.h"

class Helix
{

public:
    Helix();
    ~Helix();

    void importJSON(QString json_string, QString root_id = "");
    void exportJSON(QString filename, QString root_id = "");
    void saveToDisk(QString filename);

    class Node
    {
    public:
        ~Node();

        QString getHelixId() {return Helix_Id;}
        Node getHelixRootId();
        QString getHelixParent() {return Helix_Parent;}
        QString getHelixNodeName() {return Helix_Node_Name;}
        quint32 getHelixItemOrder() {return Helix_Item_Order;}

        void setHelixParent(QString value) {Helix_Parent = value;}
        void setHelixNodeName(QString value) {Helix_Node_Name = value;}
        void setHelixItemOrder(quint32 value) {Helix_Item_Order = value;}

        QMap<QString, QString> getData();
        QList<Node> getChildren();

//these should probably be private
        Node(QString node_id, QSqlDatabase db,  QString table = "helix");
        void setHelixId(QString value){Helix_Id = value;}
    private:


        QString Helix_Id;
        QString Helix_Parent;
        QString Helix_Node_Name;
        quint32 Helix_Item_Order;

    };

    Node *createNode(QString node_id, QString table = "helix");
    Node getNode(QString node_id, QString table = "helix");
    QList<Node> getRootNodes(QString table = "helix");
    QList<Node> getAllNodes(QString table = "helix");

    void deleteNode();



    QSqlQueryModel *getProjectModel();
    void setModelQuery(QString qry);

    QSqlQuery queryResults(QString qry_str, QString err_str = "");

    QStringList getViewOptions();

private:
    QSqlDatabase DB;
    QSqlQueryModel *ProjectModel;

    bool initTable();

    void parse_object(cJSON *item, QString parent_id = "");
    bool queryCommand(QString qry_str, QString err_str = " ");

    bool insertRecord(QString property, qreal inclusion, QString datum, QString id  = "");

//    void beginTransaction();
//    void endTransaction();
//    void fullSpeedTest();

    QString getNewUUID();
};

#endif // HELIX_H
