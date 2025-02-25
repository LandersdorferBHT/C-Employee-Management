//
//  main.cpp
//  ESA1
//
//  Created by Anton Landersdorfer on 15.05.24.
//

#include <iostream>
#include <string>

using namespace std;

const int MAX_EMPLOYEES = 500;

class Employee {
    
public:
    
    string name;
    string firstName;
    string birthDate;
    int disabilityDegree;
    int takenVacation;
    int vacationDays;
    
    // Constructor with default values
    Employee() : name(""), firstName(""), birthDate(""), disabilityDegree(0), takenVacation(0), vacationDays(30) {}
    
    void setData(string sName, string fName, string bDate, int dDegree) {
        name = sName;
        firstName = fName;
        birthDate = bDate;
        disabilityDegree = dDegree;
        takenVacation = 0;
        vacationDays = calculateVacationDays();
    }
    
    int calculateVacationDays() {
        int age = calculateAge();
        int days = 30; // 30 as default amount of vacation days
        
        if (age >= 50) {
            days += 2; // 2 additional vacation days if employee is atleast 50
        }
        
        if (disabilityDegree >= 50) {
            days += 5; // 5 additional vacation days if disability degree is atleast 50%
        }
        
        return days;
    }
    
    int calculateAge() {
        string birthYear = birthDate.substr(6, 4); //Extract birth year from format DD.MM.YYYY, Source: https://www.geeksforgeeks.org/substring-in-cpp/
        int year = stoi(birthYear); // Convert birth year from string to int, Source: https://www.geeksforgeeks.org/stdstoi-function-in-cpp/
        
        
        return 2024 - year;
    }
    
    int getRemainingVacation() {
        return vacationDays - takenVacation;
    }
    
    void takeVacation(int days) {
        
        if (takenVacation + days <= vacationDays) {
            takenVacation += days;
        } else {
            cout << "Not enough vacation days available!" << endl;
        }
        
    }
    
    void displayData() {
        cout << "Name: " << name << ", First Name: " << firstName
        << ", Birth Date: " << birthDate << ", Disability Degree: " << disabilityDegree
        << ", Taken Vacation: " << takenVacation << ", Remaining Vacation: " << getRemainingVacation() << endl;
    }
};

class VacationManagement {
    
private:
    
    Employee employeeList[MAX_EMPLOYEES];
    int employeeCount;
    
    // Validation of name (only letters allowed)
    bool validateName(string input) {
        
        for (char c : input) {
            
            if (!isalpha(c)) { // Source: https://www.programiz.com/cpp-programming/library-function/cctype/isalpha
                return false;
            }
            
        }
        return true;
    }
    
public:
    
    string name;
    string firstName;
    string birthDate;
    int disabilityDegree;
    
    // Initialize employee count to 0
    VacationManagement() : employeeCount(0) {}
    
    void addEmployee() {
        
        // Check if max amount of employees (500) is reached
        if (employeeCount >= MAX_EMPLOYEES) {
            cout << "Maximum number of employees reached!" << endl;
            return;
        }
        
        cout << "Name: ";
        cin >> name;
        
        // Surname should only have letters
        if (!validateName(name)) {
            cout << "Invalid name. Only letters are allowed." << endl;
            return;
        }
        
        cout << "First Name: ";
        cin >> firstName;
        
        //First name should only have letters
        if (!validateName(firstName)) {
            cout << "Invalid first name. Only letters are allowed." << endl;
            return;
        }
        
        cout << "Birth Date (DD.MM.YYYY): ";
        cin >> birthDate;
        
        // Birthdate needs to be in format DD.MM.YYYY
        if (birthDate.length() != 10 || birthDate[2] != '.' || birthDate[5] != '.') {
            cout << "Invalid birth date format. Use DD.MM.YYYY." << endl;
            return;
        }
        
        cout << "Disability Degree (%): ";
        
        // Disability degree needs to be between 0 and 100
        if (!(cin >> disabilityDegree) || disabilityDegree < 0 || disabilityDegree > 100) {
            cout << "Invalid disability degree. Enter a number between 0 and 100." << endl;
            cin.clear();
            cin.ignore();
            return;
        }
        
        employeeList[employeeCount].setData(name, firstName, birthDate, disabilityDegree);
        employeeCount++;
    }
    
    void deleteEmployee() {
        
        string name;
        string firstName;
        
        cout << "Name: ";
        cin >> name;
        cout << "First Name: ";
        cin >> firstName;
        
        // Search for employee in list
        for (int i = 0; i < employeeCount; ++i) {
            
            if (employeeList[i].name == name && employeeList[i].firstName == firstName) {
                
                // Shift remaining employees to empty index
                for (int j = i; j < employeeCount - 1; ++j) {
                    employeeList[j] = employeeList[j + 1];
                }
                
                employeeCount--;
                cout << "Employee " << name << " " << firstName << " deleted." << endl;
                
                return;
            }
        }
        cout << "Employee not found!" << endl;
    }
    
    void inputVacationDays() {
        
        string name;
        string firstName;
        int days;
        
        cout << "Name: ";
        cin >> name;
        cout << "First Name: ";
        cin >> firstName;
        cout << "Number of vacation days: ";
        
        // Number of vacation days to take
        if (!(cin >> days) || days < 0) {
            cout << "Invalid number of days. Enter a positive number." << endl;
            cin.clear();
            cin.ignore();
            return;
        }
        
        // Get employee in list and add vacation days
        for (int i = 0; i < employeeCount; ++i) {
            
            if (employeeList[i].name == name && employeeList[i].firstName == firstName) {
                employeeList[i].takeVacation(days);
                return;
            }
        }
        cout << "Employee not found!" << endl;
    }
    
    void searchEmployee() {
        
        string name;
        string firstName;
        
        cout << "Name: ";
        cin >> name;
        cout << "First Name: ";
        cin >> firstName;
        
        // Search employee by full name
        for (int i = 0; i < employeeCount; ++i) {
            
            if (employeeList[i].name == name && employeeList[i].firstName == firstName) {
                employeeList[i].displayData();
                return;
            }
        }
        cout << "Employee not found!" << endl;
    }
    
    void displayAllEmployees() {
        
        // Loops through all employees and displayus their data1
        
        for (int i = 0; i < employeeCount; ++i) {
            employeeList[i].displayData();
        }
    }
};

int main(int argc, char *argv[]) {
    
    VacationManagement vacationManager;
    int choice;
    
    do {
        
        // Display menu to the user
        cout << "\nVacation Management Menu:\n";
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Enter Vacation Days\n";
        cout << "4. Search Employee\n";
        cout << "5. Display All Employees\n";
        cout << "6. Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        
        cin.ignore(); // Clear the input buffer
        
        
        // Perform actions based on the users choice
        switch (choice) {
            case 1:
                vacationManager.addEmployee();
                break;
                
            case 2:
                vacationManager.deleteEmployee();
                break;
                
            case 3:
                vacationManager.inputVacationDays();
                break;
                
            case 4:
                vacationManager.searchEmployee();
                break;
                
            case 5:
                vacationManager.displayAllEmployees();
                break;
                
            case 6:
                cout << "Exiting program.\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
        
    } while (choice != 6); // Repeats showing the menu until user chooses to exit
    
    return 0;
}


