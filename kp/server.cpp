#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <vector>
#include <fcntl.h>
#include <map>
#include "funk.hpp"
#include <vector>

int in(std::vector<std::string> logins, std::string str)
{
    if(logins.empty())
        return -1;
    for (int i = 0; i < logins.size(); ++i)
    {
        if (logins[i] == str)
            return i;
    }
    return -1;
}

int main()
{
    std::cout << "test1";
    if (mkfifo("input", 0777) == -1)
    {
        std::cout << "MAIN INPUT FIFO WAS NOT CREATED";
        exit(1);
    }
    std::cout<<"test1";
    int fd_recv = open("input", O_RDWR);
    if (fd_recv == -1)
    {
        std::cout << "INPUT FIFO WAS NOT OPENED";
        exit(1);
    }
    std::cout<<"test1";
    std::vector <std::string> logins;
    std::vector <int> fd_clients;
    std::cout<<"test1";
    for(;;)
    {
        std::cout<<"test1";
        std::string message;
        message = recieve_message_server(fd_recv);//получение сообщение от клиента
        std::cout<<"test2";
        std::cout << message;
        if (extract_addressee(message) == "login")
        {
            std::string reply;
            std::cout<<"test2";
            // if (in(logins, extract_login(message)) != -1)
            // {
            //     logins.push_back(extract_login(message));
            //     reply = "login success";

            //     if (mkfifo(extract_login(message).c_str(), 0777) == -1)
            //     {
            //         if (errno != EEXIST)
            //         {
            //             std::cout << "FIFO WAS NOT CREATED";
            //             exit(1);
            //         }
            //     }
            //     int new_fd = open("input", O_RDWR);
            //     fd_clients.push_back(new_fd);
            // }
            // else 
            // {
            //     reply = "alredy exists";
            // }

            // send_message_to_client(fd_clients[in(logins, extract_login(message))], reply);
        }
    }
    
    return 0;
}