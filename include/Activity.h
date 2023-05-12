#pragma once
#include <iostream>

class Activity {
 public:
  Activity(std::string title) : title_(title), time_elapsed_(0){};
  void updateTimeElapsed(double timeToAdd);
  double getTimeElapsedSeconds();
  std::string getTimeElapsedFormatted() const ;
  std::string getTitle();
  bool operator=(const Activity& other) const { return title_ == other.title_; }

  friend std::ostream& operator<<(std::ostream& os, const Activity& activity) {
    os << "-------------------\nTitle: " << activity.title_
       << "\nTime elapsed: " << activity.getTimeElapsedFormatted()
       << "\n-------------------" << std::endl;
    return os;
  }

 private:
  std::string title_;
  double time_elapsed_;
};

std::string Activity::getTitle() { return title_; }

double Activity::getTimeElapsedSeconds() { return time_elapsed_; }

std::string Activity::getTimeElapsedFormatted() const {
  int minutes = time_elapsed_ / 60;
  int hours = minutes / 60;
  int mins = minutes - (hours * 60);
  int secs = time_elapsed_ - (minutes * 60);
  std::string time = std::to_string(hours) + "h " + std::to_string(mins) + "m" + std::to_string(secs) + "s";
  return time;
}

void Activity::updateTimeElapsed(double timeToAdd) {
  time_elapsed_ += timeToAdd;
}
