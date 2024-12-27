#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // For system("CLS") and system("PAUSE")
using namespace std;

// Car rental structure
struct Cars {
    vector<string> company = {"Maruti Suzuki", "Volkswagen", "BMW", "Audi", "KIA", "Tesla", "Mercedes", "Mahindra", "TATA"};
    vector<vector<string>> models = {
        {"800", "Swift"},
        {"2020", "Passat"},
        {"Q7", "X5"},
        {"R8", "A4"},
        {"Seltos", "Sonet"},
        {"S-Series", "Model 3"},
        {"Benz", "C-Class"},
        {"Thar", "Scorpio"},
        {"Nano", "Harrier", "Safari"}
    };
    vector<string> color = {"White", "Black", "Green", "Yellow", "Red", "Blue", "Silver", "Black", "Grey"};
    vector<string> max_speed = {"80 Km/h", "200 Km/h", "300 Km/h", "250 Km/h", "320 Km/h", "400 Km/h", "200 Km/h", "250 Km/h", "280 Km/h"};
    vector<int> price = {10000, 20000, 50000, 40000, 50000, 60000, 70000, 20000, 15000};
    vector<int> date = {2020, 2012, 2019, 2018, 2017, 2016, 2015, 2021, 2010};
} car;

// Bike rental structure
struct Bikes {
    vector<string> company = {"Hero", "Honda", "Yamaha", "Royal Enfield", "KTM", "Suzuki"};
    vector<string> model = {"Splendor", "Shine", "R15", "Classic 350", "Duke 200", "Gixxer"};
    vector<string> color = {"White", "Blue", "Red", "Green", "Yellow", "Black"};
    vector<string> max_speed = {"60 Km/h", "80 Km/h", "130 Km/h", "120 Km/h", "140 Km/h", "100 Km/h"};
    vector<int> hourly_rate = {50, 60, 80, 100, 120, 70};
} bike;

struct LeaseInfo {
    vector<string> Name;
    vector<string> Natio_ID;
    vector<int> payment_acc;
} lease;

vector<string> rental_history;

// Displays main menu
void Menu() {
    cout << "\n\t\t\tWelcome to Gear Go\n\n";
    cout << "\t\t1 - Rent a Car\n";
    cout << "\t\t2 - Rent a Bike\n";
    cout << "\t\t3 - Search for a Vehicle\n";
    cout << "\t\t4 - View Rental History\n";
    cout << "\t\t0 - Exit\n";
}

// Displays car details
void Details(int choice) {
    system("CLS");
    cout << "\n\n\t\tYou Have Selected - " << car.company[choice - 1] << "\n";
    cout << "\t\tAvailable Models:\n";
    for (const auto& model : car.models[choice - 1]) {
        cout << "\t\t- " << model << "\n";
    }
    cout << "\t\tColor: " << car.color[choice - 1] << "\n";
    cout << "\t\tMaximum Speed: " << car.max_speed[choice - 1] << "\n";
    cout << "\t\tPrice: " << car.price[choice - 1] << "\n";
    cout << "\t\tManufacture Date: " << car.date[choice - 1] << "\n";
}

// Displays bike details
void BikeDetails(int choice) {
    system("CLS");
    cout << "\n\n\t\tYou Have Selected - " << bike.company[choice - 1] << "\n";
    cout << "\t\tModel: " << bike.model[choice - 1] << "\n";
    cout << "\t\tColor: " << bike.color[choice - 1] << "\n";
    cout << "\t\tMaximum Speed: " << bike.max_speed[choice - 1] << "\n";
    cout << "\t\tHourly Rate: $" << bike.hourly_rate[choice - 1] << "\n";
}

// Handles bike rental
void RentBike() {
    int choice;
    system("CLS");
    cout << "\t\tAvailable Bikes:\n";
    for (size_t i = 0; i < bike.company.size(); ++i) {
        cout << "\t\t" << (i + 1) << " - " << bike.company[i] << " (" << bike.model[i] << ")\n";
    }
    cout << "\t\tEnter the number to select a bike (or 0 to go back): ";
    cin >> choice;

    if (choice == 0) return;

    if (choice > 0 && choice <= (int)bike.company.size()) {
        BikeDetails(choice);

        string name, id;
        int hours, payment;
        cout << "\t\tEnter Your Name: ";
        cin >> name;
        cout << "\t\tEnter Your National ID: ";
        cin >> id;
        cout << "\t\tEnter Number of Hours to Rent: ";
        cin >> hours;

        int cost = bike.hourly_rate[choice - 1] * hours;
        cout << "\t\tDo you need a helmet? (yes/no): ";
        string helmet;
        cin >> helmet;

        if (helmet == "yes") cost += 10; // Add $10 for helmet

        cout << "\t\tTotal Cost: $" << cost << "\n";
        cout << "\t\tEnter Payment Amount: ";
        cin >> payment;

        if (payment >= cost) {
            cout << "\t\tPayment Successful! Enjoy your ride!\n";
            rental_history.push_back(name + " rented " + bike.company[choice - 1] + " for " + to_string(hours) + " hours");
        } else {
            cout << "\t\tPayment Failed: Insufficient Amount!\n";
        }
    } else {
        cout << "\t\tInvalid Choice. Returning to Menu.\n";
    }
    system("PAUSE");
}

// Handles car lease
void CheckLease(int index, int payment) {
    if (payment >= car.price[index]) {
        cout << "\n\t\tPayment Successful! Enjoy your car!\n";
        rental_history.push_back(lease.Name.back() + " rented " + car.company[index]);
    } else {
        cout << "\n\t\tPayment Failed: Insufficient Amount!\n";
    }
}

// Collects user input for car rental
void UserInput(int choice) {
    system("CLS");
    int index = choice - 1;
    string name, id;
    int payment;

    cout << "\t\tPlease Provide Your Details:\n";
    cout << "\t\tEnter Your Name: ";
    cin >> name;
    lease.Name.push_back(name);

    cout << "\t\tEnter Your National ID: ";
    cin >> id;
    lease.Natio_ID.push_back(id);

    cout << "\t\tEnter Payment Amount: ";
    cin >> payment;
    lease.payment_acc.push_back(payment);

    CheckLease(index, payment);
}

// Searches for vehicles within budget and color preference
void SearchCar() {
    system("CLS");
    int budget;
    string preferred_color;
    cout << "\t\tEnter your budget: ";
    cin >> budget;
    cout << "\t\tEnter preferred color: ";
    cin >> preferred_color;

    cout << "\n\t\tCars matching your criteria:\n";
    for (size_t i = 0; i < car.company.size(); ++i) {
        if (car.price[i] <= budget && car.color[i] == preferred_color) {
            cout << "\t\t" << car.company[i] << " - " << car.models[i][0] << " - $" << car.price[i] << "\n";
        }
    }

    cout << "\n\t\tBikes matching your criteria:\n";
    for (size_t i = 0; i < bike.company.size(); ++i) {
        if (bike.hourly_rate[i] * 5 <= budget && bike.color[i] == preferred_color) { // Assuming 5 hours of rental
            cout << "\t\t" << bike.company[i] << " - " << bike.model[i] << " - $" << bike.hourly_rate[i] << "/hour\n";
        }
    }
}

// Displays rental history
void DisplayRentalHistory() {
    system("CLS");
    cout << "\t\tRental History:\n";
    for (const auto &entry : rental_history) {
        cout << "\t\t" << entry << "\n";
    }
    system("PAUSE");
}

// Login function
bool Login() {
    string pass;
    cout << "\n\n\t\t GEARGO: Revolutizing the art of travel\n";
    cout << "\n\t\t\t Vehicle Rental System Login\n";
    cout << "\n\t\tEnter Password: ";
    cin >> pass;

    if (pass == "pass") {
        cout << "\t\tAccess Granted! Welcome!\n";
        system("PAUSE");
        system("CLS");
        return true;
    } else {
        cout << "\t\tAccess Denied. Try Again.\n";
        return false;
    }
}

int main() {
    if (!Login()) {
        return 0;
    }

    while (true) {
        Menu();
        cout << "\n\t\tYour Choice: ";
        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "\t\tThank you for using the Vehicle Rental System.\n";
            break;
        }

        switch (choice) {
            case 1: {
                system("CLS");
                cout << "\t\tAvailable Cars:\n";
                for (size_t i = 0; i < car.company.size(); ++i) {
                    cout << "\t\t" << (i + 1) << " - " << car.company[i] << "\n";
                }
                cout << "\t\tEnter the number to select a car (or 0 to go back): ";
                cin >> choice;
                if (choice > 0 && choice <= (int)car.company.size()) {
                    Details(choice);
                    cout << "\n\t\tWould you like to rent this car? (yes/no): ";
                    string decision;
                    cin >> decision;
                    if (decision == "yes") {
                        UserInput(choice);
                    }
                }
                break;
            }
            case 2:
                RentBike();
                break;
            case 3:
                SearchCar();
                system("PAUSE");
                break;
            case 4:
                DisplayRentalHistory();
                break;
            default:
                cout << "\t\tInvalid choice. Please try again.\n";
                break;
        }
        system("CLS");
    }

    return 0;
}
