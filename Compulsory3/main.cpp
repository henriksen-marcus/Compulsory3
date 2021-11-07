#include "declarations.h"

std::pair <int, int> winPos{};
std::string dir{};

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
    Player* p1 = new Player();
    Player* p2 = new Player();
    Player* currentPlayer = p1;
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
    std::vector <std::vector <int>> board{};
    std::pair <bool, int> returnResult (false, 0);

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

        if (currentPlayer == p1) {
            checkInput(&board, currentPlayer, p1, p2);
            
        }
        else {
            aiMove(&board, currentPlayer, p1, p2);
        }

        
        returnResult = checkWin(&board);

        if (returnResult.first) { // If game is won
            printBoard(&board, aiMode, currentPlayer, p1, p2);
            if (returnResult.second == 1) {
                std::cout << p1->name << " has won!" << std::endl;
            }
            else if (returnResult.second == 2) {
                std::cout << p2->name << " has won!" << std::endl;
            }
            system("pause");
            break;
        }  
    }
    saveGamePrompt(&board, p1, p2);
}


void saveGamePrompt(std::vector<std::vector<int>>* board, Player* p1, Player* p2) {
    
    int pos{ 1 };

    while (true) {
        std::cout << "Do you want to save the game?: " << std::endl << std::endl;

        if (pos == 1) { std::cout << pC << " > "; }
        std::cout << "Yes" << reset << std::endl;
        if (pos == 2) { std::cout << pC << " > "; }
        std::cout << "No" << reset << std::endl;
        std::cout << std::endl;

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
            if (pos == 1) {
                saveGame(board, p1, p2);
                std::cout << std::endl;
                std::cout << "Saving game..." << std::endl;
                Sleep(300);
            }
            return;
            break;
        }
    }
}


void printBoard(std::vector<std::vector<int>>* board, bool aiMode, Player* &currentPlayer, Player* &p1, Player* &p2) 
{
    system("cls");
    /*if (aiMode) { std::cout << "Player versus AI." << std::endl; }
    else { std::cout << "Player versus player." << std::endl; }*/

    std::cout << std::endl;

    std::cout << "Move: " << pC << "   [A - D]" << std::endl;
    std::cout << pW << "Confirm: " << pC << "[ENTER]" << reset << std::endl << std::endl;

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
 
    

    std::vector <std::vector<int>> arr{};
    std::vector <int> temp{};
    if (dir != "") {
        if (dir == "hor") {
            arr.push_back({ winPos.first, winPos.second });
            arr.push_back({ winPos.first, winPos.second-1 });
            arr.push_back({ winPos.first, winPos.second-2 });
            arr.push_back({ winPos.first, winPos.second-3 });
        }
        else if (dir == "ver") {
            arr.push_back({ winPos.first, winPos.second });
            arr.push_back({ winPos.first-1, winPos.second });
            arr.push_back({ winPos.first-2, winPos.second });
            arr.push_back({ winPos.first-3, winPos.second });
        }
        else if (dir == "dr") {
            arr.push_back({ winPos.first, winPos.second });
            arr.push_back({ winPos.first - 1, winPos.second - 1 });
            arr.push_back({ winPos.first - 2, winPos.second - 2 });
            arr.push_back({ winPos.first - 3, winPos.second - 3 });
        }
        else if (dir == "dl") {
            arr.push_back({ winPos.first, winPos.second });
            arr.push_back({ winPos.first - 1, winPos.second + 1 });
            arr.push_back({ winPos.first - 2, winPos.second + 2 });
            arr.push_back({ winPos.first - 3, winPos.second + 3 });
        }
    }


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
    bool stop = false;

    for (int y{}; y < ROW_HEIGHT; y++) { 
        std::cout << "|";
        
        for (int x{}; x < ROW_WIDTH; x++) {
            stop = false;
            if (dir != "") {
                for (int g{}; g < arr.size(); g++) {
                    if (arr[g][0] == y && arr[g][1] == x) {
                        std::cout << pR << termcolor::on_bright_cyan << " O " << reset;
                        stop = true;
                        break;
                    }
                }
            }
            if (stop) { continue; }
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


void checkInput(std::vector<std::vector<int>>* board, Player* &currentPlayer, Player* &p1, Player* &p2)
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
    if (currentPlayer == p1) {
        p2->pos = p1->pos;
    }
    else {
        p1->pos = p2->pos;
    }
}


void insertMarker(std::vector<std::vector<int>>* board, Player*& currentPlayer, Player*& p1, Player*& p2)
{
    for (int i = ROW_HEIGHT - 1; i >= 0; i--) {
        if (board->at(i).at(currentPlayer->pos) == 0) {
            board->at(i).at(currentPlayer->pos) = currentPlayer->marker;
            if (currentPlayer == p1) {
                currentPlayer = p2;
            }
            else {
                currentPlayer = p1;
            }
            return;
        }
    }
    std::cout << "No available spaces!" << std::endl;
    Sleep(600);
}


std::pair<bool, int> checkWin(std::vector<std::vector<int>>* board)
{
    int p1Counter{}, p2Counter{};

    // Horizontal
    for (int i{}; i < ROW_HEIGHT; i++) {
        p1Counter = 0;
        p2Counter = 0;
        for (int k{}; k < ROW_WIDTH; k++) {
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
                winPos.first = i;
                winPos.second = k;
                dir = "hor";
                return std::make_pair(true, board->at(i).at(k));
            }
        }
    }

    p1Counter = 0;
    p2Counter = 0;

    // Vertical
    for (int i{}; i < ROW_WIDTH; i++) {
        p1Counter = 0;
        p2Counter = 0;
        for (int k{}; k < ROW_HEIGHT; k++) {
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
                winPos.first = k;
                winPos.second = i;
                dir = "ver";
                return std::make_pair(true, board->at(k).at(i));
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
        p1Counter = 0;
        p2Counter = 0;
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
            else {
                p1Counter = 0;
                p2Counter = 0;
            }
            if (p1Counter == 4 || p2Counter == 4) {
                winPos.first = v;
                winPos.second = h;
                dir = "dr";
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
        p1Counter = 0;
        p2Counter = 0;
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
            else {
                p1Counter = 0;
                p2Counter = 0;
            }
            if (p1Counter == 4 || p2Counter == 4) {
                winPos.first = v;
                winPos.second = h;
                dir = "dr";
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
                winPos.first = v;
                winPos.second = h;
                dir = "dl";
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
                winPos.first = v;
                winPos.second = h;
                dir = "dl";
                return std::make_pair(true, board->at(v).at(h));
            }
            h--;
        }
        z++;
    }
    return std::make_pair(false, 0);
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
    file << p1->score << "\n";

    file << p2->name << "\n";
    file << p2->color << "\n";
    file << p2->score << "\n";

    std::stringstream textBoard{};

    for (int i{}; i < board->size(); i++) {
        for (int k{}; k < board->at(0).size(); k++) {
            textBoard << board->at(i).at(k);
        }
    }

    file << textBoard.str() << "\n";


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
        int p1Score{};
        std::string p2Name;
        int p2Color{};
        int p2Score{};
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


    for (int i{}; i < fileLength; i += 7) {
        temp.p1Name = fileInfo[i];
        temp.p1Color = std::stoi(fileInfo[i + 1]);
        temp.p1Score = std::stoi(fileInfo[i + 2]);

        temp.p2Name = fileInfo[i + 3];
        temp.p2Color = std::stoi(fileInfo[i + 4]);
        temp.p2Score = std::stoi(fileInfo[i + 5]);

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

        /*for (int j{}; j < ROW_HEIGHT; j++) {
            horizontalLines.push_back(fileInfo[i + 6].substr(i * 6, 7));
        }


        for (int k{}; k < ROW_HEIGHT; k++) {
            std::vector <int> temp1{};
            for (int l{}; l < 7; l++) {
                temp1.push_back(horizontalLines[k][l]);
            }
            temp.board.push_back(temp1);
        }*/
    }


    std::cout << pT << termcolor::bright_blue << " Saved Games " << reset << reset << std::endl << std::endl;

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

        


        for (int j{}; j < ROW_HEIGHT; j++) {
            std::cout << "|";
            for (int k{}; k < ROW_WIDTH; k++) {
                if (saveGames[i].board[j][k] == '0') {
                    std::cout << " X ";
                }
                else if (saveGames[i].board[j][k] == '1') {
                    switch (saveGames[i].p1Color) {
                    case 1:
                        std::cout << pR << " O " << reset;
                        break;
                    case 2:
                        std::cout << pG << " O " << reset;
                        break;
                    case 3:
                        std::cout << pB << " O " << reset;
                        break;
                    case 4:
                        std::cout << pY << " O " << reset;
                        break;
                    }
                }
                else if (saveGames[i].board[j][k] == '2') {
                    switch (saveGames[i].p2Color) {
                    case 1:
                        std::cout << pR << " O " << reset;
                        break;
                    case 2:
                        std::cout << pG << " O " << reset;
                        break;
                    case 3:
                        std::cout << pB << " O " << reset;
                        break;
                    case 4:
                        std::cout << pY << " O " << reset;
                        break;
                    }
                }
                
            }
            std::cout << "|" << std::endl;
        }
        std::cout << row << std::endl;
        std::cout << std::endl << std::endl << std::endl;
    }
    system("pause");
}


void aiMove(std::vector<std::vector<int>>* board, Player* &currentPlayer, Player* &p1, Player* &p2) {
    std::vector<int> blockpos = getAiInfo(board);
    if (blockpos.size() != 0) {
        p2->pos = blockpos[0];
    }
    else {
        p2->pos = rand() % 6 + 1;
    }
    std::cout << p2->pos << std::endl;
    system("pause");
    insertMarker(board, currentPlayer, p1, p2);
}

std::vector<int> getAiInfo(std::vector<std::vector<int>>* board) {
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

        for (int i{}; i < ROW_HEIGHT; i++) {
            p1Counter = 0;
            p2Counter = 0;
            for (int k{}; k < ROW_WIDTH; k++) {
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
        for (int i{}; i < ROW_WIDTH; i++) {
            p1Counter = 0;
            p2Counter = 0;
            for (int k{}; k < ROW_HEIGHT; k++) {
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
                    pWinPosCurrent.push_back(std::make_tuple(i, k, "ver"));
                }
                if (p2Counter == checkLen) {
                    aWinPosCurrent.push_back(std::make_tuple(i, k, "ver"));
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
            p1Counter = 0;
            p2Counter = 0;
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
        while (z <= max_h) {
            h = z; // Change start position
            p1Counter = 0;
            p2Counter = 0;
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
        while (z <= max_v) {
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
        while (z < max_h) {
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
    std::vector<int> blockPositions3{};
    std::vector<int> blockPositions2{};

    //Find AI block positions
    for (int i{}; i < pWinPos3.size(); i++) { // Notice how I am only pushing back the horizontal position

        std::string dir = std::get<2>(pWinPos3[i]);
        int x = std::get<1>(pWinPos3[i]);
        int y = std::get<0>(pWinPos3[i]);
        

        if (dir == "hor") { // Horizontal
            // Check if spot in front to winpos is open
            if (x + 1 < 7) { // Check if spot exists
                /* std::get<1>(pWinPos3[i]) returns the horizontal position in the board vector, here I check if that value + 1 is outside the board,
                which will determine if the AI is allowed to place a marker there. Only checking horizontal because the check direction was horizontal. 
                Vertical remanins zero. */
                if (board->at(y).at(x + 1) == 0) { // Check if spot is available
                    if (y == 0 || board->at(y + 1).at(x + 1) != 0) { // Check if the marker will be supported (gravity)
                        blockPositions3.push_back(x + 1);
                    }
                } 
            }
            // Check if spot behind winpos is open
            if (x - 3 >= 0) { // Check if spot exists
                if (board->at(y).at(x - 3) == 0) { // Check if spot is available
                    if (board->at(x - 3).at(y + 1) != 0) { // Check if the marker will be supported
                        blockPositions3.push_back(x - 3);
                    }
                }
                
            }
        }
        else if (dir == "ver") { // Vertical
            // Don't need to check in front here, because of gravity ensures there will always be a marker under
            if (y - 3 >= 0) { // Check behind
                if (board->at(y - 3).at(x) == 0) {
                    blockPositions3.push_back(x);
                }
            }
        }
        else if (dir == "dr") { // Diagonal right
            if (x + 1 < 7 && y + 1 < 6) {
                if (board->at(y + 1).at(x + 1) == 0) {
                    if (y + 1 == 5 || board->at(y + 2).at(x + 1) != 0) {
                        blockPositions3.push_back(x + 1);
                    }
                }
            }
            if (x - 3 >= 0 && y - 3 >= 0) {
                if (board->at(y - 3).at(x - 3) == 0) {
                    if (board->at(y - 2).at(x - 3) != 0) {
                        blockPositions3.push_back(x - 3);
                    }
                }
            }
        }
        else if ( dir == "dl") { // Diagonal left
            if (x - 1 >= 0 && y + 1 < 6) {
                if (board->at(y + 1).at(x - 1) == 0) {
                    if (board->at(y + 2).at(x - 1) != 0) {
                        blockPositions3.push_back(x - 1);
                    }
                }
            }
            if (x + 3 < 7 && y - 3 >= 0) {
                if (board->at(y - 3).at(x + 3) == 0) {
                    if (board->at(y - 2).at(x + 3) != 0) {
                        blockPositions3.push_back(x + 3);
                    }
                }
            }
        }
    }

    return blockPositions3;

}
