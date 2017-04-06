#ifndef SCORE_H
#define SCORE_H

#include <QFile>
#include <QTextStream>
#include <vector>
#include <QSettings>
#include <algorithm>

class ScoreStorage
{
public:
    enum Difficulty {EASY = 0, MEDIUM, HARD, INSANE};
    class Score{
        QString name;
        int minutes, seconds;
        bool helped;
    public:
        Score(QString name, int minutes, int seconds, bool helped);
        QString getName();
        QString getTime();
        int getMinutes() const;
        int getSeconds() const;
        bool wasHelped();
    };

   static void saveScore(Score score, Difficulty difficulty);
   ScoreStorage();
   std::vector<Score> getScores(Difficulty difficulty, bool withHelp);
private:
   std::vector<Score> scores[8];
   static const QString valueName[];
   static const QString modeName[];
};

bool operator<(const ScoreStorage::Score & a, const ScoreStorage::Score & b);

#endif // SCORE_H
