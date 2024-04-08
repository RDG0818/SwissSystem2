#include "person.h"

Person::Person() {
    this->name = "";
    this->USCFID = "";
    this->rating = 0;
    this->score = 0;
}

Person::Person(string name, int rating) {
    this->name = name;
    this->rating = rating;
    this->score = 0;
}

void Person::setScore(double score) {
    this->score = score;
}

double Person::getScore() {
    return score;
}


void Person::setRating(int rating) {
    this->rating = rating;
}

int Person::getRating() {
    return rating;
}


void Person::setName(string name) {
    this->name = name;
}

string Person::getName() {
    return name;
}


void Person::setUSCFID(string USCFID) {
    this->USCFID = USCFID;
}

string Person::getUSCFID() {
    return USCFID;
}

