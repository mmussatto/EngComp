#include <iostream>
#include <stack>


/*  Prints the stack in reversed order */
void printStackReversed(std::stack<int> s)
{
    if(s.empty())   //base case
        return;

    int temp = s.top();

    s.pop();

    printStackReversed(s);  //recursion
    
    std::cout << temp << "\n";  //print element
    
}

/* Clears the stack */
void clearStack(std::stack<int> *s)
{
    while (!(s->empty()))
        s->pop();
}

/*  Since the first element shown is the top of the stack, all elements must
*  be read before pushing them into the stack.     
*/
void readStack(int n, std::stack<int> *s)
{

    if (n == 0)     //base case
        return;
    

    int temp;
    std::cin >> temp;

    readStack(n-1, s);  //recursion

    s->push(temp);
    
}


int main ()
{
    int nTests, nEntries;

    std::stack<int> s;

    std::cin >> nTests;

    while(nTests--)
    {

        std::cin >> nEntries;

        readStack(nEntries, &s);    //read elements and build stack

        printStackReversed(s);      //print stack in reversed order          

        if (nTests != 0)
        {
            std::cout << "\n";
            clearStack(&s);     //clear stack for other test cases
        }

    }

    return 0;
}