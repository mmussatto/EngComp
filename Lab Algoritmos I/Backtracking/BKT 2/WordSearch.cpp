#include <iostream>
#include <vector>
#include <string>

/*  backtraking algorithm to find the rest of the word in the board*/
bool LetterInBoard(std::vector<std::vector<char>> &board, std::string word, int k, int index, int x, int y)
{
    //found the entire word
    if(index == k)  
        return true;

    //verifying if position is valid
    //integer casting necessary because of RunCodes.com compiler
    if(x < 0 || x >= (int)board.size() || y < 0 || y >= (int)board[0].size() || board[x][y] != word[index])
        return false;

    
    char letter = board[x][y];  //save letter
    board[x][y] = '*';          //change letter on the board

    //backtraking in all four directions
    bool found_letter = LetterInBoard(board, word, k, index+1, x-1, y) ||
                        LetterInBoard(board, word, k, index+1, x+1, y) ||
                        LetterInBoard(board, word, k, index+1, x, y+1) ||
                        LetterInBoard(board, word, k, index+1, x, y-1);

    board[x][y] = letter;   //reverse letter to the board

    return found_letter;
}

/*  iterate through all the letters in the board until the first letter of the word is found;
    then, iniciate a backtraking search to find the rest of the word in the board*/
bool WordInBoard(std::vector<std::vector<char>> &board, std::string word, int k)
{  
    
    for (size_t i = 0; i < board.size(); i++)           //iterate through rows
    {
        for (size_t j = 0; j < board[i].size(); j++)    //iterate through columns
        {
            if(board[i][j] != word[0])  //letter is not the first in word
                continue;

            if(LetterInBoard(board, word, k, 0, i, j)) //backtraking search for the word.
                return true;
        }
    }

    //no solution was found
    return false;
}


int main ()
{
    std::vector<std::vector<char>> board;

    int n, m, k;    //n-> number of rows, m-> number of columns, k-> length of the word
    std::string word;

    //read size of the board
    std::cin >> n >> m;

    //read board
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

    //read size of the word and word 
    std::cin >> k; 
    std::cin >> word;


    if(WordInBoard(board, word, k))
        std::cout << "Yes";
    else
        std::cout << "No";

    return 0;
}