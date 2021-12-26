#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <vector>
#include <fcntl.h>
#include "funk.hpp"
#include <thread>

int main()
{
    //подключение к входному FIFO сервера
    int fd_send = open("input", O_RDWR);
    if (fd_send == -1)
    {
        std::cout << "ERROR: MAIN FIFO WAS NOT OPENED\n";
        exit(1);
    }
    std::cout << "Insert your login: ";
    std::string login;
    std::cin >> login;
    send_message_to_server(fd_send, login, "login", "");
    int fd_pers = open(login.c_str(), O_RDWR);
    std::string message = recieve_message_client(fd_pers);
    std::cout << message << "test5";

    // while (1)
    // {
    //     std::cout << login << "> ";
    //     std::cin >> adressee;
    //     if (adressee == "history")
    //     {
    //         std::string pattern;
    //         std::getline(std::cin, pattern);
    //         send_message_to_server(fd_send, login, adressee, pattern);
    //     }
    //     else
    //     {
    //         if (adressee == "quit")
    //             break;
    //         std::getline(std::cin, message);
    //         send_message_to_server(fd_send, login, adressee, message);
    //     }
    // }
    return 0;
}