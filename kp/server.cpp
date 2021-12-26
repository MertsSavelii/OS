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



int main()
{
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
    
    while(1)
    {
        std::string message;
        message = recieve_message_server(fd_recv);
        std::cout << message;

    }
    
    return 0;
}