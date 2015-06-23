#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QString>

class database
{
public:
    // base
    database();

    int connect ();

    // errors
    QString last_error () {return db.lastError().text();}
    QString last_query_error () {return query->lastError().text();}

    // insert methods
    int add_knowledge(QString table, QString text);
    void process_seance (int solution_id);
    int add_answer(int answer);

    // get methods
    QString get_question ();
    QString get_solution ();

    // other

private:
    QSqlDatabase db;
    QSqlQuery *query;
    QString error;
    int question_id;
    int seance_id;
};

extern database *db;


#endif // DATABASE_H
