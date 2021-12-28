#ifndef GAMES_LIST_H
#define GAMES_LIST_H

#include <map>
#include <string>

struct Game {
    std::string password;
    std::string word;
    size_t wordSize;
};

class GamesList {
   public:
    GamesList();
    bool GameExists(std::string gameName);
    bool CreateGame(std::string gameName, std::string gamePassword);
    bool DeleteGame(std::string gameName);
    std::string GetPassword(std::string gameName);
    bool ChangeWord(std::string gameName, std::string newWord);
    bool GuessWord(std::string gameName, std::string tryWord);
    int GetHint(std::string gameName, std::string tryWord);
    ~GamesList();

   private:
    std::map<std::string, Game> games;
};

#endif  // GAMES_LIST_H
