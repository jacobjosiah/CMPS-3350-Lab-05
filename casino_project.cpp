#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm> // for std::transform

using namespace std;

struct Player
{
    string name;
    double money;
};

std::string drawCard(std::vector<std::string> &deck);
int cardValue(const std::string &card);
void playBlackjack(Player &player);


double updateMoney(double amount, double & m) { // Changed return type to double
    m += amount;
    return m; // Return updated balance
}

bool canAfford(double amount, double m) { return m >= amount; } // Changed amount type to double


void roulette_rules()
{
    cout << "\n\n====== Objective ====== \n\n - Your goal is to predict where the small ball will land on the spinning roulette wheel. You can place bets on different outcomes based on numbers, colors, and combinations.\n"
         << "\n\n====== Bet Types ======\n\n - Inside bets: Placed on specific numbers or small groups of numbers. This includes Straight (bet on a single number), Split (bet on two adjacent numbers), Street (three numbers in a row) "
         << " Corner (four numbers forming a square), and Six Line (six numbers in two adjacent rows).\n\n - Outside Bets: Placed on larger groups of numbers or characteristics. "
         << "This includes Red/Black, Odd/Even, High/Low (1-18/19-36) Dozens (1-12, 13-24, 25-36), and Columns (vertical columns of 12 numbers).\n\n";
  
}

void show_board()
{
    int count;
    cout << "\n~~~~~ Board ~~~~~";
    for (int i = 3; i > 0; i--)
    {
        count = i;
        cout << "\n---------------------------------\n";

        for (int j = 0; j < 12; j++)
        { 
            cout << "|" <<  count;
            count = count + 3;
        }
    }
    cout << "\n---------------------------------\n";

}

double calc_r_bet(string type, double bet, string choice)
{
    double amount;
    if (type == "o") // Outside Bets
    {
        if (choice == "a" || choice == "b" || choice == "c"  ) // Red/Black, Odd/Even, High/Low (1:1 payout)
            amount = bet * 2;

        else if (choice == "d" || choice == "e") // Dozens (1-12, 13-24, 25-36), Columns (vertical columns of 12 numbers) (1:2 payout)
            amount = bet * 3;
    }

    else if (type == "i") // Inside Bets
    {
        if (choice == "a") // Straight (single number) (35:1 payout)
            amount = bet + (bet * 35);

        else if (choice == "b") // Split (two adjacent numbers) (17:1 payout)
            amount = bet + (bet * 17);

        else if (choice == "c") // Street (three numbers in a row) (11:1 payout)
            amount = bet + (bet * 11);

        else if (choice == "d") // Corner (four numbers forming a square) (8:1 payout)
            amount = bet + (bet * 8);
        else if (choice == "e") // Six Line (six numbers in two adjacent rows) (5:1 payout)
            amount = bet + (bet * 5);
    }
    
    return amount;
}


double roulette(double m, string n)
{
    string c = "";
    string color;
    int picks[20];
    double money = m;
    double curr_bet, pot;
    bool valid = false;
    bool win = false;
    int outcome;

    while (!valid)
    {
        cout << "Welcome to Roulette! Would You like to view the rules? Yes(y) / No(n): ";
        cin >> c;
        valid = (c == "y" || c == "n" ? true : false);
    }

    if (c == "y")
    {
        roulette_rules();
        show_board();
    }

    do 
    { 
        do
        {
            color = "";
            cout << "\n\nTime to place your bets! Will you be placing a safer outside bet, or upping the steaks with an inside bet?\n\n";
            cout << "(o) - Outside Bet" << endl << "(i) - Inside Bet" << endl << "(h) - Help " << endl  << "(s) - Show Board " << endl;
            cout << endl << n << "'s cash: $" << money << "\n\n  -> ";
            cin >> c;

            if (c == "h")
            {
                roulette_rules();
            }
            else if (c == "s")
            {
                show_board();
            }
            valid = (c == "o" || c == "i" ? true : false);

        } while (!valid && c != "q"); // Repeats the bet screen if user needed to refer to help screen for assistance

        if (c == "o") // Outside bets (low risk - low reward)
        {
            do
            {
                cout << "\n\nChose a bet type \n\n a) Red/Black \t b) Odd/Even \t c) High/Low (1-18/19-36) \t d) Dozens (1-12, 13-24, 25-36) \t e) Columns (vertical columns of 12 numbers)\n -> ";
                cin >> c;
                cout << "\n\n\n";

            } while (!(c == "a" || c == "b" ||  c == "c" || c == "d" || c == "e"));

            do
            {
                cout << "\n\nHow much will you be playing this round? \n\nCurrent Balance: $" << money << "\nBet amount: $";
                cin >> curr_bet;
                cout << "\n\n\n";

                if (curr_bet < 5)
                    cout << "\n\nBet too low! \n\nEnter bet: $";

                else if (curr_bet > money)
                    cout << "\n\nYou know you don't have it like that! Try again: $";

            } while (curr_bet < 5 || curr_bet > money); // Loop to verify valid bet amount

            money = money - curr_bet;
            pot = calc_r_bet("o", curr_bet, c);
            
            if (c == "a") // Red/Black
            {
                while (c != "r" && c != "b")
                {
                    cout << "\nChoose a color: Red(r) or Black(b): "; // r = 0 ; b = 1
                    cin >> c;   
                }

                picks[0] = (c == "r" ? 0 : 1);
                outcome = rand() % 2; // Returns 1 or 0
                color = (outcome == 1 ? "black" : "red"); 
                win = (picks[0] == outcome ? true : false);

            }
            
            else if (c == "b") // Even/Odd Even = 0, odd = 1
            {
                while (c != "e" && c != "o")
                {
                    cout << "Even(e) or Odd(o)?: ";
                    cin >> c;
                }

                picks[0] = (c == "e" ? 0 : 1);
                outcome = rand() % 37;
                win =  ((picks[0] % 2) == (outcome % 2) ? true : false);
            } 

            else if (c == "c") // High/Low (1-18/19-36)
            {
                do 
                {
                    cout << "Enter a number. Low is 1 - 18, High is 19 - 36: "; 
                    cin >> picks[0];
                } while (picks[0] < 1 || picks[0] > 36);
                outcome = rand() % 37;

                if (outcome == 0)
                {
                    win = false;
                }

                else if ((outcome < 19 && picks[0] < 19) || (outcome > 18 && picks[0] > 18))
                {
                    win = true;
                }

                else
                {
                    win = false;
                }
            } 

            else if (c == "d") //Dozens (1-12, 13-24, 25-36)
            {
                do 
                {
                    cout << "Enter a number for within the range of the 3 dozens (1-12, 13-24, 25-36): "; 
                    cin >> picks[0];
                } while (picks[0] < 1 || picks[0] > 36);
                outcome = rand() % 37;

                if (outcome == 0)
                    win = false;

                else if (outcome < 13 && picks[0] < 13)
                    win = true;
                
                else if ((outcome > 12 && picks[0] > 12) && (outcome < 25 && picks[0] < 25))
                    win = true;

                else if (outcome > 24 && picks[0] > 24)
                    win = true;

                else
                    win = false;
            } 

            else if (c == "e") // Columns
            {
                do 
                {
                    cout << "Choose column 1, 2, or 3. \n1st column: 1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34\n\n"
                         << "2nd column: 2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35\n\n3rd column: 3, 6, 9, 12, 15, 18, 31, 24, 27, 30, 33, 36\n\n  -> "; 
                    cin >> picks[0];
                } while (picks[0] < 1 || picks[0] > 3);
                outcome = rand() % 37;
                win = false;

                if (picks[0] == 1)
                {
                    for (int i = 1; i < 35; i += 3)
                    {
                        if (i == outcome)
                            win = true;
                    }
                }
                
                else if (picks[0] == 2)
                {
                    for (int j = 2; j < 36; j += 3)
                    {
                        if (j == outcome)
                            win = true;
                    }
                }

                else if (picks[0] == 3)
                {
                    for (int k = 2; k < 37; k += 3)
                    {
                        if (k == outcome)
                            win = true;
                    }
                }
            } 
        }

        else if (c == "i") // Inside bets (High risk - High Reward)
        {
            cout << "\nChose a bet type \n\n a) Straight (single number) \t b) Split (two adjacent numbers) \t c) Street (three numbers in a row) \t d) Six Line (six numbers in two adjacent rows)\n ->";
            cin >> c;
            do
            {
                cout << "\n\nHow much will you wager? You chose high steaks, so bet like it. \nCurrent Balance: $" << money << "\nBet amount: $";
                cin >> curr_bet;

                if (curr_bet < 50)
                    cout << "\n\nDo not embarrass yourself!";

                else if (curr_bet > money)
                    cout << "\n\n\"YOUR CARD HAS DECLINED!!\" The dealer screams loudly. Try again";

            } while (curr_bet < 50 || curr_bet > money); // Loop to verify valid bet amount

            money = money - curr_bet;
            pot = calc_r_bet("i", curr_bet, c);

            if (c == "a") // Single Number
            {
                do
                {
                    cout << "Choose a number from 0 - 36: "; 
                    cin >> picks[0];
                } while (picks[0] < 0 || picks[0] > 36);

                outcome = rand() % 37; // Returns 0 to 36 
                win = (picks[0] == outcome ? true : false);
            }
            
            else if (c == "b") // Split
            {
                do
                {             
                    show_board();
                    valid = false;
                    do
                    { 
                        cout << "Enter two adjacent numbers: ";
                        cin >> picks[0] >> picks[1];  
                    } while ((picks[0] < 1 || picks[0] > 36) || (picks[1] < 1 || picks[1] > 36)); // While numbers picked are out of range

                    int diff = abs(picks[0] - picks[1]);
                    if (diff == 3)                    
                        valid = true;

                    else if ((diff == 1) && (((picks[0] - 1) / 3 == (picks[1] - 1) / 3)))
                    {
                        valid = true;
                    }
                    if (!valid)
                        cout << "\n\nInvalid split\n";
                } while (!valid);
                outcome = rand() % 37; // Returns 0 to 36 
                win = ((picks[0] == outcome || picks[1] == outcome) ? true : false);
            } 

            else if (c == "c") // Street
            {
                show_board();
                win = false;
                do
                { 
                    cout << "Choose a street 1-12, with street 1 being (1, 2, 3): ";
                    cin >> picks[0];  
                } while ((picks[0] < 1 || picks[0] > 12)); // While numbers picked are out of range
                outcome = rand() % 37;

                for (int i = 0; i < 3; i++)
                {
                    if ((picks[0] * 3) - i == outcome) // Checks the 3 numbers on a street for bet
                        win = true; 
                }  
            } 

            else if (c == "d") // Six Line
            {
                show_board();
                win = false;
                do
                { 
                    cout << "\nChoose a section 1-6.  \nSection 1: (1, 2, 3, 4, 5, 6) \nSection 2: (7, 8, 9, 10, 11, 12) \nSection 3: (13, 14, 15, 16 17, 18 \n"
                         << "Section 4: (19, 20, 21, 22, 23 ,24) \nSection 5: (25, 26, 27, 28, 29, 30) \nSection 6: (31. 32. 33. 34. 35. 36)\n  -> ";
                    cin >> picks[0];  
                } while ((picks[0] < 1 || picks[0] > 6)); // While numbers picked are out of range
                outcome = rand() % 37;

                for (int i = 0; i < 6; i++)
                {
                    if ((picks[0] * 6) - i == outcome)
                        win = true;
                }  
            } 

        }

        if (c != "q")
        {
            cout << "\n\n---------------------------\n\n\t Roll: ";
            if (color == "")
                cout << outcome;
            else
                cout << color;
            
            cout << " \n\n---------------------------\n";

            if (win)
            {
                cout << "\nCongrats " << n << "! You won $" << pot << endl;
                money = money + pot; 
            }

            else
            {
                cout << "You lost! Better luck next turn" << endl;
            }
        }

    } while (money > 0 && c != "q");
    return money;

}
   
double slots1(double m)
{
    string symbol[10] = {"@", "#", "$", "&", "*", "|", "~", "()", "?", "!"};
    int index = rand() % 10;
    string slot1, slot2, slot3;
    int money = m;
    int bet;

    do
    {
        cout << "\n\nWelcome to Silver Slots!\n\nPlease enter a bet amount. or enter 0 to exit\nYour money: ";
        cout << money << "\n  -> ";
        cin >> bet;

        if (bet > 0 && bet < money)
        {
            money = money - bet;
            int bet = bet * 3;

            index = rand() % 10;
            slot1 = symbol[index];

            index = rand() % 10;
            slot2 = symbol[index];

            index = rand() % 10;
            slot3 = symbol[index];

            cout << "\n--------------------------\n\t" << slot1 << "  " << slot2 << "  " << slot3 << "\n--------------------------\n";
            if (slot1 == slot2 && slot2 == slot3)
            {
                money = money + bet;
                cout << "You Won! Current balance: " << money << endl;
            }
            else
            {
                cout << "Sorry, you lost!\n";
            }

        }
    } while (money > 0 && bet > 0);
    return money;

}

int main()
{
    Player p1;
    string choice;
    p1.money = 5000;
    srand(time(NULL));
    
    cout << "\nWelcome to AJ's Aces! Who will be playing today? : ";
    cin >> p1.name;

    do
    {  
        cout << "You currently have $" << p1.money << " to spend. \n\n";
        cout << "What game would you like to play? Blackjack(b), Silver Slots(s), Other_slot(o) Roulette(r), or quit(q)? ";
        cin >> choice;

      
        if (choice == "b")
            playBlackjack(p1);

        else if (choice == "s")
            p1.money = slots1(p1.money);

        else if (choice == "0")
            p1.money = slots1(p1.money);

        else if (choice == "r")
            p1.money = roulette(p1.money, p1.name);

    } while (choice != "q" && p1.money > 0);

    return 0;
}


void playBlackjack(Player &player) {
    const double startingMoney = 5000.0; // Changed startingMoney to double

    std::vector<std::string> deck = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    while (player.money > 0) {
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Welcome to Blackjack, " << player.name << "! Your balance: $" << player.money
                  << std::endl;
        double buyIn = 0; // Changed buyIn type to double
        if (!canAfford(100, player.money)) {
            std::cout << "Sorry, you don't have enough money to continue playing." << std::endl;
            break;
        }

        do
        {
            std::cout << "Enter your bet amount (minimum $100, 0 to exit): ";
            std::cin >> buyIn;
        } while ((buyIn < 100 || buyIn > player.money) && buyIn != 0);

        if (buyIn <= 0) {
            std::cout << "Thanks for playing!" << std::endl;
            break;
        } else if (!canAfford(buyIn, player.money)) {
            std::cout << "Insufficient funds. Please enter a valid bet amount." << std::endl;
            continue;
        }

        Player currentPlayer = player;
        updateMoney(-buyIn, currentPlayer.money);

        int playerScore = 0;
        bool doubledDown = false;

        // Deal cards
        std::string playerCard1 = drawCard(deck);
        std::string playerCard2 = drawCard(deck);

        std::cout << "Your cards: " << playerCard1 << ", " << playerCard2 << std::endl;

        playerScore += cardValue(playerCard1) + cardValue(playerCard2);

        // Check for blackjack
        if (playerScore == 21) {
            std::cout << "Blackjack! You win 1.5 times your bet." << std::endl;
            if (buyIn != 0) {
                // Ensure division by zero doesn't occur
                updateMoney(3.0 * buyIn / 2.0, currentPlayer.money);
            } else {
                std::cout << "Your bet was 0. No additional winnings." << std::endl;
            }
            std::cout << "Your new total: $" << currentPlayer.money << std::endl;
            player = currentPlayer;
            continue;
        } else {
            // Player's turn
            char choiceHit;
            while (true) {
                std::cout << "Your current score: " << playerScore << std::endl;
                std::cout << "Press 'H' to Hit, 'S' to Stand, or 'D' to Double Down: ";
                std::cin >> choiceHit;

                if (choiceHit == 'H' || choiceHit == 'h') {
                    std::string newCard = drawCard(deck);
                    std::cout << "New card: " << newCard << std::endl;
                    playerScore += cardValue(newCard);
                    if (playerScore > 21) {
                        std::cout << "Busted! You lose this round." << std::endl;
                        break;
                    }
                } else if ((choiceHit == 'D' || choiceHit == 'd') && !doubledDown) {
                    double additionalBet; // Changed additionalBet type to double
                    std::cout << "Enter additional bet amount for doubling down: ";
                    std::cin >> additionalBet;
                    if (additionalBet <= 0 || !(canAfford(additionalBet, currentPlayer.money))) {
                        std::cout << "Invalid bet amount or insufficient funds. Doubling down canceled." << std::endl;
                    } else {
                        buyIn += additionalBet;
                        updateMoney(-additionalBet, currentPlayer.money);
                        doubledDown = true;
                        std::string newCard = drawCard(deck);
                        std::cout << "New card: " << newCard << std::endl;
                        playerScore += cardValue(newCard);
                        if (playerScore > 21) {
                            std::cout << "Busted! You lose this round." << std::endl;
                            break;
                        }
                        break; // Player cannot take any more actions after doubling down
                    }
                } else {
                    break;
                }
            }
        }

        // Dealer's turn
        if (playerScore <= 21) {
            int dealerScore = 0;
            std::string dealerCard1 = drawCard(deck);
            std::string dealerCard2 = drawCard(deck);

            dealerScore += cardValue(dealerCard1) + cardValue(dealerCard2);
            std::cout << "Dealer's cards: " << dealerCard1 << ", " << dealerCard2 << std::endl;

            while (dealerScore < 17) {
                std::string newCard = drawCard(deck);
                std::cout << "Dealer draws: " << newCard << std::endl;
                dealerScore += cardValue(newCard);
            }

            std::cout << "Dealer's score: " << dealerScore << std::endl;

            // Determine winner
            if ((playerScore <= 21 && playerScore > dealerScore) || (dealerScore > 21 && playerScore <= 21)) {
                std::cout << "Congratulations! You win this round." << std::endl; 
                if (doubledDown)
                    updateMoney(3.0 * buyIn, currentPlayer.money);
                else
                    updateMoney(3.0 * buyIn, currentPlayer.money);

            } else if ((dealerScore <= 21 && dealerScore > playerScore) || (playerScore > 21 && dealerScore <= 21)) {
                std::cout << "Dealer wins this round." << std::endl;
            } else {
                std::cout << "It's a tie!" << std::endl;
                updateMoney(buyIn, currentPlayer.money);
            }
        }

        std::cout << "Your new total: $" << currentPlayer.money << std::endl;
        player = currentPlayer;
    }

    std::cout << "Game over. Your final balance: $" << player.money << std::endl;
}

std::string drawCard(std::vector<std::string> &deck) {
    int index = rand() % deck.size();
    std::string card = deck[index];
    deck.erase(deck.begin() + index);
    return card;
}

int cardValue(const std::string &card) {
    if (card == "J" || card == "Q" || card == "K") {
        return 10;
    } else if (card == "A") {
        return 11; // Assuming A is initially counted as 11
    } else {
        return std::stoi(card);
    }
}