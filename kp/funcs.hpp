#include <string>

//отправить сообщение серверу в удобной форме - логин$команда$сообщение
void send_message_to_server(int fd, std::string curlogin, std::string command, std::string data)
{
    std::string text = curlogin + "$" + command + "$" + data;
    int k = text.size();
    write(fd, &k, sizeof(k));
    char messagec[k];
    for (int i = 0; i < k; ++i)
        messagec[i] = text[i];

    write(fd, messagec, k);
}
//отправить сообщение клиенту
void send_message_to_client(int fd, std::string message)
{
    std::string text = message;
    int k = text.size();
    write(fd, &k, sizeof(k));
    char messagec[k];
    for (int i = 0; i < k; ++i)
        messagec[i] = text[i];
    write(fd, messagec, k);
}

//получить сообщение в удобной для клиента форме
std::string recieve_message_client(int fd)
{
    int size;
    read(fd, &size, sizeof(size));

    char messagec[size];
    read(fd, messagec, size);

    std::string recv;
    for (int i = 0; i < size; ++i)
    {
        if (messagec[i] != '$')
            recv.push_back(messagec[i]);
        else
            recv = recv + ": ";
    }
    return recv;
}

//получить сообщение в удобной для сервера форме
void recieve_message_server(int fd, std::string *rcvd_name, std::string *rcvd_command, std::string *rcvd_data)
{
    int size;
    read(fd, &size, sizeof(size));

    char messagec[size];
    read(fd, messagec, size);

    std::string recv;
    for (int i = 0; i < size; ++i)
        recv.push_back(messagec[i]);
    
    *rcvd_name = extract_login(recv);
    *rcvd_command = extract_command(recv);
    *rcvd_data = extract_data(recv);
    //return recv;
}

//получить логин из сообщения для сервера
std::string extract_login(std::string message)
{
    std::string login;
    int i = 0;
    while (message[i] != '$')
    {
        login.push_back(message[i]);
        ++i;
    }
    return login;
}

//получить сообщение для клиента
std::string extract_command(std::string message)
{
    std::string command;
    int i = 0;
    while (message[i] != '$')
        ++i;
    ++i;
    while (message[i] != '$')
    {
        command.push_back(message[i]);
        ++i;
    }
    return command;
}

//получить получателя сообщения
std::string extract_data(std::string message)
{
    std::string data;
    int i = 0;
    while (message[i] != '$')
        ++i;
    ++i;
    while (message[i] != '$')
        ++i;
    ++i;
    while (i < message.size())
    {
        data.push_back(message[i]);
        ++i;
    }
    return data;
}

// //получить текст сообщения
// std::string extract_text(std::string message)
// {
//     std::string text;
//     int i = 0;
//     while (message[i] != '$')
//         ++i;
//     ++i;
//     while (message[i] != '$')
//         ++i;
//     ++i;
//     ++i;
//     while (i < message.size())
//     {
//         text.push_back(message[i]);
//         ++i;
//     }
//     return text;
// }

//обычный поиск подстроки
// bool search(std::string text, std::string pattern)
// {
//     if (pattern.size() <= text.size())
//         for (int i = 0; i <= text.size() - pattern.size(); ++i)
//         {
//             std::string pat;
//             for (int z = 0; z < pattern.size(); ++z)
//                 if (text[i + z] == pattern[z])
//                     pat.push_back(text[i + z]);
//             if (pat == pattern)
//                 return true;

//             pat.clear();
//         }
//     return false;
// }