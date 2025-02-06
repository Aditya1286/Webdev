#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <string>
#include <vector>

class TodoList {
private:
    std::vector<std::string> tasks;

public:
    void addTask(const std::string& task);
    void removeTask(int index);
    void displayTasks() const;
    int getTaskCount() const;
};

#endif

// todo_list.cpp
#include "todo_list.h"
#include <iostream>

void TodoList::addTask(const std::string& task) {
    tasks.push_back(task);
}

void TodoList::removeTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);
    }
}

void TodoList::displayTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks in the list." << std::endl;
        return;
    }

    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". " << tasks[i] << std::endl;
    }
}

int TodoList::getTaskCount() const {
    return tasks.size();
}

// main.cpp
#include <iostream>
#include "todo_list.h"

void displayMenu() {
    std::cout << "\n--- Todo List Menu ---" << std::endl;
    std::cout << "1. Add Task" << std::endl;
    std::cout << "2. Remove Task" << std::endl;
    std::cout << "3. View Tasks" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    TodoList todoList;
    int choice;
    std::string task;

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cin.ignore();
                std::cout << "Enter task: ";
                std::getline(std::cin, task);
                todoList.addTask(task);
                break;
            }
            case 2: {
                int index;
                std::cout << "Enter task number to remove: ";
                std::cin >> index;
                todoList.removeTask(index - 1);
                break;
            }
            case 3:
                todoList.displayTasks();
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    }

    return 0;
}
