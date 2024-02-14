#include <iostream>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <utility>
using namespace std;

void runApp();
void admin();
void employee();
void admin_login();
void admin_signup();
void employee_login();
void employee_signup();

class Admin
{
public:
    string username;
    string password;
    string name;
    string cab_id;

    Admin(string username, string password, string name, string cab_id)
    {
        this->username = username;
        this->password = password;
        this->name = name;
        this->cab_id = cab_id;
    }
};

class Employee
{
public:
    string username;
    string password;
    string name;

    Employee(string username, string password, string name)
    {
        this->username = username;
        this->password = password;
        this->name = name;
    }
};

class Cab
{
public:
    string cab_id;
    bool booked;
    pair<int, int> location;

    Cab(string cab_id)
    {
        this->cab_id = cab_id;
        this->booked = false;
        this->location.first = location.first;
        this->location.second = location.second;
    }
};

vector<Admin> admin_data;
vector<Employee> employee_data;
vector<Cab> cab_data;

string getPasswordFromUser()
{
    HANDLE hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;

    GetConsoleMode(hStdInput, &mode);

    SetConsoleMode(hStdInput, mode & (~ENABLE_ECHO_INPUT));

    string input;
    cin >> input;

    SetConsoleMode(hStdInput, mode);

    return input;
}

bool checkUsername(string username)
{
    int check1 = false, check2 = false;
    for (int i = 0; i < (int)admin_data.size(); ++i)
    {
        if (admin_data[i].username == username)
        {
            check1 = true;
            break;
        }
    }

    if (!check1)
    {
        for (int i = 0; i < (int)employee_data.size(); ++i)
        {
            if (employee_data[i].username == username)
            {
                check2 = true;
                break;
            }
        }
    }

    return check1 || check2;
}

string getName()
{
    cout << "Enter your name: " << endl;
    string name;
    cin >> name;
    return name;
}

string getCabId()
{
    cout << "Enter your cab id: " << endl;
    string cab_id;
    cin >> cab_id;

    return cab_id;
}

string getUsername()
{
    string username;
    cin >> username;
    return username;
}

pair<int, int> getCabLocation()
{
    int x, y;
    cin >> x >> y;
    pair<int, int> p;
    p.first = x;
    p.second = y;

    return p;
}

void admin_signup()
{
    cout << "Enter Username: " << endl;
    string username = getUsername();

    if (checkUsername(username))
    {
        cout << "Username exists" << endl;
        admin_signup();
    }

    string pass1, pass2;

    do
    {
        cout << "Enter password: " << endl;
        pass1 = getPasswordFromUser();
        cout << "Confirm Password: " << endl;
        pass2 = getPasswordFromUser();
    } while (pass1 != pass2);

    string password;
    if (pass1 == pass2)
        password = pass1;

    string name = getName();
    string cab_id = getCabId();
    pair<int, int> location = getCabLocation();

    Admin tempAdmin(username, password, name, cab_id);
    admin_data.push_back(tempAdmin);

    Cab tempCab(cab_id, location);
    cab_data.push_back(tempCab);

    runApp();
}

void admin_dashboard()
{
    system("CLS");

    cout << "=========================" << endl;
    cout << "ADMIN DASHBOARD" << endl;
    cout << "=========================" << endl;

    cout << "Login as an employee to avail services: " << endl;
    cout << "Enter 1 to login as an employee: " << endl;

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        employee();
    }
    else
    {
        cout << "Wrong input!";
        admin_dashboard();
    }
}

void admin_login()
{
    cout << "Enter username: " << endl;
    string username;
    cin >> username;

    int index = -1;

    for (int i = 0; i < (int)admin_data.size(); ++i)
    {
        if (admin_data[i].username == username)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        cout << "Username does not exist" << endl;
        admin_login();
    }

    else
    {
        cout << "Enter password: " << endl;
        string password = getPasswordFromUser();

        if (admin_data[index].password == password)
        {
            cout << "Login Successful" << endl;
            admin_dashboard();
        }
        else
        {
            cout << "Wrong password. Try Again." << endl;

            admin_login();
        }
    }
}

void employee_signup()
{
    cout << "Enter Username: " << endl;
    string username = getUsername();

    if (checkUsername(username))
    {
        cout << "Username exists" << endl;
        admin_signup();
    }

    string pass1, pass2;

    do
    {
        cout << "Enter password: " << endl;
        pass1 = getPasswordFromUser();
        cout << "Confirm Password: " << endl;
        pass2 = getPasswordFromUser();
    } while (pass1 != pass2);

    string password;
    if (pass1 == pass2)
        password = pass1;

    string name = getName();

    Employee tempEmployee(username, password, name);
    employee_data.push_back(tempEmployee);

    runApp();
}

void employee_dashboard()
{
    system("CLS");

    cout << "=======================" << endl;
    cout << "  Employee Dashboard   " << endl;
    cout << "=======================" << endl;

    cout << "Enter your location in geometric co-ordinates: " << endl;

    int xInitial, yInitial;
    cin >> xInitial >> yInitial;

    cout << "Enter your destination location in geometric co-cordinates" << endl;
    int xFinal, yFinal;
    cin >> xFinal >> yFinal;

    int min = INT_MAX;
    int cabAlloted = 0;
    for (int i = 0; i < cab_data.size(); ++i)
    {
        int x1 = cab_data[i].location.first;
        int x2 = cab_data[i].location.second;
        if (cab_data[i].booked == false)
        {
            int distance = (x1 - xInitial) * (x1 - xInitial) + (y1 - yInitial) * (y1 - yInitial);
            if (distance < min)
            {
                min = distance;
                cabAlloted = i;
            }
        }
    }

    cout << "The cab alloted to you is: " << cab_data[cabAlloted].cab_id << endl;
    cab_data[cabAlloted].booked = true;

    employee_dashboard();
}

void employee_login()
{
    cout << "Enter username: " << endl;
    string username;
    cin >> username;

    int index = -1;

    for (int i = 0; i < (int)employee_data.size(); ++i)
    {
        if (employee_data[i].username == username)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        cout << "Username does not exist" << endl;
        employee_login();
    }

    else
    {
        cout << "Enter password: " << endl;
        string password = getPasswordFromUser();

        if (employee_data[index].password == password)
        {
            cout << "Login Successful" << endl;
            employee_dashboard();
        }
        else
        {
            cout << "Wrong password. Try Again." << endl;

            employee_login();
        }
    }
}

void admin()
{
    system("CLS");
    cout << "ADMIN LOGIN/SIGNUP" << endl;
    cout << "1. SignUp" << endl;
    cout << "2. Login" << endl;
    cout << "3. Go Back" << endl;

    int choice;
    cin >> choice;

    if (choice == 3)
    {
        system("CLS");
        runApp();
    }

    else if (choice == 1)
    {
        admin_signup();
    }

    else if (choice == 2)
    {
        admin_login();
    }

    else
    {
        system("CLS");
        cout << "Wrong option selected" << endl;
        admin();
    }
}

void employee()
{
    system("CLS");
    cout << "EMPLOYEE LOGIN/SIGNUP";
    cout << "1. SignUp" << endl;
    cout << "2. Login" << endl;
    cout << "3. Go Back" << endl;

    int choice;
    cin >> choice;

    if (choice == 3)
    {
        system("CLS");
        runApp();
    }

    else if (choice == 1)
    {
        employee_signup();
    }

    else if (choice == 2)
    {
        employee_login();
    }

    else
    {
        system("CLS");
        cout << "Wrong option selected" << endl;
        employee();
    }
}

// drive function

void runApp()
{
    cout << "===========================" << endl;
    cout << "SMART CAB ALLOCATION SYSTEM" << endl;
    cout << "===========================" << endl;

    cout << "1. Admin Login" << endl;
    cout << "2. Employee Login" << endl;
    cout << "3. Quit" << endl;

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        admin();
    }

    else if (choice == 2)
    {
        employee();
    }

    else if (choice == 3)
    {
        return;
    }

    else
    {
        system("CLS");
        cout << "Wrong option selected" << endl;
        runApp();
    }
}

int main()
{

    runApp();

    return 0;
}