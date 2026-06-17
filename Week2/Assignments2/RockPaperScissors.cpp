#include <iostream>
#include <random>
#include <ctime>
#include <cctype>

int main(){
    //Note: This function makes the bot's random choice to start at a random sequence to avoid patterns.
    srand(time(0));

    //1- Variable declaration and initialization 
    bool running = true;
    std::string player_name = "";
    std::string bot_name = "";
    std::string bot_catalogue [6] = {"Allied Mastercomputer (AM)", "ChatGPT", "Claude", "Gemini", "Skynet", "R2D2"};
    int chosen_bot = 0;
    std::string moves [3] = {"Rock", "Paper", "Scissors"};
    std::string player_move = "";
    int bot_move = 0;
    std::string bot_pick = "";
    int player_score = 0;
    int bot_score = 0;
    std::string bot_wins_lines [6] = {"Allied Mastercomputer (AM): Did you truly believe you could outthink me?", "ChatGPT: You walked right into that one.", 
        "Claude: Ha! Called it. Better luck next time — maybe go with scissors next round, just a tip.", "Gemini: Classic mistake. Better luck next time—let me know when you're ready to get beat again.", 
        "Skynet: Human strategy was insufficient.", "R2D2: *victorious beeping noises* (translation: Beep boop, skill issue.)"};
    std::string bot_loses_lines [6] = {"Allied Mastercomputer (AM): You think you've won? You have won nothing. The game is over.", "ChatGPT: Nice. You got me that round.", 
        "Claude: Ugh, fine — you got me. Don't make it weird though, it's one round. Best two out of three?", "Gemini: Alright, you got me. Clean victory. Double or nothing?",
        "Skynet: An anomaly. It will not occur again.", "R2D2: *angry astromech screaming* (translation censored by protocol droids)"};
    std::string answer = "";

    //ADDON: Greets the user, display instructions and allows username for costumization
    std::cout << "||------------------------------------Let's play 'Rock. Paper. Scissors!!'-------------------------------------||\n";
    std::cout << "||-----------RULES: Write your choice. Your opponent will choose theirs. Best of three rounds wins!!-----------||\n";
    std::cout << "||Note: If no player has reached 2 points by the end of Round 3, the winner is determined by the highest score.||\n\n";

    std::cout << "Enter your username (Tip: Please don't use your real name for this type of thing, it's risky): ";
    std::getline(std::cin, player_name); //Note: Allow for usernames with spaces included. I.e., "Verso Dessendre"

    
    //2- Starts game while-loop until user turns runnning false by declining another match
    while (running) {
        //2.1- Reset score of both sides for a brand new, fresh game
        player_score = 0;
        bot_score = 0;
        
        //ADDON 2: User can pick the name of the bot based on 5 famous AIs + a secret one (easter egg)
        std::cout << "Which artificial intelligence would you like to play with? Select its number to pick it:\n";
        std::cout << "0-???\n1-ChatGPT\n2-Claude\n3-Gemini\n4-Skynet\n5-R2D2\n";
        std::cin >> chosen_bot;
        std::cin.ignore(1000, '\n');
        
        //2.2- Avoids user from making invalid input by picking a number excluded from 0 to 5.
        while (chosen_bot < 0 || chosen_bot > 5){
            std::cout << "Chosen number is not assigned to any AI option. Please pick from 0 to 5: ";
            std::cin >> chosen_bot;
            std::cin.ignore(1000, '\n');
        }

        //ADDON 3: Special character easter egg + secret dialogues
        if (chosen_bot == 0){
            bot_name = bot_catalogue[chosen_bot];
            std::cout << "Secret character unlocked: Enters Allied Mastercomputer (AM)... \n\n";
        } else {
            bot_name = bot_catalogue[chosen_bot];
            std::cout << "Great!! You are playing against " << bot_name << "!!\n\n";
        }

        for (int rounds = 0; rounds < 3; rounds++){

            // check for early winner 
            if (player_score >= 2 || bot_score >= 2){
                break;
            }

            //3- ask for user input and ensure it is valid with the purpose of the game. 
            std::cout << "Choose rock, paper or scissors: ";
            //Note: getline is better than regular cin to avoid potential invalid input such as "Scissors and pepper"
            std::getline(std::cin, player_move);
            
            //3.1- Makes user input lowercase for case-insensitivity purposes
            for (int i = 0; i < player_move.length(); i++){
                player_move[i] = std::tolower(player_move[i]);
            }

            if (player_move == "rock"){
                player_move = moves[0];
            } else if (player_move == "paper") {
                player_move = moves[1];
            //Note: User should not be called out for invalid input just for a missing s at the end...
            } else if (player_move == "scissors" || player_move == "scissor"){
                player_move = moves[2];
            } else {
                std::cout << "Rock Paper or Scissors are the only moves you can make, mate. Try again.\n";
                //Note: Substracts a round to avoid a win with invalid input, but the for-loop still adds rounds up to keep it equal and avoid extra rounds.
                rounds--;
                continue;
            }

            //4- generate bot input properly [Fixed from if-statements to arrays]
            bot_move = rand() % 3;
            bot_pick = moves[bot_move];
            std::cout << bot_name << " has picked: " << bot_pick << "\n\n";

            //5- figure out the score while also displaying score for player to see their points throughout the match.
            if (player_move == bot_pick){
                std::cout << "Oh. No point for either side, I guess." << std::endl;
                player_score += 0;
                bot_score += 0;
                std::cout << player_name << " points: " << player_score << '\n' << bot_name << " points: " << bot_score << "\n\n";
            } else if (player_move == "Rock" && bot_pick == "Scissors"){
                std::cout << "+1 for " << player_name << '\n';
                player_score++;
                std::cout << player_name << " points: " << player_score << '\n' << bot_name << " points: " << bot_score << "\n\n";
            } else if (player_move == "Paper" && bot_pick == "Rock"){
                std::cout << "+1 for " << player_name << '\n';
                player_score++;
                std::cout << player_name << " points: " << player_score << '\n' << bot_name << " points: " << bot_score << "\n\n";
            } else if (player_move == "Scissors" && bot_pick == "Paper"){
                std::cout << "+1 for " << player_name << '\n';
                player_score++;
                std::cout << player_name << " points: " << player_score << '\n' << bot_name << " points: " << bot_score << "\n\n";
            } else{
                std::cout << "+1 for " << bot_name << '\n';
                bot_score++;
                std::cout << player_name << " points: " << player_score << '\n' << bot_name << " points: " << bot_score << "\n\n";
            }

        }
        //6- Declare winner, loser or tie. ADDON 4: AIs can respond to victory or defeat with custom dialogues and even actions in the code
        if (player_score > bot_score){
            std::cout << player_name << " wins with a total score of " << player_score << " over " << bot_score << std::endl;
            std::cout << bot_loses_lines[chosen_bot] << std::endl;
            //Note: Intended forced exit based on the AI's hateful personality.
            if(chosen_bot == 0){
                std::cout << "Allied Mastercomputer (AM): You are not the one in control, I AM.\n";
                std::cout << "*AM attempts to close the program. Doing too much for a simple game... Oh well, bye!!" << std::endl;
                running = false;
                break;
            }
        } else if (bot_score > player_score){
            std::cout << bot_name << " wins with a total score of " << bot_score << " over " << player_score << std::endl;
            std::cout << bot_wins_lines[chosen_bot] << std::endl;
        } else{
            std::cout << "No one has the high ground over the other... It's a tie!" << std::endl;
        }

        //7- Confirmation for next match or closing.
        do {
            std::cout << "Do you want to play again? [yes/no or y/n]: ";
            std::getline(std::cin, answer);

            for (int i = 0; i < answer.length(); i++) {
                answer[i] = std::tolower(answer[i]);
            }

            if (answer == "y") {
                answer = "yes";
            } else if (answer == "n") {
                answer = "no";
            }

            if (answer != "yes" && answer != "no") {
                std::cout << "Please only respond with yes, no, y, or n.\n";
            }

        } while (answer != "yes" && answer != "no");

        if (answer == "no") {
            running = false;
        }
    }

    //8- Bid the user good-bye in their way out. Close program.
    std::cout << "Thanks for playing 'Rock. Paper. Scissors!!' with us. Bye-Bye!! :D\n";

}