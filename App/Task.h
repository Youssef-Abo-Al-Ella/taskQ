#pragma once
#include<string>
#include<iostream>
#include <ctime>
#include <iomanip>
#include <vector>
class Task
{
private:
	std::string name;
	bool important = true;
	bool urgent = true;
	std::time_t date;
	int timeSpent = 0;
	bool continuous = true;
	bool switchable = true;
public:
    // Setters
    void setName(const std::string& taskName) {
        name = taskName;
    }

    void setImportant(bool isImportant) {
        important = isImportant;
    }

    void setUrgent(bool isUrgent) {
        urgent = isUrgent;
    }

    void setDate(std::time_t taskDate) {
        date = taskDate;
    }

    void updateTimeSpent(int time) {
        timeSpent += time;
    }

    void setContinuous(bool isContinuous) {
        continuous = isContinuous;
    }

    void setSwitchable(bool isSwitchable) {
        switchable = isSwitchable;
    }

    // Getters
    std::string getName() const {
        return name;
    }

    bool isImportant() const {
        return important;
    }

    bool isUrgent() const {
        return urgent;
    }

    std::time_t getDate() const {
        return date;
    }

    int getTimeSpent() const {
        return timeSpent;
    }

    bool isContinuous() const {
        return continuous;
    }

    bool isSwitchable() const {
        return switchable;
    }
    Task();
    Task(std::string tname);
    std::string getFormatedDate();
    void wirteToDisk();
    static std::vector<Task> readFromDisk();
    static void removeFromDisk(const std::string& taskName);
    std::string toString();
    static bool checkExists(std::string name);
};

