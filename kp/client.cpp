#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <vector>
#include <fcntl.h>
#include "funcs.hpp"
#include <thread>

#define SEND_TO_SERVER send_message_to_server(main_output_fd, login, command, message)

//функция приёма сообщений (для потока)
void func(int fd_respond, std::string login)
{
    while (1)
    {
        std::string reply = recieve_message_client(fd_respond);
        std::cout << reply << "\n";
        std::cout.flush();
        std::cout << login << ">";
        std::cout.flush();
    }
}
int main()
{
    //подключение к входному FIFO сервера
    int main_output_fd = open("main_input", O_RDWR);
    if (main_output_fd == -1)
    {
        std::cout << "ERROR: MAIN FIFO WAS NOT OPENED\n";
        exit(1);
    }

    //подготовка - инструкции, ввод логина
    std::cout << "Добро пожаловать в игру Быки и Коровы.\nЧтобы создать аккаунт запустите ./server и введите там свой логи\n";
    std::cout <<  "Затем перезапустите клиент и впишите совй логин\n";
    std::cout << "Введите свой логин: ";
    std::string login;

    // логинимся и открываем пайп для получения ответов от серва
    std::cin >> login;
    send_message_to_server(main_output_fd, login, "login", "");
    int fd_respond = open(login.c_str(), O_RDWR);
    if (fd_respond == -1)
        std::cout << "RESPOND FIFO WAS NOT OPENED";

    // //подключение к персональному именованному пайпу
    // int fd_recv = -1;
    // while (fd_recv == -1)
    // {
    //     std::cin >> login;
    //     fd_recv = open(login.c_str(), O_RDWR);
    //     if (fd_recv == -1)
    //     {
    //         std::cout << "Wrong login!\nInsert your login: ";
    //     }
    // };

    //вход успешен, запуск потока принятия сообщений от сервера
    
    std::cout << "Соединение установлено, можете отдавать команды\n";
    std::cout << "Список команд:\n";
    std::cout << "1) create @название игрового стола@ @игровое слово@ @максимальное количество игроков@\n";
    std::cout << "2) connect @название игры@\n";
    std::cout << "3) leave\n";
    std::cout << "4) quit\n";
    if (login == "admin") std::cout << "5) shut_down - выключение сервера\n";

    std::thread thr_recieve(func, fd_respond, login);

    std::string command, message;
    //запуск цикла отправки сообщений на сервер
    while (1)
    {
        std::cout << login << "> ";
        std::cin >> command;
        
        if (command == "create")
        {
            std::string name_game_table;
            std::string game_word;
            int max_players;
            std::cin >> name_game_table >> game_word >> max_players;
            message = name_game_table + "$" + game_word + "$" + std::to_string(max_players);
            SEND_TO_SERVER;
        }
        else if (command == "connect")
        {
            std::string game_name;
            std::cin >> game_name;
            message = game_name;
            SEND_TO_SERVER;
        }
        else if (command == "leave")
        {
            message = "";
            SEND_TO_SERVER;
        }
        else if (command == "quit")
        {
            message = "";
            SEND_TO_SERVER;
        }
        else if (command == "shut_down" && login == "admin")
        {
            message = "";
            SEND_TO_SERVER;
        }
        // if (command == "history")
        // {
        //     std::string pattern;
        //     std::getline(std::cin, pattern);
        //     send_message_to_server(fd_main_output, login, command, pattern);
        // }
        // else
        // {
        //     if (command == "quit")
        //         break;
        //     std::cin >> message;
        //     send_message_to_server(fd_main_output, login, command, message);
        // }
    }
    //return 0;
    thr_recieve.detach();
}