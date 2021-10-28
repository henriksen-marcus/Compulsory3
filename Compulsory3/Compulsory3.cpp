#include <iostream>
#include <vector>


int main()
{
    std::vector <std::vector <char>> board{};
    int counter{};
    int k{};

    for (int i{}; i < board.size(); i++) {
        if (board[i][k] == 'X') {
            counter++;
        }
        else {
            counter = 0;
        }
        k++;
    }
}