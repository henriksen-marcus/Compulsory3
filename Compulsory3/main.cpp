#include "declarations.h"
//#include "Player.h"

int main()
{
    //time_t currentTime;
    //srand((unsigned)time(&currentTime)); // Seed the rand function with the current time
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
    int pos{};
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
                p1->color = 0;
                p2->name = "Player 2";
                p2->color = 1;
                return;
                break;
            }
        }
    }
}


void createPlayers(Player* p1, Player* p2) {
    int count{ 1 }, pos{};
    std::string name{};
    int color{};

    while (count != 3) {
        system("cls");

        std::cout << "Player " << count << ", enter your name : " << pC << std::endl;
        std::getline(std::cin, name);
        std::cout << reset << std::endl << std::endl;

        std::cout << "Player " << count << ", select your color: " << pC << std::endl;
        std::cout << "1: " << pR << "Red" << reset << std::endl;
        std::cout << "2: " << pG << "Green" << reset << std::endl;
        std::cout << "3: " << pB << "Blue" << reset << std::endl;
        std::cout << "4: " << pY << "Yellow" << reset << std::endl;

        do
        {
            color = _getch();
        } while (color != 1 && color != 2 && color != 3 && color != 4);
        
        if (count == 1) {
            p1->name = name;
            p1->color = color;
        }
        else {
            p2->name = name;
            p2->color = color;
        }
        count++;
    }
}


void connect4(bool* aiMode, Player* p1, Player* p2)
{
    std::vector <std::vector <int>> board{};
    std::pair <bool, int> returnResult (false, 0);
    bool gameWon = returnResult.first;
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
    while (!gameWon) {
        printBoard(&board, aiMode, currentPlayer);
        checkInput(&board, currentPlayer);

        returnResult = checkWin(&board);

        if (gameWon) {
            if (returnResult.second == 1) {
                std::cout << p1->name << " has won!" << std::endl;
            }
            else if (returnResult.second == 2) {
                std::cout << p2->name << " has won!" << std::endl;
            }
            return;
        }

        //if (currentPlayer == p1) { // Switch players
        //    currentPlayer = p2;
        //}
        //else {
        //    currentPlayer = p1;
        //}
    }
}


void printBoard(std::vector<std::vector<int>>* board, bool* aiMode, Player* currentPlayer) 
{
    system("cls");
    if (*aiMode) { std::cout << "Player versus AI." << std::endl; }
    else { std::cout << "Player versus player." << std::endl; }

    std::cout << std::endl;

    std::cout << pC << "[ A   D ]" << std::endl;
    std::cout << pW << "Confirm: " << pC << "[ENTER]" << reset << std::endl;

  /*  if (aiMode) {
        if (currentPlayer == 1) { std::cout << "Your turn!" << std::endl; }
        else { std::cout << "AI's turn!" << std::endl; }
    }*/
 
    std::cout << currentPlayer->name << "'s turn!" << std::endl; 

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
                std::cout << pR << " O " << reset;
            }
            else {
                std::cout << pG << " O " << reset;
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << row << std::endl;
}


void checkInput(std::vector<std::vector<int>>* board, Player* currentPlayer)
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
        insertMarker(board, currentPlayer);
        break;
    }
}


void insertMarker(std::vector<std::vector<int>>* board, Player* p)
{
    for (int i = ROW_HEIGHT - 1; i >= 0; i--) {
        if (board->at(p->pos).at(i) != 0) {
            board->at(p->pos).at(i) = p->marker;
        }
    }
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
            if (board->at(k).at(i) == 1) {
                p1Counter++;
                p2Counter = 0;
            }
            else if (board->at(k).at(i) == 2) {
                p2Counter++;
                p1Counter = 0;
            }
            if (p1Counter == 4 || p2Counter == 4) {
                return std::make_pair(true, board->at(i).at(k));
            }
        }
    }

    int max_v = ROW_HEIGHT - 4;
    int max_h = ROW_WIDTH - 4;

    int v{}; // Vertical
    int h{}; // Horizontal
    int z{}; // Start position offset

    p1Counter = 0;
    p2Counter = 0;

    // Diagonal - Right 1
    while (z <= max_v) {
        v = z; // Change start position
        while (v < ROW_HEIGHT) {
            h = v - z;
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
            v++;
        }
        z++;
    }


    z = 1;
    p1Counter = 0;
    p2Counter = 0;

    // Diagonal - Right 2
    while (z <= max_h) {
        h = z; // Change start position
        while (h < ROW_WIDTH) {
            v = h - z;
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
            h++;
        }
        z++;
    }

    z = 0;
    p1Counter = 0;
    p2Counter = 0;

    // Diagonal - Left 1
    while (z <= max_v) {
        v = z; // Change start position
        h = 0;
        while (v < 6) {
            h = 6 - v + z;
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
            v++;
        }
        z++;
    }

    z = 0;
    p1Counter = 0;
    p2Counter = 0;

    // Diagonal - Left 2
    while (z < max_h) {
        h = 5 - z; // Change start position
        while (h >= 0) {
            v = 5 - h - z;
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
            h--;
        }
        z++;
    }
    return std::make_pair(false, 0);
}


void saveGame()
{
    std::fstream file{};
}