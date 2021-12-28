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

#define SEND_TO_SERVER(FD) send_message_to_server(FD, login, command, message)

//функция приёма сообщений (для потока)
void func(int fd_respond, std::string login)
{
    while (1)
    {
        std::string respond = recieve_message_client(fd_respond);
        std::cout << "\n" << respond << "\n";
        std::cout.flush();
        if (respond == "SERVER CLOSED")
            exit(0);
        std::cout << login << "> ";
        std::cout.flush();
    }
}

inline void write_intro() {
    std::cout << "Добро пожаловать в игру Быки и Коровы.\nЧтобы создать аккаунт запустите ./server и введите там свой логи\n";
    std::cout <<  "Затем перезапустите клиент и впишите совй логин\n";
    std::cout << "Введите свой логин: ";
    std::cout.flush();
}

inline void write_menu(std::string login){
    std::cout << "Соединение установлено, можете отдавать команды\n";
    std::cout << "Список команд:\n";
    std::cout << "1) create @название игрового стола@ @игровое слово@ @максимальное количество игроков@\n";
    std::cout << "2) connect @название игры@\n";
    std::cout << "3) leave\n";
    if (login != "admin")std::cout << "4) quit\n";
    if (login == "admin") std::cout << "5) shut_down - выключение сервера\n";
    std::cout.flush();
}

inline int server_main_input_fd(){

    int fd = open("main_input", O_RDWR);
    if (fd == -1)
    {
        std::cout << "ERROR: MAIN FIFO WAS NOT OPENED\n";
        exit(1);
    }
    return fd;
}



int main()
{
    int client_main_out_fd = server_main_input_fd();

    write_intro();
    std::string login;
    std::cin >> login;
    send_message_to_server(client_main_out_fd, login, "login", "");
    
    sleep(1);
    int fd_respond = open(login.c_str(), O_RDWR);
    if (fd_respond == -1)
    {
        std::cout << "RESPOND FIFO WAS NOT OPENED";
        exit(1);
    }

    
    write_menu(login);
    std::thread thr_respond(func, fd_respond, login);

    std::string command, message;
    std::string game_name_table, game_word;
    int max_players, game_fd;

    while (1)
    {
        std::cout << login << "> ";
        std::cin >> command;
        
        if (command == "create")
        {
            std::cin >> game_name_table >> game_word >> max_players;
            message = game_name_table + "$" + game_word + "$" + std::to_string(max_players);
            SEND_TO_SERVER(client_main_out_fd);
        }
        else if (command == "connect")
        {
            std::string game_name;
            std::cin >> game_name;
            game_fd = open(game_name.c_str(), O_RDWR);
            if (game_fd == -1)
            {
                std::cout << "ERROR: GAME NOT FOUND\n";
                std::cout.flush();
            }
            else
            {
                message = "";
                SEND_TO_SERVER(game_fd);
                while (1)
                {
                    std::cout << game_name << "> ";
                    std::cin >> command;

                    if (command == "maybe")
                    {
                        //std::cout << "Введити слово: ";
                        std::cout.flush();
                        std::cin >> message;
                        SEND_TO_SERVER(game_fd);
                    }
                    else if (command == "leave")
                    {
                        message = "";
                        SEND_TO_SERVER(game_fd);
                    }
                }
            }
        }
        else if (command == "quit" && login != "admin")
        {
            message = "";
            SEND_TO_SERVER(client_main_out_fd);
            thr_respond.detach();
            return 0;
        }
        else if (command == "shut_down" && login == "admin")
        {
            message = "";
            SEND_TO_SERVER(client_main_out_fd);
            thr_respond.detach();
            return 0;
        }
    }
    return 0;
}