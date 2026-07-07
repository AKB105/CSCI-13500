#include <cctype>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

//ADDON: Greets the user, display instructions and allows username for costumization
void DisplayWelcomeMessage() {
    std::cout << "||------------------------------------Let's play 'Rock. Paper. Scissors!!'-------------------------------------||\n";
    std::cout << "||-----------RULES: Write your choice. Your opponent will choose theirs. Best of three rounds wins!!-----------||\n";
    std::cout << "||Note: If no player has reached 2 points by the end of Round 3, the winner is determined by the highest score.||\n\n";
}

//Note: Allow for usernames with spaces included. I.e., "Verso Dessendre"
std::string GetPlayerName() {
    std::string player_name = "";

    std::cout << "Enter your username (Tip: Please don't use your real name for this type of thing, it's risky): ";
    std::getline(std::cin, player_name);

    return player_name;
}

//Makes user input lowercase for case-insensitivity purposes
std::string ToLowercase(std::string text) {
    int text_length = text.length();

    for (int i = 0; i < text_length; i++) {
        text[i] = std::tolower(text[i]);
    }

    return text;
}

//ADDON 2: User can pick the name of the bot based on 5 famous AIs + a secret one (easter egg)
int ChooseBot() {
    int chosen_bot = 0;

    std::cout << "Which artificial intelligence would you like to play with? Select its number to pick it:\n";
    std::cout << "0-???\n1-ChatGPT\n2-Claude\n3-Gemini\n4-Skynet\n5-R2D2\n";
    std::cin >> chosen_bot;
    std::cin.ignore(1000, '\n');

    //2.2- Avoids user from making invalid input by picking a number excluded from 0 to 5.
    while (chosen_bot < 0 || chosen_bot > 5) {
        std::cout << "Chosen number is not assigned to any AI option. Please pick from 0 to 5: ";
        std::cin >> chosen_bot;
        std::cin.ignore(1000, '\n');
    }

    return chosen_bot;
}

//ADDON 3: Special character easter egg + secret dialogues
std::string GetBotName(const std::string bot_catalogue[], int chosen_bot) {
    std::string bot_name = bot_catalogue[chosen_bot];

    if (chosen_bot == 0) {
        std::cout << "Secret character unlocked: Enters Allied Mastercomputer (AM)... \n\n";
    } else {
        std::cout << "Great!! You are playing against " << bot_name << "!!\n\n";
    }

    return bot_name;
}

//Ask for user input and ensure it is valid with the purpose of the game. 
std::string GetPlayerMove(const std::string moves[]) {
    std::string player_move = "";
    bool valid_move = false;
    
    while (!valid_move) {
        std::cout << "Choose rock, paper or scissors: ";
        //Note: getline is better than regular cin to avoid potential invalid input such as "Scissors and pepper"
        std::getline(std::cin, player_move);

        player_move = ToLowercase(player_move);

        if (player_move == "rock") {
            player_move = moves[0];
            valid_move = true;
        } else if (player_move == "paper") {
            player_move = moves[1];
            valid_move = true;
        } else if (player_move == "scissors" || player_move == "scissor") {
            player_move = moves[2];
            valid_move = true;
        } else {
            std::cout << "Rock Paper or Scissors are the only moves you can make, mate. Try again.\n";
        }
    }

    return player_move;
}

//Generate bot input properly [Fixed from if-statements to arrays. Updated: From arrays in main to a function!!]
std::string GenerateBotMove(const std::string moves[]) {
    int bot_move = rand() % 3;
    return moves[bot_move];
}

void DisplayScore(const std::string player_name, const std::string bot_name,
                  int player_score, int bot_score) {
    std::cout << player_name << " points: " << player_score << '\n'
              << bot_name << " points: " << bot_score << "\n\n";
}

//Figure out the score while also displaying score for player to see their points throughout the match.
void UpdateScore(const std::string player_name, const std::string bot_name,
                 const std::string player_move, const std::string bot_pick,
                 int& player_score, int& bot_score) {
    if (player_move == bot_pick) {
        std::cout << "Oh. No point for either side, I guess." << std::endl;
    } else if (player_move == "Rock" && bot_pick == "Scissors") {
        std::cout << "+1 for " << player_name << '\n';
        player_score++;
    } else if (player_move == "Paper" && bot_pick == "Rock") {
        std::cout << "+1 for " << player_name << '\n';
        player_score++;
    } else if (player_move == "Scissors" && bot_pick == "Paper") {
        std::cout << "+1 for " << player_name << '\n';
        player_score++;
    } else {
        std::cout << "+1 for " << bot_name << '\n';
        bot_score++;
    }

    DisplayScore(player_name, bot_name, player_score, bot_score);
}

void PlayRound(const std::string moves[], const std::string player_name,
               const std::string bot_name, int& player_score, int& bot_score) {
    std::string player_move = GetPlayerMove(moves);
    std::string bot_pick = GenerateBotMove(moves);

    std::cout << bot_name << " has picked: " << bot_pick << "\n\n";

    UpdateScore(player_name, bot_name, player_move, bot_pick, player_score, bot_score);
}

//Declare winner, loser or tie. ADDON 4: AIs can respond to victory or defeat with custom dialogues and even actions in the code
void DisplayMatchResults(const std::string player_name, const std::string bot_name,
                         int chosen_bot, int player_score, int bot_score,
                         const std::string bot_wins_lines[],
                         const std::string bot_loses_lines[],
                         bool& running) {
    if (player_score > bot_score) {
        std::cout << player_name << " wins with a total score of " << player_score << " over " << bot_score << std::endl;
        std::cout << bot_loses_lines[chosen_bot] << std::endl;

        if (chosen_bot == 0) {
            std::cout << "Allied Mastercomputer (AM): You are not the one in control, I AM.\n";
            std::cout << "*AM attempts to close the program. Doing too much for a simple game... Oh well, bye!!" << std::endl;
            running = false;
        }
    } else if (bot_score > player_score) {
        std::cout << bot_name << " wins with a total score of " << bot_score << " over " << player_score << std::endl;
        std::cout << bot_wins_lines[chosen_bot] << std::endl;
    } else {
        std::cout << "No one has the high ground over the other... It's a tie!" << std::endl;
    }
}

//Confirmation for next match or closing.
bool AskToPlayAgain() {
    std::string answer = "";

    do {
        std::cout << "Do you want to play again? [yes/no or y/n]: ";
        std::getline(std::cin, answer);

        answer = ToLowercase(answer);

        if (answer == "y") {
            answer = "yes";
        } else if (answer == "n") {
            answer = "no";
        }

        if (answer != "yes" && answer != "no") {
            std::cout << "Please only respond with yes, no, y, or n.\n";
        }

    } while (answer != "yes" && answer != "no");

    return answer == "yes";
}

int main() {
    //Note: This function makes the bot's random choice to start at a random sequence to avoid patterns.
    srand(time(0));

    //Variables declaration and initialization 
    bool running = true;
    std::string player_name = "";
    std::string bot_name = "";
    std::string bot_catalogue[6] = {"Allied Mastercomputer (AM)", "ChatGPT", "Claude", "Gemini", "Skynet", "R2D2"};
    int chosen_bot = 0;
    std::string moves[3] = {"Rock", "Paper", "Scissors"};
    int player_score = 0;
    int bot_score = 0;
    std::string bot_wins_lines[6] = {
        "Allied Mastercomputer (AM): Did you truly believe you could outthink me?",
        "ChatGPT: You walked right into that one.",
        "Claude: Ha! Called it. Better luck next time -- maybe go with scissors next round, just a tip.",
        "Gemini: Classic mistake. Better luck next time -- let me know when you're ready to get beat again.",
        "Skynet: Human strategy was insufficient.",
        "R2D2: *victorious beeping noises* (translation: Beep boop, skill issue.)"};
    std::string bot_loses_lines[6] = {
        "Allied Mastercomputer (AM): You think you've won? You have won nothing. The game is over.",
        "ChatGPT: Nice. You got me that round.",
        "Claude: Ugh, fine -- you got me. Don't make it weird though, it's one round. Best two out of three?",
        "Gemini: Alright, you got me. Clean victory. Double or nothing?",
        "Skynet: An anomaly. It will not occur again.",
        "R2D2: *angry astromech screaming* (translation censored by protocol droids)"};

    DisplayWelcomeMessage();
    player_name = GetPlayerName();

    //Starts game while-loop until user turns runnning false by declining another match
    while (running) {
        //2.1- Reset score of both sides for a brand new, fresh game
        player_score = 0;
        bot_score = 0;

        chosen_bot = ChooseBot();
        bot_name = GetBotName(bot_catalogue, chosen_bot);

        for (int rounds = 0; rounds < 3; rounds++) {
            if (player_score >= 2 || bot_score >= 2) {
                break;
            }

            PlayRound(moves, player_name, bot_name, player_score, bot_score);
        }

        DisplayMatchResults(player_name, bot_name, chosen_bot, player_score, bot_score,
                            bot_wins_lines, bot_loses_lines, running);

        if (running) {
            running = AskToPlayAgain();
        }
    }

    //Bid the user good-bye in their way out. Close program.
    std::cout << "Thanks for playing 'Rock. Paper. Scissors!!' with us. Bye-Bye!! :D\n";

    return 0;
}
