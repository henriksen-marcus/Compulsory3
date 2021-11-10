// Compulsory 3, Marcus Henriksen, Connect 4
// In this project I decided to use classes for the two players, and make it universal so that the AI
// can also be the same type of object. I made the AI algorithm myself without following any tutorials.
// In short, the AI will check for 3 in a rows and 2 in a rows for both players, and append them to
// seperate vectors. It will then run an extensive check to filter out any moves that will cause problems
// or are not as viable as the other moves. I call it a "priority and request" system as each check will
// return a certain priority, and another algoritm will take the best moves, check if any of those moves
// request the same location, in which case that move will get a higer prority (killing two birds with one stone).


#include "declarations.h"


int main()
{
    srand((unsigned)time(NULL));
    system("color F"); // White
    while (true) { mainMenu(); }
    return 0;
}


void mainMenu()
{
    int pos = 1;
    bool aiMode = false;
    Player* p1 = new Player();
    Player* p2 = new Player();
    Player* currentPlayer = p1;
    p1->marker = 1;
    p2->marker = 2;

    while (true) {
        system("cls");
        std::cout << " === Main Menu - Connect-Four ===" << std::endl << std::endl;
        std::cout << "Select an option:" << reset << std::endl << std::endl;
        if (pos == 1) { std::cout << pC << " > "; }
        std::cout << "Player vs Player" << reset << std::endl;
        if (pos == 2) { std::cout << pC << " > "; }
        std::cout << "Player vs AI" << reset << std::endl;
        if (pos == 3) { std::cout << pC << " > "; }
        std::cout << "Show Saved Games" << reset << std::endl;
        if (pos == 4) { std::cout << pC << " > "; }
        std::cout << "Exit" << reset << std::endl;
        std::cout << std::endl;

        char ch = _getch();
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
            switch (pos) {
            case 1:
                aiMode = false;
                middleMenu(p1, p2, aiMode);
                connect4(aiMode, p1, p2, currentPlayer);
                break;
            case 2:
                aiMode = true;
                p2->color = 1;
                p2->name = "AI";
                middleMenu(p1, p2, aiMode);
                connect4(aiMode, p1, p2, currentPlayer);
                break;
            case 3:
                loadGame();
                break;
            case 4:
                exit(0);
                break;
            }
        }
    }
}


void middleMenu(Player* p1, Player* p2, bool aiMode) {
    int pos = 1;
    while (true) {
        system("cls");
        std::cout << " === Creating Players ===" << std::endl << std::endl;
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
                createPlayers(p1, p2, aiMode);
                return;
                break;
            case 2:
                p1->name = "Player 1";
                if (!aiMode) {
                    p1->color = 1;
                    p2->name = "Player 2";
                    p2->color = 2;
                }
                else {
                    p1->color = 2;
                    p2->name = "AI";
                    p2->color = 1;
                }
                return;
                break;
            }
        }
    }
}


void createPlayers(Player* p1, Player* p2, bool aiMode) {
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
        if (pos == 2) { std::cout << pB << " > "; }
        std::cout << "Blue" << reset << std::endl;
        if (pos == 3) { std::cout << pG << " > "; }
        std::cout << "Green" << reset << std::endl;
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
                if (aiMode) { 
                    if (pos == p2->color) {
                        std::cout << std::endl;
                        std::cout << p2->name << " has already chosen this color!" << std::endl;
                        system("pause");
                        break;
                    }
                    else {
                        p1->color = pos;
                        return;
                    }
                }
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


void connect4(bool aiMode, Player* &p1, Player* &p2, Player* &currentPlayer)
{
    bool exit = false;
    while (!exit) {
        std::vector <std::vector <int>> board{};
        std::tuple <bool, int, int, int, std::string> returnResult{};
        currentPlayer = p1;

        // Init board
        for (int i{}; i < 6; i++) {
            std::vector <int> temp{};
            for (int k{}; k < 7; k++) {
                temp.push_back(0);
            }
            board.push_back(temp);
        }

        // Game loop
        while (true) {
            printBoard(&board, aiMode, currentPlayer, p1, p2);
            if (aiMode) {
                if (currentPlayer == p1) {
                    checkInput(&board, currentPlayer, p1, p2);
                }
                else {
                    aiMove(&board, aiMode, currentPlayer, p1, p2);
                }
            }
            else {
                checkInput(&board, currentPlayer, p1, p2);
            }


            returnResult = checkWin(&board);

            if (std::get<0>(returnResult)) { // If game is won
                boardUpdate(&board, returnResult);
                printBoard(&board, aiMode, currentPlayer, p1, p2);
                if (std::get<1>(returnResult) == 1) {
                    std::cout << p1->name << " has won!" << std::endl;
                    p1->winner = true;
                }
                else if (std::get<1>(returnResult) == 2) {
                    std::cout << p2->name << " has won!" << std::endl;
                    p2->winner = true;
                }
                system("pause");
                break;
            }

            if (checkForFullBoard(&board)) {
                std::cout << "Draw!" << std::endl;
                system("pause");
                break;
            }
        }
        exit = saveGamePrompt(&board, currentPlayer, p1, p2, aiMode);
    }
}


bool saveGamePrompt(std::vector<std::vector<int>>* board, Player* currentPlayer, Player* p1, Player* p2, bool aiMode) {
    
    int pos{ 1 };
    
    while (true) {
        system("cls");
        printBoard(board, aiMode, currentPlayer, p1, p2);
        std::cout << "Choose an option: " << std::endl << std::endl;
        if (pos == 1) { std::cout << pC << " > "; }
        std::cout << "Save & play again" << reset << std::endl;
        if (pos == 2) { std::cout << pC << " > "; }
        std::cout << "Play again" << reset << std::endl;
        if (pos == 3) { std::cout << pC << " > "; }
        std::cout << "Save & exit" << reset << std::endl;
        if (pos == 4) { std::cout << pC << " > "; }
        std::cout << "Exit" << reset << std::endl;
        std::cout << std::endl;

        char ch = _getch();
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
            switch (pos) {
            case 1:
                saveGame(board, p1, p2);
                std::cout << std::endl;
                std::cout << "Saving game..." << std::endl;
                Sleep(400);
                return false;
                break;
            case 2:
                return false;
                break;
            case 3:
                saveGame(board, p1, p2);
                std::cout << std::endl;
                std::cout << "Saving game..." << std::endl;
                p1->clear();
                p2->clear();
                Sleep(400);
                return true;
                break;
            case 4:
                p1->clear();
                p2->clear();
                return true;
                break;
            }
        }
    }
}


void boardUpdate(std::vector<std::vector<int>>* board, std::tuple<bool, int, int, int, std::string> winInfo) {
    std::vector <std::vector <int>> arr{};

    std::string dir = std::get<4>(winInfo);
    int y = std::get<2>(winInfo);
    int x = std::get<3>(winInfo);

    arr.push_back({ y, x });

    if (dir == "hor") {
        arr.push_back({ y, x - 1 });
        arr.push_back({ y, x - 2 });
        arr.push_back({ y, x - 3 });
    }
    else if (dir == "ver") {
        arr.push_back({ y - 1, x });
        arr.push_back({ y - 2, x });
        arr.push_back({ y - 3, x });
    }
    else if (dir == "dr") {
        arr.push_back({ y - 1, x - 1 });
        arr.push_back({ y - 2, x - 2 });
        arr.push_back({ y - 3, x - 3 });
    }
    else if (dir == "dl") {
        arr.push_back({ y - 1, x + 1 });
        arr.push_back({ y - 2, x + 2 });
        arr.push_back({ y - 3, x + 3 });
    }

    int winner{};
    if (std::get<1>(winInfo) == 1) {
        winner = 3;
    }
    else {
        winner = 4;
    }

    board->at(arr[0][0]).at(arr[0][1]) = winner;
    board->at(arr[1][0]).at(arr[1][1]) = winner;
    board->at(arr[2][0]).at(arr[2][1]) = winner;
    board->at(arr[3][0]).at(arr[3][1]) = winner;
}


void printBoard(std::vector<std::vector<int>>* board, bool aiMode, Player*& currentPlayer, Player*& p1, Player*& p2)
{
    system("cls");
    if (aiMode) { std::cout << " === Player versus AI ===" << std::endl; }
    else { std::cout << " === Player versus Player ===" << std::endl; }

    std::cout << std::endl;

    std::cout << "Move: " << pC << "   [A - D]" << reset << std::endl;
    std::cout << "Confirm: " << pC << "[ENTER]" << reset << std::endl << std::endl;

    if (aiMode) {
        if (currentPlayer == p1) {
            std::cout << "Your turn!" << std::endl << std::endl;
        }
        else {
            std::cout << "AI's turn!" << std::endl << std::endl;
        }
    }
    else {
        std::cout << currentPlayer->name << "'s turn!" << std::endl << std::endl;
    }


    std::string row = " ---------------------";
    for (int i{}; i < 7; i++) {

        if (currentPlayer->pos == i) {
            std::cout << pC << "  v" << reset;
        }
        else {
            std::cout << "   ";
        }
    }
    std::cout << std::endl;
    bool stop = false;

    for (int y{}; y < 6; y++) { 
        std::cout << "|";
        
        for (int x{}; x < 7; x++) {

            switch (board->at(y).at(x)) {
            case 0:
                std::cout << " * ";
                break;
            case 1:
                p1->printSelf();
                break;
            case 2:
                p2->printSelf();
                break;
            case 3:
                p1->printSelf(true);
                break;
            case 4:
                p2->printSelf(true);
                break;
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << row << std::endl;
}


void checkInput(std::vector<std::vector<int>>* board, Player* &currentPlayer, Player* &p1, Player* &p2)
{
    char ch{};
    ch = _getch();
    switch (ch) {
        case 'a':
        case 'A':
            if (currentPlayer->pos == 0) {
                currentPlayer->pos = 6;
            }
            else {
                currentPlayer->pos--;
            }
            break;
        case 'd':
        case 'D':
            if (currentPlayer->pos == 6) {
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
    if (currentPlayer == p1) {
        p2->pos = p1->pos;
    }
    else {
        p1->pos = p2->pos;
    }
}


void insertMarker(std::vector<std::vector<int>>* board, Player*& currentPlayer, Player*& p1, Player*& p2)
{
    std::pair <bool, int> spot = checkAvailablility(board, currentPlayer->pos);
    if (spot.first == true) {
        board->at(spot.second).at(currentPlayer->pos) = currentPlayer->marker;
        if (currentPlayer == p1) { // Switch players
            currentPlayer = p2;
            p2->pos = p1->pos;
        }
        else {
            currentPlayer = p1;
            p1->pos = p2->pos;
        }
        return;
    }
    std::cout << "No available spaces!" << std::endl;
    Sleep(600);
}


std::tuple <bool, int, int, int, std::string> checkWin(std::vector<std::vector<int>>* board)
{
    int p1Counter{}, p2Counter{};

    // Horizontal
    for (int i{}; i < 6; i++) {
        p1Counter = 0;
        p2Counter = 0;
        for (int k{}; k < 7; k++) {
            if (board->at(i).at(k) == 1) {
                p1Counter++;
                p2Counter = 0;
            }
            else if (board->at(i).at(k) == 2) {
                p2Counter++;
                p1Counter = 0;
            }
            else {
                p1Counter = 0;
                p2Counter = 0;
            }
            if (p1Counter == 4 || p2Counter == 4) {
                return std::make_tuple( true, board->at(i).at(k), i, k, "hor" );
            }
        }
    }

    p1Counter = 0;
    p2Counter = 0;

    // Vertical
    for (int i{}; i < 7; i++) {
        p1Counter = 0;
        p2Counter = 0;
        for (int k{}; k < 6; k++) {
            if (board->at(k).at(i) == 1) {
                p1Counter++;
                p2Counter = 0;
            }
            else if (board->at(k).at(i) == 2) {
                p2Counter++;
                p1Counter = 0;
            }
            else {
                p1Counter = 0;
                p2Counter = 0;
            }
            if (p1Counter == 4 || p2Counter == 4) {
                return std::make_tuple(true, board->at(k).at(i), k, i, "ver");
            }
        }
    }

    int v{}; // Vertical
    int h{}; // Horizontal
    int z{}; // Start position offset

    p1Counter = 0;
    p2Counter = 0;

    // Diagonal - Right 1
    while (z <= 2) {
        v = z; // Change start position
        p1Counter = 0;
        p2Counter = 0;
        while (v < 6) {
            h = v - z;
            if (board->at(v).at(h) == 1) {
                p1Counter++;
                p2Counter = 0;
            }
            else if (board->at(v).at(h) == 2) {
                p2Counter++;
                p1Counter = 0;
            }
            else {
                p1Counter = 0;
                p2Counter = 0;
            }
            if (p1Counter == 4 || p2Counter == 4) {
                return std::make_tuple(true, board->at(v).at(h), v, h, "dr");
            }
            v++;
        }
        z++;
    }


    z = 1;
    p1Counter = 0;
    p2Counter = 0;

    // Diagonal - Right 2
    while (z <= 3) {
        h = z; // Change start position
        p1Counter = 0;
        p2Counter = 0;
        while (h < 7) {
            v = h - z;
            if (board->at(v).at(h) == 1) {
                p1Counter++;
                p2Counter = 0;
            }
            else if (board->at(v).at(h) == 2) {
                p2Counter++;
                p1Counter = 0;
            }
            else {
                p1Counter = 0;
                p2Counter = 0;
            }
            if (p1Counter == 4 || p2Counter == 4) {
                return std::make_tuple(true, board->at(v).at(h), v, h, "dr");
            }
            h++;
        }
        z++;
    }

    z = 0;
    p1Counter = 0;
    p2Counter = 0;

    // Diagonal - Left 1
    while (z <= 2) {
        v = z; // Change start position
        p1Counter = 0;
        p2Counter = 0;
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
            else {
                p1Counter = 0;
                p2Counter = 0;
            }
            if (p1Counter == 4 || p2Counter == 4) {
                return std::make_tuple(true, board->at(v).at(h), v, h, "dl");
            }
            v++;
        }
        z++;
    }

    z = 0;
    p1Counter = 0;
    p2Counter = 0;

    // Diagonal - Left 2
    while (z < 3) {
        h = 5 - z; // Change start position
        p1Counter = 0;
        p2Counter = 0;
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
            else {
                p1Counter = 0;
                p2Counter = 0;
            }
            if (p1Counter == 4 || p2Counter == 4) {
                return std::make_tuple(true, board->at(v).at(h), v, h, "dl");
            }
            h--;
        }
        z++;
    }
    return std::make_tuple(false, 0, 0, 0, "");
}


bool checkForFullBoard(std::vector<std::vector<int>>* board)
{
    // Efficient check 
    for (int i{}; i < 6; i++) {
        if (board->at(0).at(i) == 0) {
            return false;
        }
    }
    return true;
}


void saveGame(std::vector<std::vector<int>>* board, Player*& p1, Player*& p2)
{
    std::fstream file("scores.txt");
    if (file.is_open()) {
        file.close();
    }
    file.open("scores.txt", std::ios::app);

    file << p1->name << "\n";
    file << p1->color << "\n";

    file << p2->name << "\n";
    file << p2->color << "\n";
    
    if (p1->winner) {
        file << "1\n";
    }
    else if (p2->winner) {
        file << "2\n";
    }
    else {
        file << "0\n";
    }

    file << time(NULL) << "\n";

    std::stringstream numToText{};
    
    for (int i{}; i < board->size(); i++) {
        for (int k{}; k < board->at(0).size(); k++) {
            numToText << board->at(i).at(k);
        }
    }

    file << numToText.str() << "\n";
    file.close();
}


void loadGame() {
    std::fstream file("scores.txt");
    std::string line{};
    int fileLength{};
    std::vector <std::string> fileInfo{};

    struct game {
        std::string p1Name;
        int p1Color{};
        std::string p2Name;
        int p2Color{};
        int winner{};
        long int time{};
        std::vector<std::vector<char>> board{};
    }temp;
    
    std::vector <game> saveGames{};

    if (file.is_open()) {
        file.close();
    }
    file.open("scores.txt", std::ios::in);


    while (std::getline(file, line)) {
        fileInfo.push_back(line);
        fileLength++;
    }
    file.clear();

    if (fileLength == 0) {
        std::cout << "No saved games." << std::endl;
        system("pause");
        return;
    }


    for (int i{}; i < fileLength; i += 7) {
        temp.p1Name = fileInfo[i];
        temp.p1Color = std::stoi(fileInfo[i + 1]);
        temp.p2Name = fileInfo[i + 2];
        temp.p2Color = std::stoi(fileInfo[i + 3]);
        temp.winner = std::stoi(fileInfo[i + 4]);
        temp.time = std::stoi(fileInfo[i + 5]);

        std::vector <char> tempArr{};

        for (int k{}; k < 42; k++) {
            if (k % 7 == 0 && k != 0) {
                temp.board.push_back(tempArr);
                tempArr = {};
            }
            tempArr.push_back((char)fileInfo[i + 6][k]);
        }
        temp.board.push_back(tempArr);

        saveGames.push_back(temp);
        temp = {};
    }

    system("cls");
    std::cout << pC << "===== Saved Games: =====" << reset << reset << std::endl << std::endl;

    std::string row = " ---------------------";

    for (int i{}; i < saveGames.size(); i++) {

        switch (saveGames[i].p1Color) {
        case 1:
            std::cout << pR <<saveGames[i].p1Name << reset;
            break;
        case 2:
            std::cout << pB << saveGames[i].p1Name << reset;
            break;
        case 3:
            std::cout << pG << saveGames[i].p1Name << reset;
            break;
        case 4:
            std::cout << pY << saveGames[i].p1Name << reset;
            break;
        }

        std::cout << " vs ";

        switch (saveGames[i].p2Color) {
        case 1:
            std::cout << pR << saveGames[i].p2Name << reset << std::endl;
            break;
        case 2:
            std::cout << pB << saveGames[i].p2Name << reset << std::endl;
            break;
        case 3:
            std::cout << pG << saveGames[i].p2Name << reset << std::endl;
            break;
        case 4:
            std::cout << pY << saveGames[i].p2Name << reset << std::endl;
            break;
        }
        std::cout << std::endl;

        


        for (int j{}; j < 6; j++) {
            std::cout << "|";
            for (int k{}; k < 7; k++) {
                switch (saveGames[i].board[j][k]) {
                case '0':
                    std::cout << " * ";
                    break;
                case '1':
                    switch (saveGames[i].p1Color) {
                    case 1:
                        std::cout << pR << " O " << reset;
                        break;
                    case 2:
                        std::cout << pB << " O " << reset;
                        break;
                    case 3:
                        std::cout << pG << " O " << reset;
                        break;
                    case 4:
                        std::cout << pY << " O " << reset;
                        break;
                    }
                    break;
                case '2':
                    switch (saveGames[i].p2Color) {
                    case 1:
                        std::cout << pR << " O " << reset;
                        break;
                    case 2:
                        std::cout << pB << " O " << reset;
                        break;
                    case 3:
                        std::cout << pG << " O " << reset;
                        break;
                    case 4:
                        std::cout << pY << " O " << reset;
                        break;
                    }
                    break;
                case '3':
                    switch (saveGames[i].p1Color) {
                    case 1:
                        std::cout << oW << pR << " O " << reset;
                        break;
                    case 2:
                        std::cout << oW << pB << " O " << reset;
                        break;
                    case 3:
                        std::cout << oW << pG << " O " << reset;
                        break;
                    case 4:
                        std::cout << oW << pY << " O " << reset;
                        break;
                    }
                    break;
                case '4':
                    switch (saveGames[i].p2Color) {
                    case 1:
                        std::cout << oW << pR << " O " << reset;
                        break;
                    case 2:
                        std::cout << oW << pB << " O " << reset;
                        break;
                    case 3:
                        std::cout << oW << pG << pB << " O " << reset;
                        break;
                    case 4:
                        std::cout << oW << pY << " O " << reset;
                        break;
                    }
                }
            }
            std::cout << "|" << std::endl;
        }
        std::cout << row << std::endl;
        

        if (saveGames[i].winner == 1) {
            std::cout << saveGames[i].p1Name << " won the game!" << std::endl << std::endl;
        }
        else if (saveGames[i].winner == 2){
            std::cout << saveGames[i].p2Name << " won the game!" << std::endl << std::endl;
        }
        else {
            std::cout << "Draw!" << std::endl;
        }

        double converted = time(NULL) - saveGames[i].time;
        int rounded{};
        std::string text{};

        if (converted > 86400) {
            rounded = converted / 86400;
            text = "day(s) ago";
        }
        else if (converted > 3600) {
            rounded = converted / 3600;
            text = "hour(s) ago";
        }
        else if (converted > 60) {
            rounded = converted / 60;
            text = "minute(s) ago";
        }
        else {
            text = "Less than a minute ago";
        }

        if (rounded != 0) {
            std::cout << rounded << " " << text << std::endl;
        }
        else {
            std::cout << text << std::endl;
        }

        std::cout << std::endl << std::endl;
    }
    system("pause");
}


void aiMove(std::vector<std::vector<int>>* board, bool aiMode, Player* &currentPlayer, Player* &p1, Player* &p2) {
    std::cout << "Thinking..." << std::endl;
    Sleep(600);
    int blockPos = getAiInfo(board);
    int newPos{};
    if (blockPos != -1) {
        newPos = blockPos;
    }
    else {
        do
        {
            newPos = rand() % 7;
        } while (!checkAvailablility(board, newPos).first);
        
    }

    // Move arrow
    int moveAmount{};
    if (p2->pos < newPos) {
        moveAmount = newPos - p2->pos;
        for (int i{}; i < moveAmount; i++) {
            p2->pos++;
            printBoard(board, aiMode, currentPlayer, p1, p2);
            Sleep(330);
        }
    }
    else if (p2->pos > newPos) {
        moveAmount = p2->pos - newPos;
        for (int i{}; i < moveAmount; i++) {
            p2->pos--;
            printBoard(board, aiMode, currentPlayer, p1, p2);
            Sleep(330);
        }
    }
    insertMarker(board, currentPlayer, p1, p2);
}


int getAiInfo(std::vector<std::vector<int>>* &board) {
    int p1Counter{}, p2Counter{};

    std::vector<std::tuple<int, int, std::string>> pWinPos3{};
    std::vector<std::tuple<int, int, std::string>> pWinPos2{};
    std::vector<std::tuple<int, int, std::string>> aWinPos3{};
    std::vector<std::tuple<int, int, std::string>> aWinPos2{};

    std::vector<std::tuple<int, int, std::string>> pWinPosCurrent{};
    std::vector<std::tuple<int, int, std::string>> aWinPosCurrent{};



    for (int checkLen = 3; checkLen >= 2; checkLen--) {
       
        pWinPosCurrent.clear();
        aWinPosCurrent.clear();

        for (int i{}; i < 6; i++) {
            p1Counter = 0;
            p2Counter = 0;
            for (int k{}; k < 7; k++) {
                if (board->at(i).at(k) == 1) {
                    p1Counter++;
                    p2Counter = 0;
                }
                else if (board->at(i).at(k) == 2) {
                    p2Counter++;
                    p1Counter = 0;
                }
                else {
                    p1Counter = 0;
                    p2Counter = 0;
                }
                if (p1Counter == checkLen) {
                    pWinPosCurrent.push_back(std::make_tuple(i, k, "hor"));
                }
                if (p2Counter == checkLen) {
                    aWinPosCurrent.push_back(std::make_tuple(i, k, "hor"));
                }
            }
        }

        p1Counter = 0;
        p2Counter = 0;

        // Vertical
        for (int i{}; i < 7; i++) {
            p1Counter = 0;
            p2Counter = 0;
            for (int k{}; k < 6; k++) {
                if (board->at(k).at(i) == 1) {
                    p1Counter++;
                    p2Counter = 0;
                }
                else if (board->at(k).at(i) == 2) {
                    p2Counter++;
                    p1Counter = 0;
                }
                else {
                    p1Counter = 0;
                    p2Counter = 0;
                }
                if (p1Counter == checkLen) {
                    pWinPosCurrent.push_back(std::make_tuple(k, i, "ver"));
                }
                if (p2Counter == checkLen) {
                    aWinPosCurrent.push_back(std::make_tuple(k, i, "ver"));
                }
            }
        }

        int v{}; // Vertical
        int h{}; // Horizontal
        int z{}; // Start position offset

        p1Counter = 0;
        p2Counter = 0;

        // Diagonal - Right 1
        while (z <= 2) {
            v = z; // Change start position
            p1Counter = 0;
            p2Counter = 0;
            while (v < 6) {
                h = v - z;
                if (board->at(v).at(h) == 1) {
                    p1Counter++;
                    p2Counter = 0;
                }
                else if (board->at(v).at(h) == 2) {
                    p2Counter++;
                    p1Counter = 0;
                }
                else {
                    p1Counter = 0;
                    p2Counter = 0;
                }
                if (p1Counter == checkLen) {
                    pWinPosCurrent.push_back(std::make_tuple(v, h, "dr"));
                }
                if (p2Counter == checkLen) {
                    aWinPosCurrent.push_back(std::make_tuple(v, h, "dr"));
                }
                v++;
            }
            z++;
        }


        z = 1;
        p1Counter = 0;
        p2Counter = 0;

        // Diagonal - Right 2
        while (z <= 3) {
            h = z; // Change start position
            p1Counter = 0;
            p2Counter = 0;
            while (h < 7) {
                v = h - z;
                if (board->at(v).at(h) == 1) {
                    p1Counter++;
                    p2Counter = 0;
                }
                else if (board->at(v).at(h) == 2) {
                    p2Counter++;
                    p1Counter = 0;
                }
                else {
                    p1Counter = 0;
                    p2Counter = 0;
                }
                if (p1Counter == checkLen) {
                    pWinPosCurrent.push_back(std::make_tuple(v, h, "dr"));
                }
                if (p2Counter == checkLen) {
                    aWinPosCurrent.push_back(std::make_tuple(v, h, "dr"));
                }
                h++;
            }
            z++;
        }

        z = 0;
        p1Counter = 0;
        p2Counter = 0;

        // Diagonal - Left 1
        while (z <= 2) {
            v = z; // Change start position
            p1Counter = 0;
            p2Counter = 0;
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
                else {
                    p1Counter = 0;
                    p2Counter = 0;
                }
                if (p1Counter == checkLen) {
                    pWinPosCurrent.push_back(std::make_tuple(v, h, "dl"));
                }
                if (p2Counter == checkLen) {
                    aWinPosCurrent.push_back(std::make_tuple(v, h, "dl"));
                }
                v++;
            }
            z++;
        }

        z = 0;
        p1Counter = 0;
        p2Counter = 0;

        // Diagonal - Left 2
        while (z < 3) {
            h = 5 - z; // Change start position
            p1Counter = 0;
            p2Counter = 0;
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
                else {
                    p1Counter = 0;
                    p2Counter = 0;
                }
                if (p1Counter == checkLen) {
                    pWinPosCurrent.push_back(std::make_tuple(v, h, "dl"));
                }
                if (p2Counter == checkLen) {
                    aWinPosCurrent.push_back(std::make_tuple(v, h, "dl"));
                }
                h--;
            }
            z++;
        }

        // Insert info
        if (checkLen == 3) {
            pWinPos3 = pWinPosCurrent;
            aWinPos3 = aWinPosCurrent;
        }
        else {
            pWinPos2 = pWinPosCurrent;
            aWinPos2 = aWinPosCurrent;
        }
    }

    /* I suddenly came to a realization that this game has gravity, so all the AI really needs to know 
    is which column to drop the marker lol... Refactoring/Simplification masterrace */
    std::vector<std::pair<int, int>> winPositions3{};
    std::vector<std::pair<int, int>> winPositions2{};
    std::vector<std::pair<int, int>> blockPositions3{};
    std::vector<std::pair<int, int>> blockPositions2{};

    /* Priority system, AI will check for all cases and rank them according to how urgent they are.
    * Priorities:
       AI has 3 in a row:                   6
       Player has 3 in a row:               5
       AI has 2 in a row in the open:       4
       Player has 2 in a row in the open:   3
       AI has 2 in a row:                   2
       Player has 2 in a row:               1
    */


    //Find AI win positions for 3 in a row
    for (int i{}; i < aWinPos3.size(); i++) { // Notice how I am only pushing back the horizontal position

        std::string dir = std::get<2>(aWinPos3[i]);
        int x = std::get<1>(aWinPos3[i]);
        int y = std::get<0>(aWinPos3[i]);


        if (dir == "hor") { // Horizontal
            // Check if spot in front to winpos is open
            if (x + 1 < 7) { // Check if spot exists
                /* std::get<1>(pWinPos3[i]) returns the horizontal position in the board vector, here I check if that value + 1 is outside the board,
                which will determine if the AI is allowed to place a marker there. Only checking horizontal because the check direction was horizontal.
                Vertical remanins zero. */
                if (board->at(y).at(x + 1) == 0) { // Check if spot is available
                    if (y == 5 || board->at(y + 1).at(x + 1) != 0) { // Check if the marker will be supported (gravity)
                        winPositions3.push_back({ x + 1, 6 });
                    }
                }
            }
            // Check if spot behind winpos is open
            if (x - 3 >= 0) { // Check if spot exists
                if (board->at(y).at(x - 3) == 0) { // Check if spot is available
                    if (y == 5 || board->at(y + 1).at(x - 3) != 0) { // Check if the marker will be supported
                        winPositions3.push_back(std::make_pair(x - 3, 6));
                    }
                }
            }
        }
        else if (dir == "ver") { // Vertical
            // Don't need to check in front here, because of gravity ensures there will always be a marker under
            if (y - 3 >= 0) { // Check behind
                if (board->at(y - 3).at(x) == 0) {
                    winPositions3.push_back(std::make_pair(x, 6));
                }
            }
        }
        else if (dir == "dr") { // Diagonal right
            if (x + 1 < 7 && y + 1 < 6) {
                if (board->at(y + 1).at(x + 1) == 0) {
                    if (y + 1 == 5 || board->at(y + 2).at(x + 1) != 0) {
                        winPositions3.push_back(std::make_pair(x + 1, 6));
                    }
                }
            }
            if (x - 3 >= 0 && y - 3 >= 0) {
                if (board->at(y - 3).at(x - 3) == 0) {
                    if (board->at(y - 2).at(x - 3) != 0) {
                        winPositions3.push_back(std::make_pair(x - 3, 6));
                    }
                }
            }
        }
        else if (dir == "dl") { // Diagonal left
            if (x - 1 >= 0 && y + 1 < 6) {
                if (board->at(y + 1).at(x - 1) == 0) {
                    if (board->at(y + 2).at(x - 1) != 0) {
                        winPositions3.push_back(std::make_pair(x - 1, 6));
                    }
                }
            }
            if (x + 3 < 7 && y - 3 >= 0) {
                if (board->at(y - 3).at(x + 3) == 0) {
                    if (board->at(y - 2).at(x + 3) != 0) {
                        winPositions3.push_back(std::make_pair(x + 3, 6));
                    }
                }
            }
        }
    }


    //Find AI win positions for 2 in a row
    for (int i{}; i < aWinPos2.size(); i++) {

        std::string dir = std::get<2>(aWinPos2[i]);
        int x = std::get<1>(aWinPos2[i]);
        int y = std::get<0>(aWinPos2[i]);
        bool front = false;
        bool back = false;


        if (dir == "hor") { // Horizontal
            if (x + 1 < 7) {
                if (board->at(y).at(x + 1) == 0) {
                    if (y == 5 || board->at(y + 1).at(x + 1) != 0) {
                        front = true;
                    }
                }
            }
            if (x - 3 >= 0) {
                if (board->at(y).at(x - 2) == 0) {
                    if (y == 5 || board->at(y + 1).at(x - 2) != 0) {
                        back = true;
                    }
                }
            }
            if (front || back) {
                if (front && back) {
                    winPositions2.push_back(std::make_pair(x + 1, 4));
                    winPositions2.push_back(std::make_pair(x - 2, 4));
                }
                else if (front) {
                    winPositions2.push_back(std::make_pair(x + 1, 2));
                }
                else if (back) {
                    winPositions2.push_back(std::make_pair(x - 2, 2));
                }
            }
        }
        else if (dir == "ver") { // Vertical
            // Don't need to check in front here, because of gravity ensures there will always be a marker under
            if (y - 3 >= 0) { // Check behind
                if (board->at(y - 2).at(x) == 0) {
                    winPositions2.push_back(std::make_pair(x, 2));
                }
            }
        }
        else if (dir == "dr") { // Diagonal right
            if (x + 1 < 7 && y + 1 < 6) {
                if (board->at(y + 1).at(x + 1) == 0) {
                    if (y < 4) {
                        if (board->at(y + 2).at(x + 1) != 0) {
                            front = true;
                        }
                    } else if (y == 4) {
                        front = true;
                    }
                }
            }
            if (x - 2 >= 0 && y - 2 >= 0) {
                if (board->at(y - 2).at(x - 2) == 0) {
                    if (board->at(y - 1).at(x - 2) != 0) {
                        back = true;
                    }
                }
            }
            if (front || back) {
                if (front && back) {
                    winPositions2.push_back(std::make_pair(x + 1, 4));
                    winPositions2.push_back(std::make_pair(x - 2, 4));
                }
                else if (front) {
                    winPositions2.push_back(std::make_pair(x + 1, 2));
                }
                else if (back) {
                    winPositions2.push_back(std::make_pair(x - 2, 2));
                }
            }
        }
        else if (dir == "dl") { // Diagonal left
            if (x - 1 >= 0 && y + 1 < 6) {
                if (board->at(y + 1).at(x - 1) == 0) { 
                    if (y < 4) {
                        if (board->at(y + 2).at(x - 1) != 0) {
                            front = true;
                        }
                    }
                    else if (y == 4) {
                        front = true;
                    }
                    
                }
            }
            if (x + 2 < 7 && y - 2 >= 0) {
                if (board->at(y - 2).at(x + 2) == 0) {
                    if (board->at(y - 1).at(x + 2) != 0) {
                        back = true;
                    }
                }
            }
            if (front || back) {
                if (front && back) {
                    winPositions2.push_back(std::make_pair(x - 1, 4));
                    winPositions2.push_back(std::make_pair(x - 1, 4));
                }
                else if (front) {
                    winPositions2.push_back(std::make_pair(x - 1, 2));
                }
                else if (back) {
                    winPositions2.push_back(std::make_pair(x + 2, 2));
                }
            }
        }
    }


    //Find player block positions for 3 in a row
    for (int i{}; i < pWinPos3.size(); i++) {

        std::string dir = std::get<2>(pWinPos3[i]);
        int x = std::get<1>(pWinPos3[i]);
        int y = std::get<0>(pWinPos3[i]);
        

        if (dir == "hor") { // Horizontal
            if (x + 1 < 7) { 
                /* std::get<1>(pWinPos3[i]) returns the horizontal position in the board vector, here I check if that value + 1 is outside the board,
                which will determine if the AI is allowed to place a marker there. Only checking horizontal because the check direction was horizontal. 
                Vertical remanins zero. */
                if (board->at(y).at(x + 1) == 0) { 
                    if (y == 5 || board->at(y + 1).at(x + 1) != 0) { 
                        blockPositions3.push_back(std::make_pair(x + 1, 5));
                    }
                } 
            }
            if (x - 3 >= 0) { 
                if (board->at(y).at(x - 3) == 0) {
                    if (y == 5 || board->at(y + 1).at(x - 3) != 0) { 
                        blockPositions3.push_back(std::make_pair(x - 3, 5));
                    }
                }
            }
        }
        else if (dir == "ver") { // Vertical
            if (y - 3 >= 0) {
                if (board->at(y - 3).at(x) == 0) {
                    blockPositions3.push_back(std::make_pair(x, 5));
                }
            }
        }
        else if (dir == "dr") { // Diagonal right
            if (x + 1 < 7 && y + 1 < 6) {
                if (board->at(y + 1).at(x + 1) == 0) {
                    if (y + 1 == 5 || board->at(y + 2).at(x + 1) != 0) {
                        blockPositions3.push_back(std::make_pair(x + 1, 5));
                    }
                }
            }
            if (x - 3 >= 0 && y - 3 >= 0) {
                if (board->at(y - 3).at(x - 3) == 0) {
                    if (board->at(y - 2).at(x - 3) != 0) {
                        blockPositions3.push_back(std::make_pair(x - 3, 5));
                    }
                }
            }
        }
        else if ( dir == "dl") { // Diagonal left
            if (x - 1 >= 0 && y + 1 < 6) {
                if (board->at(y + 1).at(x - 1) == 0) {
                    if (board->at(y + 2).at(x - 1) != 0) {
                        blockPositions3.push_back(std::make_pair(x - 1, 5));
                    }
                }
            }
            if (x + 3 < 7 && y - 3 >= 0) {
                if (board->at(y - 3).at(x + 3) == 0) {
                    if (board->at(y - 2).at(x + 3) != 0) {
                        blockPositions3.push_back(std::make_pair(x + 3, 5));
                    }
                }
            }
        }
    }

    
    //Find player block positions for 2 in a row
    for (int i{}; i < pWinPos2.size(); i++) {

        std::string dir = std::get<2>(pWinPos2[i]);
        int x = std::get<1>(pWinPos2[i]);
        int y = std::get<0>(pWinPos2[i]);
        bool front = false;
        bool back = false;


        if (dir == "hor") { // Horizontal
            if (x + 1 < 7) {
                if (board->at(y).at(x + 1) == 0) {
                    if (y == 5 || board->at(y + 1).at(x + 1) != 0) {
                        front = true;
                    }
                }
            }
            if (x - 3 >= 0) {
                if (board->at(y).at(x - 2) == 0) {
                    if (y == 5 || board->at(y + 1).at(x - 2) != 0) {
                        back = true;
                    }
                }
            }
            if (front || back) {
                if (front && back) {
                    blockPositions2.push_back(std::make_pair(x + 1, 3));
                    blockPositions2.push_back(std::make_pair(x - 2, 3));
                }
                else if (front) {
                    blockPositions2.push_back(std::make_pair(x + 1, 1));
                }
                else if (back) {
                    blockPositions2.push_back(std::make_pair(x - 2, 1));
                }
            }
        }
        else if (dir == "ver") { // Vertical
            if (y - 3 >= 0) { 
                if (board->at(y - 2).at(x) == 0) {
                    blockPositions2.push_back(std::make_pair(x, 0));
                }
            }
        }
        else if (dir == "dr") { // Diagonal right
            if (x + 1 < 7 && y + 1 < 6) {
                if (board->at(y + 1).at(x + 1) == 0) {
                    if (y < 4) {
                        if (board->at(y + 2).at(x + 1) != 0) {
                            front = true;
                        }
                    }
                    else if (y == 4) {
                        front = true;
                    }
                }
            }
            if (x - 2 >= 0 && y - 2 >= 0) {
                if (board->at(y - 2).at(x - 2) == 0) {
                    if (board->at(y - 1).at(x - 2) != 0) {
                        back = true;
                    }
                }
            }
            if (front || back) {
                if (front && back) {
                    blockPositions2.push_back(std::make_pair(x + 1, 3));
                    blockPositions2.push_back(std::make_pair(x - 2, 3));
                }
                else if (front) {
                    blockPositions2.push_back(std::make_pair(x + 1, 1));
                }
                else if (back) {
                    blockPositions2.push_back(std::make_pair(x - 2, 1));
                }
            }
        }
        else if (dir == "dl") { // Diagonal left
            if (x - 1 >= 0 && y + 1 < 6) {
                if (board->at(y + 1).at(x - 1) == 0) {
                    if (y < 4) {
                        if (board->at(y + 2).at(x - 1) != 0) {
                            front = true;
                        }
                    }
                    else if (y == 4) {
                        front = true;
                    }
                    
                }
            }
            if (x + 2 < 7 && y - 2 >= 0) {
                if (board->at(y - 2).at(x + 2) == 0) {
                    if (board->at(y - 1).at(x + 2) != 0) {
                        back = true;
                    }
                }
            }
            if (front || back) {
                if (front && back) {
                    blockPositions2.push_back(std::make_pair(x - 1, 3));
                    blockPositions2.push_back(std::make_pair(x + 2, 3));
                }
                else if (front) {
                    blockPositions2.push_back(std::make_pair(x - 1, 1));
                }
                else if (back) {
                    blockPositions2.push_back(std::make_pair(x + 2, 1));
                }
            }
        }
    }

    // Winpos3 takes highest priority no matter what
    if (winPositions3.size() > 0) {
        return winPositions3[0].first;
    }


    // Find if there are any multi-block opptertunities
    if (blockPositions3.size() > 0) {
        if (blockPositions3.size() > 1) {
            std::pair <int, int> bp3 = getBestInt(blockPositions3);
            return bp3.first;
        }
        else {
            return blockPositions3[0].first;
        }
    }


    if (winPositions2.size() > 0 && blockPositions2.size() > 0) {
        // Find if there are any multi-block oppertunities
        bool winOK = false;
        bool blockOK = false;
        std::pair <int, int> wp2{};
        std::pair <int, int> bp2{};


        if (winPositions2.size() > 1) {
            wp2 = getBestInt(winPositions2);
            winOK = true;
        }
        if (winPositions2.size() > 1) {
            bp2 = getBestInt(blockPositions2);
            blockOK = true;
        }

        if (winOK && blockOK) {
            if (wp2.second > bp2.second) {
                if (wp2.second != 1) {
                    return wp2.first;
                }
            }
            else {
                if (bp2.second != 1) {
                    return bp2.first;
                }
            }
        }
        else if (winPositions2[0].second > blockPositions2[0].second) {
            if (winPositions2[0].second > 0) {
                return winPositions2[0].first;
            }
        }
        else if (blockPositions2[0].second > 0) {
            return blockPositions2[0].first;
        }
    }
    else if (winPositions2.size() > 0) {
        return winPositions2[0].first;
    }
    else if (blockPositions2.size() > 0) {
        return blockPositions2[0].first;
    }
    
    for (int i{}; i < 7; i++) {
        for (int k{}; k < 6; k++) {
            if (board->at(k).at(i) == 2 && checkAvailablility(board, i).first == true) {
                return i;
            }
            else if (board->at(k).at(i) == 1) {
                break;
            }
        }
    }
    return -1;
}


std::pair <int, int> getBestInt(std::vector <std::pair<int,int>> arr) 
{

    std::vector<std::pair<int, int>> compArr{};
    for (int i{}; i < arr.size(); i++) {
        if (i == 0) {
            compArr.push_back({ arr[i].first, 0 });
        }
        for (int k{}; k < compArr.size(); k++) {
            if (arr[i].first == compArr[k].first) {
                compArr[k].second += 1;
                break;
            }
            if (k == compArr.size() - 1) {
                compArr.push_back({ arr[i].first, 0 });
            }
        }
    }

    std::pair<int, int> bestChoice(0, 0);
    for (int i{}; i < compArr.size(); i++) { // Find element with higest number of duplicates/requests
        if (compArr[i].second > bestChoice.second) {
            bestChoice = compArr[i];
        }
    }

    if (bestChoice.second > 1) {
        bestChoice.second++;
    }

    for (int i{}; i < arr.size(); i++) { // Check if that element can match the priority of the original array
        if (bestChoice.second <= arr[i].second) {
            break;
        }
        if (i == arr.size() - 1) {
        }
    }

    bestChoice = { 0, 0 };
    for (int i{}; i < arr.size(); i++) { 
        if (bestChoice.second < arr[i].second) {
            bestChoice = arr[i];
        }
        if (i == arr.size() - 1) {
            return bestChoice;
        }
    }
}


std::pair <bool, int> checkAvailablility(std::vector<std::vector<int>>* board, int x) {
    for (int i = 5; i >= 0; i--) {
        if (board->at(i).at(x) == 0) {
            return {true, i};
        }
    }
    return {false, -1};
}
