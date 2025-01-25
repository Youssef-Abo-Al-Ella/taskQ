#include <iostream>
#include <vector>
#include "../Task.h"

void resetTerminal();
void createTaskScreen();
std::vector<Task> toDo;

using std::cout, std::cin, std::string;

int main() {
    toDo = Task::readFromDisk();
    char option;

    do {
        resetTerminal();
        cout << "1- Create a task\n";
        cout << "2- Start working\n";
        cout << "3- View tasks\n";
        cout << "4- Delete task\n";
        cout << "q- Quit\n";
        cout << "Enter your choice: ";
        cin >> option;

        // Clear the input buffer
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (option == '1') {
            createTaskScreen();
        }
        else if (option == '2') {
            resetTerminal();
            cout << "Feature to start working is not implemented yet.\n";
            cin.get(); // Pause for user to read
        }
        else if (option == '3') {
            resetTerminal();
            cout << "Viewing tasks...\n";
            for ( auto& task : toDo) {
                cout << task.toString() << "\n\n";
            }
            cin.get(); // Pause to let user view tasks
        }
        else if (option =='4') {
            resetTerminal();
            std::string temp;
            cout << "Enter the name of the task you want to remove\n";
            cin >> temp;
            Task::removeFromDisk(temp);
            toDo = Task::readFromDisk();
        }else if (option != 'q') {
            resetTerminal();
            cout << "Invalid option. Please try again.\n";
            cin.get(); // Pause for user to read
        }
    } while (option != 'q');

    cout << "Goodbye!\n";
    return 0;
}

void resetTerminal() {
    // ANSI escape code to clear the terminal and move cursor to the top-left corner
    std::cout << "\033[2J\033[H";
}

void createTaskScreen() {
    char option;
    Task newTask;
    std::string temp;

    resetTerminal();
    cout << "Enter task name: ";
    cin >> temp;

    // Clear input buffer
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (Task::checkExists(temp)) {
        cout << "Task already exists!\n";
        cin.get(); // Pause for user to read the message
        return;
    }
    newTask.setName(temp);

    do {
        resetTerminal();
        cout << newTask.toString() << "\n";
        cout << "---------------------------------\n";
        cout << "Enter the number of configuration to change or 'q' to quit:\n";
        cout << "1- Change name\n";
        cout << "2- Toggle importance\n";
        cout << "3- Toggle urgency\n";
        cout << "4- Toggle continuity\n";
        cout << "5- Toggle switchability\n";
        cout << "Enter your choice: ";
        cin >> option;

        // Clear input buffer
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (option == '1') {
            resetTerminal();
            cout << "Enter the new name: ";
            cin >> temp;

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (Task::checkExists(temp)) {
                cout << "Task already exists!\n";
                cin.get(); // Pause for user to read the message
                return;
            }
            newTask.setName(temp);
        }
        else if (option == '2') {
            newTask.setImportant(!newTask.isImportant());
        }
        else if (option == '3') {
            newTask.setUrgent(!newTask.isUrgent());
        }
        else if (option == '4') {
            newTask.setContinuous(!newTask.isContinuous());
        }
        else if (option == '5') {
            newTask.setSwitchable(!newTask.isSwitchable());
        }
        else if (option != 'q') {
            cout << "Invalid option. Please try again.\n";
            cin.get(); // Pause for user to read the message
        }
    } while (option != 'q');

    // Save the task to disk and update the in-memory list
    newTask.wirteToDisk();
    toDo.push_back(newTask);

    cout << "Task saved successfully!\n";
    cin.get(); // Pause for user to read the message
}
