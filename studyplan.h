#ifndef STUDYPLAN_H
#define STUDYPLAN_H

#include <QString>
#include <QStringList>

class StudyPlan {

public:
    StudyPlan(
        int id, QString username, QString deadline, QString topic, int priority,
        QString content, QString create_time, QString update_time,
        QString reminder_time, QString finish_time, short status
    ) {
        this->id =id, this->username = username, this->deadline = deadline,
        this->topic = topic, this->priority = priority, this->content = content,
        this->create_time = create_time, this->update_time =update_time,
        this->reminder_time = reminder_time, this->finish_time = finish_time,
        this->status = status;
    }

    int getId() {return this->id;}
    QString getUsername() {return this->username;}
    QString getTopic() {return this->topic;}
    QString getContent() {return this->content;}
    QString getDeadLine() {return this->deadline;}
    QString getReminderTime() {return this->reminder_time;}
    QString getFinishTime() {return this->finish_time;}
    int getPriority() {return this->priority;}
    int getStatus() {return this->status;}

private:
    int id;
    QString username;
    QString deadline;
    QString topic;
    int priority;
    QString content;
    QString create_time;
    QString update_time;
    QString reminder_time;
    QString finish_time;
    int status;
};

#endif // STUDYPLAN_H
