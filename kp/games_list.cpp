#include "games_list.h"


bool IsLetter(const char &c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return true;
    return false;
}

bool IsLettersOnly(std::string str) {
    for (size_t i = 0; i < str.size(); ++i)
        if (!IsLetter(str[i]))
            return false;
    return true;
}

bool CheckStringUnique(std::string str) {
    for (size_t i = 0; i < str.size() - 1; ++i)
        for (size_t j = i + 1; j < str.size(); ++j)
            if (str[i] == str[j])
                return false;
    return true;
}

bool GamesList::GameExists(std::string gameName) {
    if (games.find(gameName) == games.end())
        return false;
    return true;
}

bool GamesList::CreateGame(std::string gameName, std::string gamePassword) {
    if (GameExists(gameName))
        return false;
    games[gameName] = {gamePassword, "", 0};
    return true;
}

bool GamesList::DeleteGame(std::string gameName) {
    if (!GameExists(gameName))
        return false;
    games.erase(gameName);
    return true;
}

// std::string GamesList::GetPassword(std::string gameName) {
//     if (!GameExists(gameName))
//         return "notexists";
//     return games[gameName].password;
// }

// bool GamesList::ChangeWord(std::string gameName, std::string newWord) {
//     if (!GameExists(gameName))
//         return false;
//     if (IsLettersOnly(newWord) && CheckStringUnique(newWord)) {
//         games[gameName] = {games[gameName].password, newWord, newWord.size()};
//         return true;
//     }
//     return false;
// }

bool GamesList::GuessWord(std::string gameName, std::string tryWord) {
    // if (!GameExists(gameName))
    //     return false;
    // if (games[gameName].wordSize == tryWord.size() && games[gameName].word == tryWord)
    //     return true;
    if (games[gameName].word == tryWord)
        return true;
    return false;
}

// Returns -3 if guessed, otherwise (10000 * withPos + withoutPos): withPos /=, withoutPos %=
int GamesList::GetHint(std::string gameName, std::string tryWord) {
    if (!GameExists(gameName))
        return -1;
    if (tryWord.size() != games[gameName].wordSize)
        return -2;
    if (GuessWord(gameName, tryWord))
        return -3;

    int guessedWithoutPositions = 0, guessedWithPositions = 0;
    for (size_t i = 0; i < tryWord.size(); ++i)
        if (tryWord[i] == games[gameName].word[i])
            ++guessedWithPositions;
    for (size_t i = 0; i < tryWord.size(); ++i)
        for (size_t j = 0; j < games[gameName].word.size(); ++j)
            if (tryWord[i] == games[gameName].word[j])
                ++guessedWithoutPositions;

    guessedWithoutPositions -= guessedWithPositions;
    return 10000 * guessedWithPositions + guessedWithoutPositions;
}

GamesList::GamesList() {}

GamesList::~GamesList() {}
