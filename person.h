#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <vector>
using std::string;

class Person
{
public:
    Person();
    Person(string name, int rating);

    void setScore(double score);
    double getScore();


    void setRating(int rating);
    int getRating();


    void setName(string name);
    string getName();

    void updateMatchHistory(int currRound, string result, int matchNum, string color);
    void setMatchHistory(int rounds);
    void setCurHistory(std::vector<string> matches);

    std::vector<string> getMatchHistory();

private:
    int rating;
    string name;
    int score;
    std::vector<string> playablePeople;
    std::vector<string> matchHistory;
};

#endif // PERSON_H

