#include "person.h"
#include <iostream>

Person::Person() {
    this->name = "";
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

void Person::updateMatchHistory(int currRound, string result, int matchNum, string color) {

    string playerResult;
    currRound--;
    playerResult = result + " " + std::to_string(matchNum) + " " + color;
    if (result == "BYE") {
        this->matchHistory.at(currRound) = "BYE";
        this->score += 1;
    }
    else if (result == "W"){
        this->matchHistory.at(currRound) = playerResult;
        this->score +=1;
    }
    else if (result == "D") {
        this->matchHistory.at(currRound) = playerResult;
        this->score += 0.5;
    }
    else {
        this->matchHistory.at(currRound) = playerResult;
    }
}


void Person::setMatchHistory(int rounds) {
    for(int i = 0; i < rounds; i++) {
        this->matchHistory.push_back("DNE");
    }
}

void Person::setCurHistory(std::vector<string> matches) {
    this->matchHistory = matches;
}

std::vector<string> Person::getMatchHistory() {
    return matchHistory;
}

