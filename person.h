#ifndef PERSON_H
#define PERSON_H
#include <string>
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

    void setUSCFID(string USCFID);
    string getUSCFID();


private:
    int rating;
    string name;
    string USCFID;
    int score;

};

#endif // PERSON_H

