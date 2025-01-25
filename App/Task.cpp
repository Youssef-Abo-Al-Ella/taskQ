#include "Task.h"
#include<ctime>
#include <iomanip> // For std::put_time
#include <sstream> // For std::ostringstream
#include<fstream>
Task::Task()
{
	time(&date);
}

Task::Task(std::string tname)
{
	time(&date);
	name = tname;
}

std::string Task::getFormatedDate()
{
    // Convert the raw time to a struct tm
    std::tm* timeInfo = std::localtime(&date);

    // Use std::ostringstream to format the date and time
    std::ostringstream formattedDate;
    formattedDate << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");

    // Return the formatted date as a string
    return formattedDate.str();
}

void Task::wirteToDisk()
{
    // Open the file in append mode
    std::ofstream file("persistent_tasks.txt", std::ios::app);

    if (!file) {
        std::cerr << "Error: Could not open the file for writing.\n";
        return;
    }

    // Write the task details to the file
    file<< "{\n"
        << "\tTask Name: " << name << ",\n"
        << "\tImportant: " << (important ? "Yes" : "No") << ",\n"
        << "\tUrgent: " << (urgent ? "Yes" : "No") << ",\n"
        << "\tDate: " << getFormatedDate() << ",\n"
        << "\tTime Spent: " << timeSpent << " minutes,\n"
        << "\tContinuous: " << (continuous ? "Yes" : "No") << ",\n"
        << "\tSwitchable: " << (switchable ? "Yes" : "No") << ",\n"
        << "}\n";

    // Close the file
    file.close();
}

std::vector<Task> Task::readFromDisk()
{
    std::ifstream file("persistent_tasks.txt");
    std::vector<Task> tasks;

    if (!file) {
        std::cerr << "Error: Could not open the file for reading.\n";
        return tasks;
    }

    std::string line;
    Task currentTask;

    while (std::getline(file, line)) {
        // Trim whitespace from the beginning of the line
        line.erase(0, line.find_first_not_of(" \t"));

        if (line.find("Task Name:") != std::string::npos) {
            // Extract the task name
            size_t start = line.find(":") + 2;
            size_t end = line.find(",");
            currentTask.setName(line.substr(start, end - start));
        }
        else if (line.find("Important:") != std::string::npos) {
            // Extract the importance
            currentTask.setImportant(line.find("Yes") != std::string::npos);
        }
        else if (line.find("Urgent:") != std::string::npos) {
            // Extract the urgency
            currentTask.setUrgent(line.find("Yes") != std::string::npos);
        }
        else if (line.find("Date:") != std::string::npos) {
            // Extract and parse the date
            size_t start = line.find(":") + 2;
            size_t end = line.find(",");
            std::string dateStr = line.substr(start, end - start);

            std::tm timeInfo = {};
            std::istringstream ss(dateStr);
            ss >> std::get_time(&timeInfo, "%Y-%m-%d %H:%M:%S");
            std::time_t date = std::mktime(&timeInfo);
            currentTask.setDate(date);
        }
        else if (line.find("Time Spent:") != std::string::npos) {
            // Extract the time spent
            size_t start = line.find(":") + 2;
            size_t end = line.find(" ");
            currentTask.updateTimeSpent(std::stoi(line.substr(start, end - start)));
        }
        else if (line.find("Continuous:") != std::string::npos) {
            // Extract the continuous flag
            currentTask.setContinuous(line.find("Yes") != std::string::npos);
        }
        else if (line.find("Switchable:") != std::string::npos) {
            // Extract the switchable flag
            currentTask.setSwitchable(line.find("Yes") != std::string::npos);
        }
        else if (line.find("}") != std::string::npos) {
            // End of a task object
            tasks.push_back(currentTask);
            currentTask = Task(); // Reset the current task for the next entry
        }
    }

    file.close();
    return tasks;
}
