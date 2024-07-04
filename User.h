#ifndef USER_H
#define USER_H

#define ROOT "http://127.0.0.1:8080/"

#include "studyplan.h"

#include <QString>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class User {

public:
    User() {}
    User(QString username, QString token)
    {
        this->username = username;
        this->token = token;
    }

public:
    void setStudyPlans(QList<StudyPlan> *studyPlans) {this->studyPlans = *studyPlans;}
    void addStudyPlan(StudyPlan studyPlan) {this->studyPlans.append(studyPlan);}
    QString getUsername() {return this->username;}
    QString getToken() {return this->token;}
    QList<StudyPlan> getStudyPlans() {return this->studyPlans;}

private:
    QString username;
    QString token;
    QList<StudyPlan> studyPlans;
};

#endif // USER_H
