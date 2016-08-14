#include <QString>
#include <QtTest>
#include <QTimer>

#include "../helix/helix.h"

#define LOOPCOUNT 10000

const QString TEST_OBJECTS("{\"Construction\":{\"Label\":{\"data_type\":\"alpha\",\"idd_position\":1,\"idd_specifier\":\"A1\",\"reference\":\"ConstructionNames\",\"required_field\":true},\"extension_type\":\"Construction_x\",\"group\":\"Surface Construction Elements\",\"memo\":\"Start with outside layer and work your way to the inside layer Up to 10 layers total 8 for windows Enter the material name for each layer. The first layer is the outside layer.\",\"reference\":\"ConstructionNames\"},\"Construction_x\":{\"Layer\":{\"data_type\":\"object_list\",\"idd_position\":2,\"idd_specifier\":\"A2\",\"note\":\"Outside Layer must be the first Layer\",\"object_list\":\"MaterialName\",\"required_field\":true},\"extension\":\"True\",\"memo\":\"New object containing the extensible fields of the original object\"}}");



class Helix_Test : public QObject
{
    Q_OBJECT

public:
    Helix_Test();

    void saveToDisk(QString id);
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    //JSON handling tests
    void insertJsonObject();
    void insertJsonIDD();

    //SQL table insert tests
//    void insertRecord();
//    void insertRecords();
//    void insertRecordsDefaultUUID();
//    void selectSpeed();


private:
    Helix *helix;
};

Helix_Test::Helix_Test()
    //:    helix(new Helix)
{
}

void Helix_Test::initTestCase()
{
    helix = new Helix;
}

void Helix_Test::cleanupTestCase()
{
    delete helix;
}

void Helix_Test::saveToDisk(QString id)
{
    helix->saveToDisk(QDir::homePath() + "/SCRATCH/helix_" + id + "_" + QTime::currentTime().toString().remove(":") + ".sqlt");
}

void Helix_Test::insertJsonObject()
{
    helix->importJSON(TEST_OBJECTS, "test");
  // saveToDisk("insertJsonObject");

}

void Helix_Test::insertJsonIDD()
{
    QElapsedTimer timer;
    timer.start();
    QFile file(":/resources/idd8-2-0.json");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        helix->importJSON(QString(file.readAll()), file.fileName());
    }
    qreal duration = timer.elapsed();
    qDebug() << " insertJSON elapsed : " << duration;
    qDebug() << " insertJSON limit : " << (8000);
    QVERIFY(duration < (8000));

    timer.restart();
    saveToDisk("insertJsonIDD");
    duration = timer.elapsed();
    qDebug() << " saveToDisk elapsed : " << duration;
    qDebug() << " saveToDisk limit : " << (2000);
    QVERIFY(duration < (2000));
}

//void Helix_Test::insertRecord()
//{
//    QElapsedTimer timer;
//    timer.start();
//    for (quint64 var = 0; var < LOOPCOUNT; ++var) {
//        helix->insertRecord("some link", 1, "8f12a98e-3577-9e5c-4584-822f4b79104d2166", QString::number(var));
//    }
//    qreal duration = timer.elapsed();
//    qDebug() << " insertRecords elapsed : " << duration;
//    qDebug() << " insertRecord limit : " << (LOOPCOUNT/40);
//    QVERIFY(duration < (LOOPCOUNT/40));
//}

//void Helix_Test::insertRecords()
//{
//    QElapsedTimer timer;
//    timer.start();
//    helix->beginTransaction();
//    for (quint64 var = 0; var < LOOPCOUNT; ++var) {
//        helix->insertRecord("some link", 1, "8f12a98e-3577-9e5c-4584-822f4b79104d2167", QString::number(var));
//    }
//    helix->endTransaction();
//    qreal duration = timer.elapsed();
//    qDebug() << " insertRecords elapsed : " << duration;
//    qDebug() << " insertRecords limit : " << (LOOPCOUNT/50);
//    QVERIFY(duration < (LOOPCOUNT/50));
//}

//void Helix_Test::insertRecordsDefaultUUID()
//{
//    QElapsedTimer timer;
//    timer.start();
//    helix->beginTransaction();
//    for (quint64 var = 0; var < LOOPCOUNT; ++var) {
//        helix->insertRecord("some link", 1, "8f12a98e-3577-9e5c-4584-822f4b79104d2167");
//    }
//    helix->endTransaction();
//    qreal duration = timer.elapsed();
//    qDebug() << " insertRecordsDefaultUUID elapsed : " << duration;
//    qDebug() << " insertRecordsDefaultUUID limit : " << (LOOPCOUNT/50);
//    QVERIFY(duration < (LOOPCOUNT/50));
//}

//void Helix_Test::selectSpeed()
//{
//    QElapsedTimer timer;
//    helix->beginTransaction();
//    timer.start();
//    helix->fullSpeedTest();
//    qreal duration = timer.elapsed();
//    helix->endTransaction();
//    qDebug() << " full select test elapsed : " << duration;
//}



QTEST_APPLESS_MAIN(Helix_Test)

#include "tst_helix_test.moc"
