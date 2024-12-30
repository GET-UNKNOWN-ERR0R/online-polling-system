#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

const int NUM_OPTIONS = 4;
const string pollFile = "poll_results.txt";
const string usersFile = "users_voted.txt"; 
const string expirationDate = "2024-12-31"; 

struct PollOption {
    string name;
    string description;
    int votes;
};

// ANSI color codes for different outputs
const string COLOR_RESET = "\033[0m";
const string COLOR_PROMPT = "\033[1;36m"; // Cyan for prompts
const string COLOR_HEADER = "\033[1;32m"; // Green for headers
const string COLOR_OPTIONS = "\033[1;33m"; // Yellow for options
const string COLOR_RESULT = "\033[1;34m"; // Blue for results
const string COLOR_VOTE = "\033[1;35m"; // Magenta for votes and percentages
const string COLOR_ERROR = "\033[1;31m"; // Red for error messages
const string COLOR_SUCCESS = "\033[1;37m"; // White for success messages

void displayPollOptions(PollOption options[]) {
    cout << COLOR_HEADER << "Please choose your favorite cricketer:\n" << COLOR_RESET;
    for (int i = 0; i < NUM_OPTIONS; ++i) {
        cout << COLOR_OPTIONS << i + 1 << ". " << options[i].name << " - " << options[i].description << "\n" << COLOR_RESET;
    }
}

void displayResults(PollOption options[], int totalVotes) {
    cout << "\n" << COLOR_HEADER << "Current Poll Results:\n" << COLOR_RESET;
    for (int i = 0; i < NUM_OPTIONS; ++i) {
        double percentage = (totalVotes == 0) ? 0 : (double(options[i].votes) / totalVotes) * 100;
        cout << COLOR_RESULT << options[i].name << ": " << COLOR_VOTE << options[i].votes << " votes" << COLOR_RESET 
             << " (" << COLOR_VOTE << fixed << setprecision(2) << percentage << "%" << COLOR_RESET << ")\n";
    }
}

void loadPollResults(PollOption options[]) {
    ifstream file(pollFile);
    if (file.is_open()) {
        for (int i = 0; i < NUM_OPTIONS; ++i) {
            file >> options[i].votes;
        }
        file.close();
    } else {
        for (int i = 0; i < NUM_OPTIONS; ++i) {
            options[i].votes = 0;
        }
    }
}

void savePollResults(PollOption options[]) {
    ofstream file(pollFile);
    if (file.is_open()) {
        for (int i = 0; i < NUM_OPTIONS; ++i) {
            file << options[i].votes << "\n";
        }
        file.close();
    } else {
        cout << COLOR_ERROR << "Error saving poll results.\n" << COLOR_RESET;
    }
}

bool isPollExpired() {
    time_t now = time(0);
    struct tm expiryTime = {};
    strptime(expirationDate.c_str(), "%Y-%m-%d", &expiryTime);
    time_t expiry = mktime(&expiryTime);
    return now > expiry;
}

bool hasUserVoted(const string& username) {
    ifstream file(usersFile);
    string line;
    while (getline(file, line)) {
        if (line == username) {
            return true;
        }
    }
    return false;
}

void markUserAsVoted(const string& username) {
    ofstream file(usersFile, ios::app);
    if (file.is_open()) {
        file << username << "\n";
        file.close();
    } else {
        cout << COLOR_ERROR << "Error marking user as voted.\n" << COLOR_RESET;
    }
}

int main() {
    PollOption options[NUM_OPTIONS] = {
        {"MS Dhoni", "The legendary former captain of India.", 0},
        {"Virat Kohli", "The modern-day cricketing icon.", 0},
        {"Rohit Sharma", "The hitman of Indian cricket.", 0},
        {"Shikhar Dhawan", "The dashing opener of India.", 0}
    };
    string username;
    int userVote;
    int totalVotes = 0;

    loadPollResults(options);

    if (isPollExpired()) {
        cout << COLOR_ERROR << "The poll has expired. You can no longer vote.\n" << COLOR_RESET;
        return 0;
    }

    cout << COLOR_PROMPT << "Enter your username: " << COLOR_RESET;
    cin >> username;

    if (hasUserVoted(username)) {
        cout << COLOR_SUCCESS << "You have already voted! Thank you for participating.\n" << COLOR_RESET;
        return 0;
    }

    displayPollOptions(options);

    cout << COLOR_PROMPT << "Enter the number of your choice (1-4): " << COLOR_RESET;
    cin >> userVote;

    if (userVote < 1 || userVote > NUM_OPTIONS) {
        cout << COLOR_ERROR << "Invalid choice. Please enter a number between 1 and 4.\n" << COLOR_RESET;
    } else {
        options[userVote - 1].votes++;
        totalVotes++;

        savePollResults(options);
        markUserAsVoted(username);

        cout << COLOR_SUCCESS << "Thank you for voting! Here's the updated results:\n" << COLOR_RESET;
        displayResults(options, totalVotes);
    }

    return 0;
}
