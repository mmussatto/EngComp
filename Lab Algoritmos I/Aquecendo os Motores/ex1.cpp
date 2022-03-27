#include <iostream>
#include <map>
#include <string>

int main () 
{
    std::map<std::string, std::string> servers; //map names to ips 

    std::string name;       //name of the server
    std::string ip;         //ip of the server
    std::string command;    

    int n_servers, n_commands;

    std::cin >> n_servers;
    std::cin >> n_commands;

    while (n_servers--) //read servers
    {
        std::cin >> name;
        std::cin >> ip;

        servers[ip] = name;
    }    

    while (n_commands--) //read commands
    {
        std::cin >> command;
        std::cin >> ip;

        std::string temp = ip;
        temp.pop_back(); //removes the ';' at the end

        std::cout << command << " " << ip << " #" << servers[temp] << "\n";
    }
    
    return 0;
}

/*Alternativa: salvar os nomes no hashmap num ip já com ';'. Assim, não precisa criar a string temp para remover o ';'*/