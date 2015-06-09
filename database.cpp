#include "database.h"

#include <QString>
#include <QVariant>
#include <QMessageBox>

/*methods:
1. Choose question id
2. Get question text by id
3. Add (another) answer
4. Add seance to seance log*/

database *db = new database ();

database::database ()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("mydb");
}

int database::connect ()
{
    db.setUserName ("root");
    db.setHostName ("localhost");
    db.setPassword ("toor");
    if (!db.open ())
        QMessageBox::critical (0, "error", db.lastError().text(),QMessageBox::Cancel);
    query = new QSqlQuery (db);
    return 0;
}

int database::add_knowledge(QString table, QString text)
{
    query->prepare (QString("INSERT INTO %1s (%1_id, text) VALUES (':text');").arg(table));
    // enough for '); ?
    query->bindValue (":text", text);
    return query->exec();
}

QString database::get_question()
{
    query->exec("CALL choose(@q,@t);");
    query->exec("SELECT @q;");
    question_id = query->value(0);
    query->exec("SELECT @t;");
    return query->value(0);
}

int database::add_answer(int answer)
{
    if (seance_id == 0)
    {
        // does "count" field automatically become "1"?
        query->exec("INSERT INTO seances (seances_id,solution,count) VALUES (NULL);");
        query->exec("SELECT MAX(seance_id) FROM seances;");
        seance_id = query->value(0);
    }
    query->exec(QString("INSERT INTO seance_log (seance_id,question_id,answer)\
                        VALUES (%1,%2,%3);").arg(seance_id,question_id,answer));
}

int database::process_seance(int solution_id)
{
    if (solution_id)
    {
        query->exec(QString("UPDATE seances SET solution_id = %1\
                            WHERE seance_id = %2").arg(solution_id,seance_id));
    }
    else
    {
        query->exec(QString("DELETE FROM seance_log WHERE seance_id = %1;").arg(seance_id));
        query->exec(QString("DELETE FROM seances WHERE seance_id = %1;").arg(seance_id));
    }
}



