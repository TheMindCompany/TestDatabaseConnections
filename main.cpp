#include <QtCore/QCoreApplication>
#include <QtSql/QtSql>
#include <Qt/qtableview.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString dbHost = "www.themindspot.com";
    QString dbName = "themind1_AMS";
    QString dbUser = "themind1_ams";
    QString dbPass = "nerdsrule";
    qint16  dbPort = 3306;
    qint16  numRows;
            //numRows2,
            //numRows3;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(dbHost);
    db.setPort(dbPort);
    db.setDatabaseName(dbName);
    db.setUserName(dbUser);
    db.setPassword(dbPass);

    if (db.open()){
        qDebug() << "Yeah!!!!";
    } else{
        qDebug() << db.lastError().text();
    }

    //Test One
    QSqlQuery dbQuery;
    dbQuery.exec("SELECT trackID, tName, tDesc FROM Tracker");
    if (db.driver()->hasFeature(QSqlDriver::QuerySize)) {
        numRows = dbQuery.size();
    } else {
        // this can be very slow
        dbQuery.last();
        numRows = dbQuery.at() + 1;
    }
    qDebug() << numRows;

    while (dbQuery.next()) {
        QString name = dbQuery.value(1).toString();
        QString descr = dbQuery.value(2).toString();
        qDebug() << name << descr;
    }


    //Test Two

    QSqlQueryModel  dbQuery2;
    dbQuery2.setQuery("SELECT * FROM Card");

    for (int i = 0; i < dbQuery2.rowCount(); ++i) {
        int cardID = dbQuery2.record(i).value("cardID").toInt();
        int trackID = dbQuery2.record(i).value("trackID").toInt();
        QString fName = dbQuery2.record(i).value("fName").toString();
        QString mName = dbQuery2.record(i).value("mName").toString();
        QString lName = dbQuery2.record(i).value("lName").toString();
        QString email = dbQuery2.record(i).value("email").toString();
        int isMember = dbQuery2.record(i).value("isMember").toInt();
        qDebug() << cardID << trackID << fName << mName << lName << email << isMember;
    }
/*
    QSqlQuery dbQuery2;
    dbQuery2.exec("SELECT cardID, trackID, fName, mName, lName, email FROM Card");

    if (db.driver()->hasFeature(QSqlDriver::QuerySize)) {
        numRows2 = dbQuery2.size();
    } else {
        // this can be very slow
        dbQuery2.last();
        numRows2 = dbQuery2.at() + 1;
    }

    qDebug() << numRows2;

    while (dbQuery2.next()) {
        QString fName = dbQuery2.value(2).toString();
        QString mName = dbQuery2.value(3).toString();
        QString lName = dbQuery2.value(4).toString();
        QString email = dbQuery2.value(5).toString();
        qDebug() << fName << mName << lName << "@" << email;
    }

*/
    //Test Three
    QSqlTableModel dbQuery3;
    dbQuery3.setTable("Survey");
    dbQuery3.setSort(2, Qt::DescendingOrder);
    dbQuery3.select();

    for (int i = 0; i < dbQuery3.rowCount(); ++i) {
        int name = dbQuery3.record(i).value("cardID").toInt();
        int salary = dbQuery3.record(i).value("trackID").toInt();
        qDebug() << name << salary;
    }
/*
    QSqlQuery dbQuery3;
    dbQuery3.exec("SELECT surveyID, cardID, trackID, q0, q1, q2, q3, q4, q5 FROM Survey");
    if (db.driver()->hasFeature(QSqlDriver::QuerySize)) {
        numRows3 = dbQuery3.size();
    } else {
        // this can be very slow
        dbQuery3.last();
        numRows3 = dbQuery3.at() + 1;
    }
    qDebug() << numRows3;
    while (dbQuery3.next()) {
        QString name = dbQuery3.value(1).toString();
        QString descr = dbQuery3.value(2).toString();
        qDebug() << name << descr;
    }
*/

    return a.exec();
}

 /*
BELOW ARE THE TABLES USED IN THIS PROGRAM

-- Host: localhost
-- Server version: 5.1.63
-- PHP Version: 5.2.17

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- Database: `themind1_AMS`
--

-- --------------------------------------------------------

--
-- Table structure for table `Card`
--

DROP TABLE IF EXISTS `Card`;
CREATE TABLE IF NOT EXISTS `Card` (
  `cardID` int(11) NOT NULL AUTO_INCREMENT,
  `trackID` int(11) NOT NULL,
  `fName` varchar(10) DEFAULT NULL,
  `mName` varchar(10) DEFAULT NULL,
  `lName` varchar(10) DEFAULT NULL,
  `email` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`cardID`),
  KEY `trackID` (`trackID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `Survey`
--

DROP TABLE IF EXISTS `Survey`;
CREATE TABLE IF NOT EXISTS `Survey` (
  `surveyID` int(11) NOT NULL,
  `cardID` int(11) NOT NULL,
  `trackID` int(11) NOT NULL,
  `q0` varchar(10) DEFAULT NULL,
  `q1` varchar(10) DEFAULT NULL,
  `q2` varchar(10) DEFAULT NULL,
  `q3` varchar(10) DEFAULT NULL,
  `q4` varchar(10) DEFAULT NULL,
  `q5` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`cardID`,`trackID`),
  KEY `cardID` (`cardID`),
  KEY `trackID` (`trackID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `Tracker`
--

DROP TABLE IF EXISTS `Tracker`;
CREATE TABLE IF NOT EXISTS `Tracker` (
  `trackID` int(11) NOT NULL AUTO_INCREMENT,
  `tName` varchar(10) DEFAULT NULL,
  `tDesc` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`trackID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

*/
