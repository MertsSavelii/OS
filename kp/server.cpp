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
#include <thread>

#define CLIENT_ID(name) in(logins,name)

inline int create_game_pipe(std::string game_name){
    int curr_playrs;
    if (mkfifo(("game_%" + game_name).c_str(), S_IRWXU|S_IRWXG|S_IRWXO) == -1)
    {
        std::cout << "GAME " << ("game_%" + game_name).c_str() << " FIFO WAS NOT CREATED";
        exit(1);
    }
    int game_input_fd = open(("game_%" + game_name).c_str(), O_RDWR);
    if (game_input_fd == -1)
    {
        std::cout << "MAIN INPUT FIFO WAS NOT OPENED";
        exit(1);
    }
    return game_input_fd;
}

void game_funk (std::string game_name, std::string game_word, int max_players)
{
    int curr_playrs;
    int game_input_fd = create_game_pipe(game_name);
    std::string rcvd_name, rcvd_command, rcvd_data;
    while (1)
    {
        recieve_message_server(game_input_fd, &rcvd_name, &rcvd_command, &rcvd_data);
        if (rcvd_command == "connect")
        {

        }
        else if (rcvd_command == "maybe")
        {

        }
        else if (rcvd_command == "leave")
        {
            
        }
        
    }
    
    
}

inline int in(std::vector<std::string> logins, std::string str)
{
    for (int i = 0; i < logins.size(); ++i)
    {
        if (logins[i] == str)
            return i;
    }
    return -1;
}

inline int create_main_pipe() {
    if (mkfifo("main_input", S_IRWXU|S_IRWXG|S_IRWXO) == -1)
    {
        std::cout << "MAIN INPUT FIFO WAS NOT CREATED";
        exit(1);
    }
    int fd_recv = open("main_input", O_RDWR);
    if (fd_recv == -1)
    {
        std::cout << "MAIN INPUT FIFO WAS NOT OPENED";
        exit(1);
    }
    return fd_recv;
}

inline int create_admin_pipe() {
    if (mkfifo("admin", S_IRWXU|S_IRWXG|S_IRWXO) == -1)
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
    return admin_fd;
}

inline int create_client_pipe(std::string rcvd_name) {
    if (mkfifo(rcvd_name.c_str(), S_IRWXU|S_IRWXG|S_IRWXO) == -1)
    {
        std::cout << "CLIENT INPUT FIFO WAS NOT CREATED";
        exit(1);
    }
    int fd = open(rcvd_name.c_str(), O_RDWR);
    if (fd == -1)
    {
        std::cout << "CLIENT INPUT FIFO WAS NOT OPENED";
        exit(1);
    }
    return fd;
}

int main()
{
    std::vector<std::string> logins;
    std::vector<int> client_pipe_fd;
    //std::vector<std::thread> games_threads;
    
    int fd_recv = create_main_pipe();
    int admin_fd = create_admin_pipe();

    std::string login;
    std::string rcvd_name, rcvd_command, rcvd_data; 
    auto iter_fd = client_pipe_fd.cbegin();
    auto iter_log = logins.cbegin();
    while (1)
    {       
        recieve_message_server(fd_recv, &rcvd_name, &rcvd_command, &rcvd_data);

        if (rcvd_command == "login" && rcvd_name != "admin")
        {
            std::cout <<"New client: " << rcvd_name << std::endl;
            std::cout.flush();

            client_pipe_fd.push_back(create_client_pipe(rcvd_name));
            logins.push_back(rcvd_name);
        }
        else if (rcvd_command == "create")
        {
            // std::string game_name_table, game_word;
            // int max_players;
            // extract_game_data(rcvd_data, &game_name_table, &game_word, &max_players);
            // //std::thread g(game_funk, game_name_table, game_word, max_players);
            // //games_threads.push_back(g);
            // // std::cout << "test create" << std::endl;
            send_message_to_client(client_pipe_fd[CLIENT_ID(rcvd_name)],"SERVER CLOSED");
        }
        else if (rcvd_command == "quit")
        {
            close(client_pipe_fd[CLIENT_ID(rcvd_name)]);
            std::remove(rcvd_name.c_str());
            iter_fd = client_pipe_fd.cbegin();
            client_pipe_fd.erase(iter_fd - 1 + CLIENT_ID(rcvd_name));
            iter_log = logins.cbegin();
            logins.erase(iter_log + CLIENT_ID(rcvd_name));
            std::cout << "CLIENT: " << rcvd_name << " LEFT\n";

        }
        else if (rcvd_command == "shut_down" && rcvd_name == "admin")
        {
            for(int i=0 ; i < logins.size(); i++)
            {
                send_message_to_client(client_pipe_fd[i],"SERVER CLOSED");
                std::remove(logins[i].c_str());
                close(client_pipe_fd[i]);
            }
            close(admin_fd);
            std::remove("admin");
            std::remove("main_input");
            std::cout << "CLIENT: " << rcvd_name << " LEFT\n";
            
            return 0;
        }
        else if(rcvd_name != "admin")
        {
            send_message_to_client(client_pipe_fd[CLIENT_ID(rcvd_name)],"NOT A COMMAND");
        }
    }
    // чтобы завершить сервер корректно надо создать лоргин алмин и подключится к нему
    // через админа будет отправлять запрос на закрытие сервера
    // std::remove; //удаляет файл надо удалять пайпы
    //game_thr.detach();
}