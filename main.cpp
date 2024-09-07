#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;

struct User {
    string username;
    int maxWpm;
};

bool compareWpm(const User& a, const User& b) {
    return a.maxWpm > b.maxWpm; // Sort in descending order
}

void leaderboard() {
    ifstream file("credentials.txt");
    string line;

    vector<User> users;

    // Read the file and parse each line
    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream iss(line);
            string username, password;
            int maxWpm;

            if (iss >> username >> password >> maxWpm) {
                users.push_back({username, maxWpm});
            }
        }
        file.close();
    } else {
            cout << "Unable to open file." << std::endl;
        return;
    }

    // Sort the users by maxWpm in descending order
      sort(users.begin(), users.end(), compareWpm);

    // Display the leaderboard
      cout << "Rank\tUsername\tMax WPM" << std::endl;
      cout << "---------------------------------" << std::endl;
    int rank = 1;
    for (const auto& user : users) {
        cout << rank++ << "\t" << user.username << "\t\t" << user.maxWpm << endl;
    }
}

 void checkAndUpdateCredentials(const string& username, const string& password, int currentWPM) {
    // Open the file to read and write
    fstream file("credentials.txt", ios::in | ios::out);
    string line, fileUsername, filePassword;
    int fileWPM;
    vector<string> fileContents;

    if (!file.is_open()) {
        cout << "Unable to open credentials file." << endl;
        
    }

    // Read the file line by line
    while (getline(file, line)) {
        istringstream iss(line);
        if (iss >> fileUsername >> filePassword >> fileWPM) {
            // Check if username and password match
            if (fileUsername == username && filePassword == password) {
                if (currentWPM > fileWPM) {
                    // Update the WPM if the current one is greater
                    fileWPM = currentWPM;
                    // Replace the line with the updated WPM value
                    stringstream updatedLine;
                    updatedLine << fileUsername << " " << filePassword << " " << fileWPM;
                    fileContents.push_back(updatedLine.str());
                } else {
                    // Keep the original line if no update is needed
                    fileContents.push_back(line);
                }
            } else {
                // Keep the original line if the username/password don't match
                fileContents.push_back(line);
            }
        }
    }

    // Close the file after reading
    file.close();

    // Open the file again for writing
    ofstream outFile("credentials.txt", ios::trunc);
    if (!outFile.is_open()) {
        cout << "Unable to open credentials file for writing." << endl;
       
    }

    // Write the updated content back to the file
    for (const string& contentLine : fileContents) {
        outFile << contentLine << endl;
    }

    outFile.close();
  
}

void practice(const string& username, const string& password) {
    // Step 1: Read all lines from sample.txt
    vector<string> lines;
    string line;
    ifstream file("sample.txt");

    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
        return;
    }

    // Step 2: Check if there are lines to practice
    if (lines.empty()) {
        cout << "No lines to practice." << endl;
        return;
    }
          int num_lines;
          cout<<"How many lines you want(Each lines contains 10 words)"<<endl;
           cout<<"1 line(10 words)"<<endl;
           cout<<"2 lines(20 words)"<<endl;
           cout<<"3 lines (30 words)"<<endl;
           cout<<"4 lines (40 words)"<<endl;
           cout<<"5 lines (50 words)"<<endl;
           cout<<"choose any number for 70 words"<<endl;
           cin>>num_lines;
           cin.ignore();
           
             srand(static_cast<unsigned int>(time(0)));

    // Perform the shuffle
    for (size_t i = 0; i < lines.size(); ++i) {
        // Generate a random index to swap with
        size_t randomIndex = rand() % lines.size();
        swap(lines[i], lines[randomIndex]);
    }
            string stored ;
           switch(num_lines){
            case 1:  
                     stored = lines[0];
                     break;
            case 2:
                     stored = lines[0] + lines[1];
                     break;
            case 3:
                     stored = lines[0] + lines[1] + lines[2];
                     break;
            case 4 :
                     stored = lines[0] + lines[1] + lines[2] + lines[3];
                     break;
           case 5  :
                       stored = lines[0] + lines[1] + lines[2] + lines[3] + lines[4] ;
                       break;
           default :
                       stored = lines[0] + lines[1] + lines[2] + lines[3] + lines[4] + lines[5]  + lines[6];
                       break;
              };
              
          
    // Step 3: Shuffle the lines and pick one line for practice
   // random_shuffle(lines.begin(), lines.end());


   // string stored = lines[0];
    cout << "Type the following line:\n" << stored << endl;

    // Typing practice
    string typed;
    auto start = chrono::high_resolution_clock::now();
    getline(cin, typed); // Read a single line from user input
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double seconds = duration.count() / 1000000.0;

    cout << endl;
    cout << "You have typed: " << endl;
    cout << "\t" << typed << endl;

    cout << "Total time taken: " << seconds << " seconds" << endl;

    // Word counting
    int word_count = 0;
    bool in_word = false;

    for (char c : typed) {
        if (isspace(c)) {
            if (in_word) {
                word_count++;
                in_word = false;
            }
        } else {
            in_word = true;
        }
    }
    if (in_word) {
        word_count++;
    }

    // Calculate WPM
    double minutes = seconds / 60.0;
    double wpm = (minutes > 0) ? (word_count / minutes) : 0; // Prevent division by zero

    cout << "Your typing speed: " << wpm << " WPM" << endl;

    // Calculate wrong characters
    vector<char> wrong;
    int correct_characters = 0;
    int total_characters = stored.length();

    for (int i = 0; i < total_characters; i++) {
        if (i >= typed.size()) {
            // User typed fewer characters than stored
            wrong.push_back(stored[i]);
        } else if (stored[i] != typed[i]) {
            wrong.push_back(stored[i]); // Store the correct character that was missed
        } else {
            correct_characters++;
        }
    }

    // If the typed input is longer, add extra characters as wrong
    if (typed.size() > stored.size()) {
        for (size_t i = stored.size(); i < typed.size(); i++) {
            wrong.push_back(typed[i]);
        }
    }

    cout << "You have typed wrong characters: " << endl;
    for (char c : wrong) {
        cout << c << " ";
    }
    cout << endl;

    // Calculate typing efficiency
    double efficiency = (total_characters > 0) ? (static_cast<double>(correct_characters) / total_characters) * 100 : 0;
    cout << "Typing efficiency: " << efficiency << "%" << endl;
    
       if(username != "null" && password != "null"){
      
         checkAndUpdateCredentials(username,password,wpm);
     }
     
  }

// Function to check if credentials are correct
bool checkCredentials(const string& username, const string& password) {
    ifstream file("credentials.txt");
    string line, fileUsername, filePassword;

    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream iss(line);
            if (iss >> fileUsername >> filePassword) {
                if (fileUsername == username && filePassword == password) {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
    } else {
        cout << "Unable to open credentials file." << endl;
    }
    
    return false;
}

// Function to handle login
void login() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Clear the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Check if the credentials are correct
    if (checkCredentials(username, password)) {
        cout << "Login successful!" << endl;
        practice(username , password); // Redirect to practice function after successful login
    } else {
        cout << "Invalid username or password. Please try again." << endl;
    }
}

// Function to handle signup
void signup() {
    string username, password, confirmPassword;

    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter a new password: ";
    cin >> password;
    cout << "Confirm your password: ";
    cin >> confirmPassword;

    // Clear the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Check if passwords match
    if (password != confirmPassword) {
        cout << "Passwords do not match. Please try again." << endl;
        return;
    }

    // Check if the username already exists
    ifstream file("credentials.txt");
    string line, fileUsername;

    while (getline(file, line)) {
        istringstream iss(line);
        if (iss >> fileUsername) {
            if (fileUsername == username) {
                cout << "Username already exists. Please choose a different username." << endl;
                file.close();
                return;
            }
        }
    }
    file.close();

    // Add new user to the file
    ofstream outfile("credentials.txt", ios::app);
    if (outfile.is_open()) {
        outfile << username << " " << password << " "<< "0" << endl;
        outfile.close();
        cout << "Signup successful! You can now log in with your new credentials." << endl;
    } else {
        cout << "Unable to open credentials file for writing." << endl;
    }
}

void choices() {
    int choice = 0;

    cout << "Choose the Features of software: " << endl;
    cout << "1. Practice purpose" << endl;
    cout << "2. Login" << endl;
    cout << "3. Signup" << endl;
    cout << "4. Show leaderboard"<<endl;
    cout << "Enter your choice: ";
    cin >> choice;

    // Clear the newline character left in the buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
     string s = "null";

    switch (choice) {
        case 1:
            cout << "Page redirected for practice" << endl;
               
            practice(s,s);
            break;
        case 2:
            cout << "Page redirected for Login" << endl;
            login();
            break;
        case 3:
            cout << "Page redirected for Signup" << endl;
            signup();
            break;
       case 4:
            cout << endl<<"Page redirected for Userboard" << endl;
             leaderboard();
            break;
            
        default:
            cout << "Invalid choice. Please try again." << endl;
            choices(); // Retry if invalid choice
            break;
    }
}

int main() {
    cout << "      __________________________________________________   " << endl;
    cout << "   |                                                  | " << endl;
    cout << "   |                                                  |  " << endl;
    cout << "   |                                                  |  " << endl;
    cout << "   |                                                  |" << endl;
    cout << "   |          Welcome to Typing software              |" << endl;
    cout << "   |                                                  |" << endl;
    cout << "   |                                                  |" << endl;
    cout << "   |                                                  |" << endl;
    cout << "   |                                                  |" << endl;
    cout << "   |                                                  |" << endl;
    cout << "    ___________________________________________________ " << endl;
    cout << endl;

    choices();

    return 0;
}

