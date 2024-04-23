#ifndef JOB_TRACKER_FUNCTIONS_H
#define JOB_TRACKER_FUNCTIONS_H

#include <cctype>
#include <fstream> 
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>

using namespace std;

//Function for splitting a line 
vector<string> split(string s){
    vector<string> splitted;
    string temp = "";
    int cnt = 0;

    for (char c : s){   
        if (c != ';'){
            temp += c;   
        }
        else{
            splitted.push_back(temp);
            temp = "";
        }
    }
    splitted.push_back(temp);
    return splitted;
}


//reading data from given file to given location
int read_file(string filename, vector<vector<string>> &data){
    ifstream inputFile;
    inputFile.open(filename);

    if (!inputFile.is_open()){
        cout << "Error opening a file " << filename << endl;
        return 1;
    }
    
    //reading and splitting data from file
    string line;
    
    while (getline(inputFile, line)){
        data.push_back(split(line));
    }

    inputFile.close();
    return 0;
}


//Transforming data to table
int format_table(vector<vector<string>> data) {
    // Calculate the maximum width for each column
    vector<size_t> maxColumnWidths(data[0].size(), 0);
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); i++) {
            maxColumnWidths[i] = max(maxColumnWidths[i], row[i].length());
        }
    }

    int starsAmount = 14;
    for (int i = 0; i < maxColumnWidths.size(); i++){
        starsAmount += maxColumnWidths[i];
    }

    string stars(starsAmount, '#');
    // Draw header
    cout << stars << endl;
    cout << "#  ";

    string header[5] = {"ID", "DATE", "COMPANY", "POSITION", "STATUS"};

    for (size_t i = 0; i < sizeof(header) / sizeof(header[0]); i++) {
            cout << left << setw(maxColumnWidths[i] + 2) << header[i];
    }
    cout << "#" << endl;
    cout << stars << endl;

    //draw rest
    for (const auto& row : data) {
        cout << "#  ";
        for (size_t i = 0; i < row.size(); ++i) {
            cout << left << setw(maxColumnWidths[i] + 2) << row[i];
        }
        cout << "#" << endl;
    }
    cout << stars << endl;

    return 0;
}


//writing new job offer
int write_file(string filename){
    return 0;
}



//hash user password
string hash_passwd(string passwd){
    string hash_passwd = "";

    for (char c : passwd){
        hash_passwd += c + 1;
    }

    return hash_passwd;
}


//login to a system
pair<int , string>  log_in(){
    string login;
    string passwd;
    vector<vector<string>> data;

    cout << "$ Login: ";
    cin >> login;
    cout << "$ Password: ";
    cin >> passwd;

    if (read_file("passwords.txt", data) != 0)
        return make_pair(1, "");
    
    for (vector<string> user:data)
    {
        if (user[0] == login && user[1] == hash_passwd(passwd)){

            cout << endl;
            cout << "Welcome "<< login << "!" << endl;
            return make_pair(0, login);
        } 
    }

    cout << "Wrong login or password!"<< endl;
    cout << endl;
    return make_pair(1, "");
}


//add new user to a system
pair<int , string> add_new_user(){
    //read all data in file
    vector<vector<string>> data;
    if (read_file("passwords.txt", data) != 0)
        return make_pair(1, "");

    string new_login;
    string new_password;

    //check if login exists
    bool login_exists = true;
    while (login_exists)
    {
        cout << "Login: ";
        cin >> new_login;

        for (vector<string> user : data){
            if (user[0] == new_login){
                cout << "This login is taken. Please choose another one" <<endl;
                login_exists = true;
                break;
            }

            login_exists = false;
        }
    }

    cout << "Password: ";
    cin >> new_password; 

    // Open a file for writing
    ofstream outputFile("passwords.txt");

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cout << "Error opening the file." << endl;
        return make_pair(1, "");
    }

    // Write data to the file
    for (vector<string> user : data){
        outputFile << user[0] << ";" << user[1] << endl;
    }

    outputFile << new_login << ";" << hash_passwd(new_password) << endl;

    // Close the file
    outputFile.close();

    //create data base for user
    ofstream newUserFile("users_data/" + new_login + ".txt");

    if (!newUserFile.is_open()) {
        cerr << "Error opening the file." << std::endl;
        return make_pair(1, ""); // Return non-zero to indicate failure
    }

    newUserFile.close();

    return make_pair(0, new_login);
}


//log out of a system
int log_out(){
    return 0;
}


void welcome(){
    cout << "######################" << endl;
    cout << "# JOB OFFERS MANAGER #" << endl;
    cout << "######################" << endl;
    cout << endl;
}


int start_screen(string &user) {
    pair<int, string> login = make_pair(1, "");
    char response;

    do {
        cout << "1. Log in" << endl;
        cout << "2. Add new user" <<endl;
        cout << "3. Quit" << endl;

        cout << "$ ";
        cin.clear();
        cin >> response;

        //check if response is valid
        if (!isdigit(response)) {
            //if response is not valid ignore all characters
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        //converting char to int
        int numeric_response = response - '0';

        switch (numeric_response) {
            case 1:
                login = log_in();
                if (login.first == 0){
                    user = login.second; 
                    break;
                }
                break;
            case 2:
                login = add_new_user();
                if (login.first == 0){
                    user = login.second; 
                    break;
                }
                break;
            case 3:
                cout << "Goodbye!" << endl;
                return 2;
            default:
                cout << "Wrong command" << endl;
                break;
        }
    } while (login.first != 0);

    return 0;
}


int show_offers(string user){
    // readign test file
    vector<vector<string>> data;
    
    if (read_file("users_data/" + user + ".txt", data) != 0)
        return 1;

    format_table(data);
    cout << endl;

    return 0;
}


//writing new job offer
int add_offer(string user){
    vector<vector<string>> data;
    
    if (read_file("users_data/" + user + ".txt", data) != 0)
        return 1;

    string date;
    string company;
    string position;
    // string status;

    cout << "Date: "; cin >> date;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Company: "; 
    getline(cin, company);
    cout << "Position: "; 
    getline(cin, position);
    // cout << "Status: "; cin >> status;
    cout << endl;


    // Open a file for writing
    ofstream outputFile("users_data/" + user + ".txt");

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cout << "Error opening the file." << endl;
        return 1;
    }
    
    // Write data to the file
    int cnt = 1;
    for (vector<string> position : data){
        outputFile << cnt << ";" << position[1] << ";" << position[2] << ";" << position[3] <<" ;" << position[4]<< endl;
        cnt++;
    }

    outputFile<< cnt << ";" << date << ";" << company << ";" << position << ";" << "Waitlist" << endl;

    // Close the file
    outputFile.close();
    return 0;
}


//delate job offer
int delete_offer(string user){
    string id;
    cout << "Which offer do you want to delete? (id) $ ";
    cin >> id;

    vector<vector<string>> data;
    
    if (read_file("users_data/" + user + ".txt", data) != 0)
        return 1;


    // Open a file for writing
    ofstream outputFile("users_data/" + user + ".txt");

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cout << "Error opening the file." << endl;
        return 1;
    }
    
    // Write data to the file
    int cnt = 1;
    for (vector<string> position : data){
        if (position[0] != id){
        outputFile << cnt << ";" << position[1] << ";" << position[2] << ";" << position[3] <<" ;" << position[4]<< endl;
        cnt++;
        }
    }

    // Close the file
    outputFile.close();
    return 0;
}


//update data
int update_offer(string user){
    string id;
    cout << "Which offer do you want to update? (id) $ ";
    cin >> id;

    vector<vector<string>> data;
    
    if (read_file("users_data/" + user + ".txt", data) != 0)
        return 1;


    // Open a file for writing
    ofstream outputFile("users_data/" + user + ".txt");

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cout << "Error opening the file." << endl;
        return 1;
    }
    
    // Write data to the file
    string new_date;
    string new_company;
    string new_position;
    string new_status;

    int cnt = 1;
    for (vector<string> position : data){
        if (position[0] != id){
        outputFile << cnt << ";" << position[1] << ";" << position[2] << ";" << position[3] <<" ;" << position[4]<< endl;
        cnt++;
        }
        else{
            string columns[4] = {new_date, new_company, new_position, new_status};

            for (int i = 0; i < 4; i++){
                cout << "OLD:  " << position[i + 1] <<endl;
                cout << "NEW $ ";
                getline(cin, columns[i]);
                if (new_date.empty()) {
                    new_date = position[i + 1];
                }
            }

            outputFile << cnt << ";" << new_date << ";" << new_company << ";" << new_position <<" ;" << new_status<< endl;
        }
    }

    // Close the file
    outputFile.close();
    return 0;
}

int focus_group(string user){
    return 0;
}

int user_screen(string user){
    char response;

    do {
        cout << "1. See offers" << endl;
        cout << "2. Add offer" <<endl;
        cout << "3. Delete offer" << endl;
        cout << "4. Update offer" << endl;
        cout << "5. Focus group" << endl;
        cout << "6. Log out" << endl;
        cout << "7. Quit" << endl;

        cout << "$ ";
        cin >> response;

        //check if response is valid
        if (!isdigit(response)) {
            //if response is not valid ignore all characters
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        //converting char to int
        int numeric_response = response - '0';

        switch (numeric_response) {
            case 1:
                show_offers(user);
                break;
            case 2:
                add_offer(user);
                break;
            case 3:
                delete_offer(user);
                break;
            case 4:
                update_offer(user);
                break;
            case 5:
                focus_group(user);
                return 2;
            case 6:
                log_out();
                return 2;
            case 7:
                cout << "Goodbye!" << endl;
                return 2;
            default:
                cout << "Wrong command" << endl;
                break;
        }
    } while (true);

    return 0;
}

#endif 