#pragma once

#include <optional>
#include <string>
#include <fstream>
#include "GameInfo.h"

class SaveException : public std::exception {
public:
    explicit SaveException(std::string message, std::optional<GameInfo> info = std::nullopt);
    [[nodiscard]] const char* what() const noexcept override;
    [[nodiscard]] const std::optional<GameInfo>& getInfo() const noexcept;
private:
    std::string str;
    std::optional<GameInfo> g_info;
};

class SaveGame {
public:
    explicit SaveGame(std::string filename = "Save.txt");
    void save(const GameInfo& game_info);
    GameInfo load();
private:
    static int64_t getHash(const std::string& data);
    static std::optional<FieldScheme> doField(const std::vector<std::string>& arr);
    static std::optional<PlayerInfo> doPlayer(const std::string& arr);
    std::string _filename;
};