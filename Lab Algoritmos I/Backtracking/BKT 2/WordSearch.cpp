#include <iostream>
#include <vector>
#include <string>

bool LetterInBoard(std::vector<std::vector<char>> &board, std::string word, int k, int index, int x, int y)
{
    if(index == k)
        return true;

    if(x < 0 || x >= (int)board.size() || y < 0 || y >= (int)board[0].size() || board[x][y] != word[index])
        return false;


    char letter = board[x][y];
    board[x][y] = '*';

    bool found_letter = LetterInBoard(board, word, k, index+1, x-1, y) ||
                        LetterInBoard(board, word, k, index+1, x+1, y) ||
                        LetterInBoard(board, word, k, index+1, x, y+1) ||
                        LetterInBoard(board, word, k, index+1, x, y-1);

    board[x][y] = letter;

    return found_letter;
}

bool WordInBoard(std::vector<std::vector<char>> &board, std::string word, int k)
{  
    for (size_t i = 0; i < board.size(); i++)   //iterate through rows
    {
        for (size_t j = 0; j < board[i].size(); j++)    //iterate through columns
        {
            if(board[i][j] != word[0])  //letter is not the first in word
                continue;

            if(LetterInBoard(board, word, k, 0, i, j))
                return true;
        }
    }

    return false;
}

int main ()
{
    std::vector<std::vector<char>> board;

    int n, m, k;
    std::string word;

    std::cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        std::vector<char> row;
        for (int j = 0; j < m; j++)
        {
            char letter;
            std::cin >> letter;

            row.push_back(letter);
        }
        board.push_back(row);
    }
    
    std::cin >> k; //read size of the word
    std::cin >> word;

    if(WordInBoard(board, word, k))
        std::cout << "Yes";
    else
        std::cout << "No";

    return 0;
}