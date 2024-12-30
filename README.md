# Simple Online Polling System

A polling system implemented in C++ where users can vote for their favorite cricketer from a predefined list of options. After voting, users can view the current poll results, which show the number of votes for each option and the corresponding percentages. The poll is active until a predefined expiration date, after which users can no longer vote.

## Output:

![image](poll.png)

## Features
- Users can vote for their favorite cricketer from a list of options.
- Voting is limited to one vote per user.
- Results are updated after each vote and displayed in percentage format.
- Poll expiration is set to a specific date.
- Colorful, professional, and user-friendly terminal interface.

## Poll Options
1. **MS Dhoni** - The legendary former captain of India.
2. **Virat Kohli** - The modern-day cricketing icon.
3. **Rohit Sharma** - The hitman of Indian cricket.
4. **Shikhar Dhawan** - The dashing opener of India.

## Poll Expiration
The poll expires on **2024-12-31**. After this date, users will no longer be able to vote.

## File Structure
- `poll_results.txt`: Stores the vote counts for each option.
- `users_voted.txt`: Keeps track of users who have already voted to prevent multiple votes from the same user.
- `poll.cpp`: Main C++ program file that handles the polling logic.

## Setup Instructions
1. Ensure you have a C++ compiler installed (e.g., GCC or Clang).
2. Clone or download the repository to your local machine.

## How to Run the Program
1. Clone The Repo:
   ```bash
   git clone https://github.com/GET-UNKNOWN-ERR0R/online-polling-system.git
   ```
   ```bash
   cd online-polling-system
   ```
2. Run The Program:
   ```bash
   g++ -o poll poll.cpp
   ```
   ```bash
   ./poll
   ```
## License    
