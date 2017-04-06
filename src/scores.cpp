#include "include/scores.h"

const QString ScoreStorage::valueName[] = {"names", "minutes", "seconds"};
const QString ScoreStorage::modeName[] = {"normal", "helped"};

ScoreStorage::Score::Score(QString name, int minutes, int seconds, bool helped) : name(name), minutes(minutes), seconds(seconds), helped(helped)
{

}

QString ScoreStorage::Score::getName()
{
    return name;
}

QString ScoreStorage::Score::getTime()
{
    QString str = QString::number(minutes) + ":";
    if(seconds < 10){
        str += "0";
    }
    return str + QString::number(seconds);
}

int ScoreStorage::Score::getMinutes() const
{
    return minutes;
}

int ScoreStorage::Score::getSeconds() const
{
    return seconds;
}

bool ScoreStorage::Score::wasHelped()
{
    return helped;
}

ScoreStorage::ScoreStorage()
{
    QSettings settings;
    for(int i=0;i<8;i++){
        QList<QVariant> lists[3];
        for(int j=0;j<3;j++){
            lists[j] = settings.value("score/"+QString::number(i/2)+"/"+modeName[i%2]+"/"+valueName[j], QList<QVariant>()).toList();
        }
        for(int j=0;j<lists[0].size();j++){
            scores[i].push_back(Score(lists[0][j].toString(), lists[1][j].toInt(), lists[2][j].toInt(), i%2));
        }
    }
}

std::vector<ScoreStorage::Score> ScoreStorage::getScores(Difficulty difficulty, bool withHelp)
{
    std::vector<ScoreStorage::Score> v = scores[difficulty*2+withHelp];
    std::sort(v.begin(), v.end());
    return v;
}

void ScoreStorage::saveScore(Score score, Difficulty difficulty)
{
    QSettings settings;
    QString key = "score/"+QString::number(difficulty)+"/"+modeName[score.wasHelped()]+"/";
    QVariant values[] = {score.getName(), score.getMinutes(), score.getSeconds() };
    for(int i=0;i<3;i++){
       QList<QVariant> list =  settings.value(key+valueName[i], QList<QVariant>()).toList();
       list.push_back(values[i]);
       settings.setValue(key+valueName[i], list);
    }
}

bool operator<(const ScoreStorage::Score & a, const ScoreStorage::Score & b){
    return a.getMinutes()*60+a.getSeconds() < b.getMinutes()*60+b.getSeconds();
}
