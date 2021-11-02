#include "declarations.h"


int main()
{
    time_t currentTime;
    srand((unsigned)time(&currentTime)); // Seed the rand function with the current time
    system("color F"); // White
    mainMenu();
}


void mainMenu()
{
    int pos = 1;
    bool aiMode = false;
    bool* aiModePtr = &aiMode;
    Player* p1 = new Player();
    Player* p2 = new Player();
    p1->marker = 1;
    p2->marker = 2;

    while (true) {
        system("cls");
        std::cout << "Main Menu - Connect-Four" << std::endl << std::endl;
        std::cout << "Select an option:" << reset << std::endl << std::endl;
        if (pos == 1) { std::cout << pC << " > "; }
        std::cout << "Player vs Player" << reset << std::endl;
        if (pos == 2) { std::cout << pC << " > "; }
        std::cout << "Player vs AI" << reset << std::endl;
        if (pos == 3) { std::cout << pC << " > "; }
        std::cout << "Exit" << reset << std::endl;

        char ch = _getch();
        switch (ch) {
        case 'W':
        case 'w':
            if (pos == 1) {
                pos = 3;
                break;
            }
            pos--;
            break;
        case 'S':
        case 's':
            if (pos == 3) {
                pos = 1;
                break;
            }
            pos++;
            break;
        case 13:
            switch (pos) {
            case 1:
                aiMode = false;
                middleMenu(p1, p2);
                connect4(aiModePtr, p1, p2);
                break;
            case 2:
                aiMode = true;
                middleMenu(p1, p2);
                connect4(aiModePtr, p1, p2);
                break;
            case 3:
                exit(0);
                break;
            }
        }
    }
}


void middleMenu(Player* p1, Player* p2) {
    int pos = 1;
    while (true) {
        system("cls");
        std::cout << "Creating Players" << std::endl << std::endl;
        std::cout << "Select an option:" << reset << std::endl << std::endl;
        if (pos == 1) { std::cout << pC << " > "; }
        std::cout << "Set Names and Color" << reset << std::endl;
        if (pos == 2) { std::cout << pC << " > "; }
        std::cout << "Default Names and Color" << reset << std::endl;

        char ch = _getch();
        switch (ch) {
        case 'W':
        case 'w':
            if (pos == 1) {
                pos = 2;
                break;
            }
            pos--;
            break;
        case 'S':
        case 's':
            if (pos == 2) {
                pos = 1;
                break;
            }
            pos++;
            break;
        case 13:
            switch (pos) {
            case 1:
                createPlayers(p1, p2);
                return;
                break;
            case 2:
                p1->name = "Player 1";
                p1->color = 1;
                p2->name = "Player 2";
                p2->color = 2;
                return;
                break;
            }
        }
    }
}


void createPlayers(Player* p1, Player* p2) {
    int count{ 1 }, pos{ 1 };
    char ch{};

    while (true) {
        system("cls");

        std::cout << "Player " << count << ", enter your name : " << pC << std::endl;

        if (count == 1 && p1->name == "") {
            std::getline(std::cin, p1->name);
        }
        else if (count == 2 && p2->name == "") {
            std::getline(std::cin, p2->name);
        }
        else if (count == 1) {
            std::cout << pC << p1->name << std::endl;
        }
        else if (count == 2) {
            std::cout << pC << p2->name << std::endl;
        }
        
        std::cout << reset << std::endl;

        if (count == 1) {
            std::cout << p1->name << ", select your color:" << std::endl << std::endl;
        }
        else if (count == 2) {
            std::cout << p2->name << ", select your color:" << std::endl << std::endl;
        }
        

        if (pos == 1) { std::cout << pR << " > "; }
        std::cout << "Red" << reset << std::endl;
        if (pos == 2) { std::cout << pG << " > "; }
        std::cout << "Green" << reset << std::endl;
        if (pos == 3) { std::cout << pB << " > "; }
        std::cout << "Blue" << reset << std::endl;
        if (pos == 4) { std::cout << pY << " > "; }
        std::cout << "Yellow" << reset << std::endl;

        ch = _getch();
        switch (ch) {
        case 'W':
        case 'w':
            if (pos == 1) {
                pos = 4;
                break;
            }
            pos--;
            break;
        case 'S':
        case 's':
            if (pos == 4) {
                pos = 1;
                break;
            }
            pos++;
            break;
        case 13:
            if (count == 1) {
                p1->color = pos;
                pos = 1;
                count++;
            }
            else if (count == 2) {
                if (pos == p1->color) {
                    std::cout << std::endl;
                    std::cout << p1->name << " has already chosen this color!" << std::endl;
                    system("pause");
                    break;
                }
                else {
                    p2->color = pos;
                    pos = 1;
                    count = 1;
                    return;
                }
            }
            break;
        }
    }
}


void connect4(bool* aiMode, Player* p1, Player* p2)
{
    std::vector <std::vector <int>> board{};
    std::pair <bool, int> returnResult (false, 0);
    //bool gameWon = returnResult.first;
    Player* currentPlayer = p1;
    

    // Init board
    for (int i{}; i < ROW_HEIGHT; i++) { 
        std::vector <int> temp{};
        for (int k{}; k < ROW_WIDTH; k++) {
            temp.push_back(0);
        }
        board.push_back(temp);
    }


    // Game loop
    while (true) {
        printBoard(&board, aiMode, currentPlayer, p1, p2);
        checkInput(&board, currentPlayer, p1, p2);
        
        //returnResult = checkWin(&board);

        if (returnResult.first) { // If game is won
            if (returnResult.second == 1) {
                std::cout << p1->name << " has won!" << std::endl;
            }
            else if (returnResult.second == 2) {
                std::cout << p2->name << " has won!" << std::endl;
            }
            return;
        }
        
        
    }
}


void printBoard(std::vector<std::vector<int>>* board, bool* aiMode, Player* currentPlayer, Player* p1, Player* p2) 
{
    system("cls");
    /*if (aiMode) { std::cout << "Player versus AI." << std::endl; }
    else { std::cout << "Player versus player." << std::endl; }*/

    std::cout << std::endl;

    std::cout << "Move: " << pC << "   [A - D]" << std::endl;
    std::cout << pW << "Confirm: " << pC << "[ENTER]" << reset << std::endl << std::endl;

  /*  if (aiMode) {
        if (currentPlayer == 1) { std::cout << "Your turn!" << std::endl; }
        else { std::cout << "AI's turn!" << std::endl; }
    }*/
 
    
    std::cout << currentPlayer->name << "'s turn!" << std::endl << std::endl;

    std::string row = " ---------------------";
    for (int i{}; i < ROW_WIDTH; i++) {

        if (currentPlayer->pos == i) {
            std::cout << pC << "  v" << reset;
        }
        else {
            std::cout << "   ";
        }
    }
    std::cout << std::endl;


    for (int y{}; y < ROW_HEIGHT; y++) { 
        std::cout << "|";
        for (int x{}; x < ROW_WIDTH; x++) {
            if (board->at(y).at(x) == 0) { 
                std::cout << " X ";
            }
            else if (board->at(y).at(x) == 1) {
                p1->printSelf();
            }
            else {
                p2->printSelf();
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << row << std::endl;
}


void checkInput(std::vector<std::vector<int>>* board, Player* currentPlayer, Player* p1, Player* p2)
{
    char ch{};
    ch = _getch();
    switch (ch) {
        case 'a':
        case 'A':
            if (currentPlayer->pos == 0) {
                currentPlayer->pos = ROW_WIDTH - 1;
            }
            else {
                currentPlayer->pos--;
            }
            break;
        case 'd':
        case 'D':
            if (currentPlayer->pos == ROW_WIDTH - 1) {
                currentPlayer->pos = 0;
            }
            else {
                currentPlayer->pos++;
            }
            break;
        case 13: // Enter
            insertMarker(board, currentPlayer, p1, p2);
            break;
    }
}


void insertMarker(std::vector<std::vector<int>>* board, Player* currentPlayer, Player* p1, Player* p2)
{
    for (int i = ROW_HEIGHT - 1; i >= 0; i--) {
        if (board->at(i).at(currentPlayer->pos) == 0) {
            board->at(i).at(currentPlayer->pos) = currentPlayer->marker;

            //Switch players
            if (currentPlayer == p1) { // Switch players
                currentPlayer = p2;
            }
            else {
                currentPlayer = p1;
            }
            return;
        }
    }
    std::cout << "No available spaces!" << std::endl;
    Sleep(800);
}


std::pair<bool, int> checkWin(std::vector<std::vector<int>>* board) 
{
    int p1Counter{}, p2Counter{};

    // Horizontal
    for (int i{}; i < ROW_HEIGHT; i++) {
        for (int k{}; k < ROW_WIDTH; k++) {
            if (board->at(i).at(k) == 1) {
                p1Counter++;
                p2Counter = 0;
            }
            else if (board->at(i).at(k) == 2) {
                p2Counter++;
                p1Counter = 0;
            }
            if (p1Counter == 4 || p2Counter == 4) {
                return std::make_pair(true, board->at(i).at(k));
            }
        }
    }

    p1Counter = 0;
    p2Counter = 0;

    // Vertical
    for (int i{}; i < ROW_WIDTH; i++) {
        for (int k{}; k < ROW_HEIGHT; k++) {
            if (board->at(i).at(k) == 1) {
                p1Counter++;
                p2Counter = 0;
            }
            else if (board->at(i).at(k) == 2) {
                p2Counter++;
                p1Counter = 0;
            }
            if (p1Counter == 4 || p2Counter == 4) {
                return std::make_pair(true, board->at(i).at(k));
            }
        }
    }

    //Horizontal -> Right

    int max_y = ROW_HEIGHT - 4;
    int max_x = ROW_WIDTH - 4;
    int h{};

    for (int z{}; z <= max_y; z++) {
        for (int v{}; v < ROW_HEIGHT - v; v++) {
            h = v;

            if (board->at(v).at(h) == 1) {
                p1Counter++;
                p2Counter = 0;
            }
            else if (board->at(v).at(h) == 2) {
                p2Counter++;
                p1Counter = 0;
            }
            if (p1Counter == 4 || p2Counter == 4) {
                return std::make_pair(true, board->at(v).at(h));
            }
        }
    }

    



    //Horizontal <- Left

}


void saveGame()
{

}