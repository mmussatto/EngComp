#include<bits/stdc++.h>

int main() 
{
    std::string sTemp;

    std::getline(std::cin, sTemp);
    int n = std::stoi(sTemp);

    while(n--)
    {
        std::string s;
        std::getline(std::cin, s); //read expression

        int sLength = s.length();
        int currentNumber = 0;
        char currentOperation = '+';

        std::stack<int> stackAdd;   //all numbers will bem summed in the end (Minimum Result)
        
        std::stack<int> stackMulti; //all numbers will be multiplied in the end (Maximum Result)

        for(int i = 0; i < sLength; i++)
        {
            char currentChar = s[i];
            if (currentChar >= '0' && currentChar <= '9') //is a digit
            {
                currentNumber = (currentNumber * 10) + (currentChar - '0');
                if (i != sLength - 1)
                {
                    continue;
                }
            }
            
            if(currentOperation == '+')
            {
                stackAdd.push(currentNumber);

                if (stackMulti.empty())
                    stackMulti.push(0);           //neutral element
                
                int stackMultiTop = stackMulti.top();
                stackMulti.pop();
                stackMulti.push(currentNumber + stackMultiTop);
            } 
            else if (currentOperation == '*')
            {
                if (stackAdd.empty())
                    stackAdd.push(1);           //neutral element

                int stackAddTop = stackAdd.top();
                stackAdd.pop();
                stackAdd.push(currentNumber * stackAddTop);

                stackMulti.push(currentNumber);
            }

            currentOperation = currentChar;
            currentNumber = 0;
            
        }


        long int resultMin = 0;
        while (!stackAdd.empty())
        {
            resultMin += stackAdd.top();
            stackAdd.pop();
        }

        long long int resultMax = 1;
        while (!stackMulti.empty())
        {
            resultMax *= stackMulti.top();
            stackMulti.pop();
        }
        


        std::cout << "The maximum and minimum are " << resultMax << " and " << resultMin << ".\n";

    }
    return 0;
}