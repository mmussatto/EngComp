#include<bits/stdc++.h>

int main() 
{
    /*Read number of test cases*/
    std::string sTemp;
    std::getline(std::cin, sTemp);
    int n = std::stoi(sTemp);

    while(n--)
    {
        /*Read expression*/
        std::string s;
        std::getline(std::cin, s);


        int sLength = s.length();
        int currentNumber = 0;
        char currentOperation = '+';

        std::stack<int> stackAdd;   //all numbers will bem summed in the end (Minimum Result)
        std::stack<int> stackMulti; //all numbers will be multiplied in the end (Maximum Result)

        /*Processs expression*/
        for(int i = 0; i < sLength; i++)
        {
            char currentChar = s[i];

            if (currentChar >= '0' && currentChar <= '9') //is a digit
            {
                currentNumber = (currentNumber * 10) + (currentChar - '0');

                if (i != sLength - 1) //if it is not the last element, read next char
                {
                    continue;
                }
            }
            
            if(currentOperation == '+')
            {
                /*Minimum value*/
                stackAdd.push(currentNumber);     

                /*Maximum Value*/
                if (stackMulti.empty())
                    stackMulti.push(0);           //neutral element
                
                int stackMultiTop = stackMulti.top();   
                stackMulti.pop();
                stackMulti.push(currentNumber + stackMultiTop); //makes the addition
            } 
            else if (currentOperation == '*')
            {
                /*Minimum value*/
                if (stackAdd.empty())
                    stackAdd.push(1);           //neutral element

                int stackAddTop = stackAdd.top();
                stackAdd.pop();
                stackAdd.push(currentNumber * stackAddTop); //makes the multiplication

                /*Maximum value*/
                stackMulti.push(currentNumber);
            }

            currentOperation = currentChar; //next operation
            currentNumber = 0;              //reset current number
       }

        /*Minimum result*/
        long int resultMin = 0;
        while (!stackAdd.empty())
        {
            resultMin += stackAdd.top();
            stackAdd.pop();
        }

        /*Maximum result*/
        long long int resultMax = 1;
        while (!stackMulti.empty())
        {
            resultMax *= stackMulti.top();
            stackMulti.pop();
        }
        
        /*Prints message*/
        std::cout << "The maximum and minimum are " << resultMax << " and " << resultMin << ".\n";
    }
    
    return 0;
}