#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Function to display the menu
void displayMenu() {
  std::cout << "To-Do List Menu:\n";
  std::cout << "1. Add a task\n";
  std::cout << "2. View tasks\n";
  std::cout << "3. Edit a task\n";
  std::cout << "4. Delete a task\n";
  std::cout << "5. Save tasks to file\n";
  std::cout << "6. Exit and Save\n";
  std::cout << "Choose an option: ";
}

// Function to add a task to the vector
void addTask(std::vector<std::string> &tasks) {
  std::string task;
  std::cout << "Enter the task: ";
  std::cin.ignore(); // Clear the buffer before taking a multi-word input
  std::getline(std::cin, task);
  tasks.push_back(task);
}

// Function to view the tasks stored in the vector
void viewTasks(const std::vector<std::string> &tasks) {
  if (tasks.empty()) {
    std::cout << "No tasks available.\n";
    return;
  }
  std::cout << "Your tasks:\n";
  for (size_t i = 0; i < tasks.size(); ++i) {
    std::cout << i + 1 << ". " << tasks[i] << "\n";
  }
}

// Function to edit a task
void editTask(std::vector<std::string> &tasks) {
  if (tasks.empty()) {
    std::cout << "No tasks available to edit.\n";
    return;
  }

  viewTasks(tasks); // Show current tasks

  int taskNumber;
  std::cout << "Enter the number of the task you want to edit: ";
  std::cin >> taskNumber;

  if (taskNumber < 1 || taskNumber > tasks.size()) {
    std::cout << "Invalid task number.\n";
    return;
  }

  std::cin.ignore(); // Clear the buffer before taking a new task description
  std::string newTask;
  std::cout << "Enter the new description for task " << taskNumber << ": ";
  std::getline(std::cin, newTask);

  tasks[taskNumber - 1] = newTask;
  std::cout << "Task " << taskNumber << " has been updated.\n";
}

// Function to delete a task
void deleteTask(std::vector<std::string> &tasks) {
  if (tasks.empty()) {
    std::cout << "No tasks available to delete.\n";
    return;
  }

  viewTasks(tasks); // Show current tasks

  int taskNumber;
  std::cout << "Enter the number of the task you want to delete: ";
  std::cin >> taskNumber;

  if (taskNumber < 1 || taskNumber > tasks.size()) {
    std::cout << "Invalid task number.\n";
    return;
  }

  tasks.erase(tasks.begin() + taskNumber - 1);
  std::cout << "Task " << taskNumber << " has been deleted.\n";
}

// Function to save tasks to a file
void saveTasksToFile(const std::vector<std::string> &tasks) {
  std::ofstream outFile("tasks.txt");
  if (outFile.is_open()) {
    for (const auto &task : tasks) {
      outFile << task << "\n";
    }
    std::cout << "Tasks saved to tasks.txt\n";
    outFile.close();
  } else {
    std::cerr << "Error: Unable to open file for writing.\n";
  }
}

// Function to load tasks from a file
void loadTasksFromFile(std::vector<std::string> &tasks) {
  std::ifstream inFile("tasks.txt");
  if (inFile.is_open()) {
    std::string task;
    while (std::getline(inFile, task)) {
      tasks.push_back(task);
    }
    inFile.close();
  } else {
    std::cerr << "No existing tasks found. Starting with an empty list.\n";
  }
}

// Main function
int main() {
  std::vector<std::string> tasks;
  int choice;

  // Load tasks from file at the start
  loadTasksFromFile(tasks);

  while (true) {
    displayMenu();
    std::cin >> choice;

    switch (choice) {
    case 1:
      addTask(tasks);
      break;
    case 2:
      viewTasks(tasks);
      break;
    case 3:
      editTask(tasks);
      break;
    case 4:
      deleteTask(tasks);
      break;
    case 5:
      saveTasksToFile(tasks);
      break;
    case 6:
      saveTasksToFile(tasks);
      std::cout << "Exiting...\n";
      return 0;
    default:
      std::cout << "Invalid option. Please choose again.\n";
    }
  }

  return 0;
}
