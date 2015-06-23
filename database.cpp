

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
    query->prepare("CALL choose(0,:q)");
    query->bindValue(":q",question_id);
    query->prepare("SELECT text FROM questions WHERE question_id = :q");
    query->bindValue(":q",question_id);
    query->exec();
    return query->value(0).toString();
}

QString database::get_solution()
{
    QVariant tmp;
    QString result = "nope";
    query->prepare("CALL choose(1,:p)");
    query->bindValue(":p",tmp);
    double priori = tmp.toDouble();
    if (priori > 0.9)
    {
        query->prepare("SELECT text FROM solutions WHERE solution_id = :p");
        query->bindValue(":p",priori);
        query->exec();
        result = query->value(0).toString();
    }
    return result;
}

int database::add_answer(int answer)
{
    if (seance_id == 0)
    {
        query->exec("INSERT INTO seances (solution) VALUES (NULL);");
        query->exec("SELECT MAX(seance_id) FROM seances;");
        seance_id = query->value(0).toInt();
    }
    return query->exec(QString("INSERT INTO seance_log (seance_id,question_id,answer)\
                        VALUES (%1,%2,%3);").arg(seance_id,question_id,answer));
}

void database::process_seance(int solution_id)
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




