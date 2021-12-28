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
    std::vector<int> client_pipe_fd;
    //std::vector<game> games;

    

    // //ввод логинов
    // std::cout << "Enter all user's logins. Insert 'end' to stop:\n";
    // while (login != "end")
    // {
    //     std::cin >> login;
    //     if (in(logins, login) == -1)
    //         logins.push_back(login);
    //     else
    //         std::cout << "already exists!";
    // }
    // //std::cout << "TEST3\n";
    // //создание выходных FIFO для всех логинов
    // for (int i = 0; i < logins.size(); ++i)
    // {
    //     if (mkfifo(logins[i].c_str(), 0777) == -1)
    //     {
    //         if (errno != EEXIST)
    //         {
    //             std::cout << "FIFO WAS NOT CREATED";
    //             exit(1);
    //         }
    //     }
    // }


    //создание входного FIFO
    if (mkfifo("main_input", 0777) == -1)
    {
        std::cout << "MAIN INPUT FIFO WAS NOT CREATED";
        exit(1);
    }
    int fd_recv = open("input", O_RDWR);
    if (fd_recv == -1)
    {
        std::cout << "MAIN INPUT FIFO WAS NOT OPENED";
        exit(1);
    }

    // открываем пайп админа
    if (mkfifo("admin", 0777) == -1)
    {
        std::cout << "ADMIN INPUT FIFO WAS NOT CREATED";
        exit(1);
    }
    int admin_fd = open("admin", O_RDWR);
    if (admin_fd == -1)
    {
        std::cout << "ADMIN INPUT FIFO WAS NOT OPENED";
        exit(1);
    }

    // //открытие всех FIFO на запись
    // int fd[logins.size()];
    // for (int i = 0; i < logins.size(); ++i)
    //     fd[i] = open(logins[i].c_str(), O_RDWR);

    std::string command;
    std::string login;

    while (1)
    {
        std::string message;
        
        message = recieve_message_server(fd_recv);
        std::string rcvd_name = extract_login(message);          //от кого
        std::string rcvd_command = extract_command(message);     //команда
        std::string rcvd_data = extract_text(message);        //информация
        //int use_ind = in(logins, rcvd_name);                     //id отправителя

        if (rcvd_command == "login")
        {
            logins.push_back();
        }
        else if (rcvd_command == "create")
        {
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
        else if (rcvd_command == "shut_down" && rcvd_name == "admin")
        {
            // отправлять всем клиентам сообщение что сер закрывается 
            // и удалять пайп клиентский потом и маин пайп
        }
    }
    // чтобы завершить сервер корректно надо создать лоргин алмин и подключится к нему
    // через админа будет отправлять запрос на закрытие сервера
    // std::remove; //удаляет файл надо удалять пайпы
}