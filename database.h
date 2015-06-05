#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QString>

class database
{
public:
    // base
    database();

    int connect (QString user_name, QString host_name, QString password);

    // errors
    QString last_error () {return db.lastError().text();}
    QString last_query_error () {return query->lastError().text();}

    // insert methods
    int add_solution (QString name, QString description, QString owner);
    int add_question (int survey_index, QString wording, int q_type, int page_num);

    // get methods
    QStringList get_survey_list (QString);

    // secutity
    char* hash_password (QString password);

    // other
    int login (QString name, QString password);

private:
    QSqlDatabase db;
    QSqlQuery *query;
    QString error;
};

extern data_base *db;


#endif // DATABASE_H
