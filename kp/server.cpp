#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string>
#include <sys/types.h>
#include <errno.h>
#include <vector>
#include <fcntl.h>
#include "funcs.hpp"
#include <map>
#include <vector>

class game
{
private:
    
public:
    std::string host_name;
    std::string game_name;
    int max_players;
    int curr_players;
    game(std::string name_host, int max){
        host_name = name_host;
        game_name = "game_" + host_name;
        max_players = max;
        curr_players = 0;
    }
    game(const game &other){
        host_name = other.host_name;
        game_name = other.game_name;
        max_players = other.max_players;
        curr_players = other.curr_players;
    }
    ~game();
};

void game_funk (std::string game_name, std::string game_word, int max_players)
{
    int curr_playrs;
    //мб надо передавать обьект класса гаме
    if (mkfifo(("game_%" + game_name).c_str(), 0777) == -1)
    {
        std::cout << "GAME " << ("game_%" + game_name).c_str() << " FIFO WAS NOT CREATED";
        exit(1);
    }
    //клиент будет кидать запрос в поток со своим ником
    //
}

int in(std::vector<std::string> logins, std::string str)
{
    for (int i = 0; i < logins.size(); ++i)
    {
        if (logins[i] == str)
            return i;
    }
    return -1;
}

int main()
{
    std::vector<std::string> logins;
    std::vector<game> games;
    std::string command;
    std::string login;

    //ввод логинов
    std::cout << "Enter all user's logins. Insert 'end' to stop:\n";
    while (login != "end")
    {
        std::cin >> login;
        if (in(logins, login) == -1)
            logins.push_back(login);
        else
            std::cout << "already exists!";
    }
    //std::cout << "TEST3\n";
    //создание выходных FIFO для всех логинов
    for (int i = 0; i < logins.size(); ++i)
    {
        if (mkfifo(logins[i].c_str(), 0777) == -1)
        {
            if (errno != EEXIST)
            {
                std::cout << "FIFO WAS NOT CREATED";
                exit(1);
            }
        }
    }
    //создание входного FIFO
    if (mkfifo("input", 0777) == -1)
    {
        std::cout << "MAIN INPUT FIFO WAS NOT CREATED";
        exit(1);
    }
    int fd_recv = open("input", O_RDWR);
    if (fd_recv == -1)
    {
        std::cout << "INPUT FIFO WAS NOT OPENED";
        exit(1);
    }

    //открытие всех FIFO на запись
    int fd[logins.size()];
    for (int i = 0; i < logins.size(); ++i)
    {
        fd[i] = open(logins[i].c_str(), O_RDWR);
    }

    while (1)
    {
        std::string message;
        
        message = recieve_message_server(fd_recv);
        //std::cout << message;
        std::string rcvd_name = extract_login(message);          //от кого
        std::string rcvd_command = extract_command(message);     //кому
        std::string rcvd_message = extract_text(message);        //что
        int use_ind = in(logins, rcvd_name);                     //id отправителя
        //std::cout << rcvd_adressee;
        if (rcvd_command == "create")
        {
            game gm(rcvd_name, stoi(rcvd_message));
            games.push_back(gm);
            std::cout << gm.host_name << std::endl;
            //тут создатьь поток на вход которого будет функция игры и аргументы к ней
            std::cout << "test create" << std::endl;
        }
        else if (rcvd_command == "connect")
        {
            std::cout << "test connect" << std::endl;
        }
        else if (rcvd_command == "leave")
        {
            std::cout << "test leave" << std::endl;
        }
        else if (rcvd_command == "shut_down" && rcvd_name == ">admin")
        {
            // отправлять всем клиентам сообщение что сер закрывается 
            // и удалять пайп клиентский потом и маин пайп
        }
    }
    // чтобы завершить сервер корректно надо создать лоргин алмин и подключится к нему
    // через админа будет отправлять запрос на закрытие сервера
    std::remove; //удаляет файл надо удалять пайпы
}