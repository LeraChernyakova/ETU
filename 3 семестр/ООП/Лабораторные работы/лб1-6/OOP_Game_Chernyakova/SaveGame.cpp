#include "SaveGame.h"
#include "Logger.h"
#include <utility>
#include <cmath>
#include "CellRegister.h"
#include <regex>

SaveGame::SaveGame(std::string filename) : _filename(std::move(filename)) {}

void SaveGame::save(const GameInfo& game_info) {
    std::ofstream f(_filename);
    if (!f.is_open()) {
        throw SaveException("File is invalid");
    }
    auto info = std::string(game_info);
    auto hash = getHash(info);
    f << info << "\n";
    f << hash << std::endl;
    f.close();
}

GameInfo SaveGame::load() {
    std::ifstream f(_filename);
    if (!f.is_open()) {
        throw SaveException("File is invalid");
    }
    std::string str;
    f >> str;
    std::vector<std::string> arr;
    while (str != "*******") {
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        arr.emplace_back(str);
        f >> str;
    }
    std::string delim = str;
    std::getline(f, str);
    std::getline(f, str);
    std::string p = std::move(str);
    std::getline(f, str);
    f.close();
    std::string data;
    data.reserve(arr.size() * arr[0].size() + p.size());
    std::for_each(arr.cbegin(), arr.cend(), [&data](const auto& str) {
        data.append(str);
        data.push_back('\n');
        });//собираем строку для проверки хеш функции(и про поле и про игрока)
    data.append(delim);
    data.append("\n");
    data.append(p);
    int64_t hash = getHash(data);
    char* ptr;
    int64_t hash_read = strtoll(str.data(), &ptr, 10);
    auto scheme = doField(arr);
    if (!scheme.has_value()) {//проверка на наличие значения
        throw SaveException("Error in field size while decoding");
    }
    auto player_info = doPlayer(p);
    if (!player_info.has_value()) {
        throw SaveException("Error in info about player");
    }
    auto gi = GameInfo{ scheme.value(), player_info.value() };
    if (hash != hash_read) {
        throw SaveException("File was changed", gi);
    }
    f.close();
    return gi;
}

std::optional<FieldScheme> SaveGame::doField(const std::vector<std::string>& arr) {
    int height = arr.size();
    if (height <= 0) {
        return std::nullopt;//optional тип с неинициализированным состоянием.
    }
    int width = arr[0].size();
    if (width <= 0) {
        return std::nullopt;
    }
    std::vector<std::vector<CellType>> map;
    map.resize(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        map[i].resize(arr[0].size());
    }
    for (int i = 0; i < arr.size(); i++) {
        if (width != arr[i].size()) {
            return std::nullopt;
        }

        for (int j = 0; j < arr[i].size(); j++) {
            map[i][j] = CellRegister::getType(arr[i][j]);
            if (map[i][j] == CellType::Undefined) {
                return std::nullopt;
            }
        }
    }
    auto scheme = FieldScheme{ map, height, width };
    return scheme;
}

std::optional<PlayerInfo> SaveGame::doPlayer(const std::string& arr) {
    const std::regex kRegex(R"(([0-1]) ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+))");
    std::vector<std::smatch> matches{
        std::sregex_iterator(arr.cbegin(), arr.cend(), kRegex),
        std::sregex_iterator{}
    };
    if (matches.empty()) {
        return std::nullopt;
    }
    const auto& match = matches[0];
    bool door_key = std::stoi(match[1]);
    int number_of_lives = std::stoi(match[2]);
    int protection = std::stoi(match[3]);
    int player_x = std::stoi(match[4]);
    int player_y = std::stoi(match[5]);
    PlayerInfo inf{ door_key, number_of_lives, protection, player_x, player_y };
    return inf;
}

int64_t SaveGame::getHash(const std::string& data) {
    double hash = 0;
    int n = 0;
    auto lambda = [&hash, &n](char c) {
        hash += c * pow(71, n++);
        if (n >= 5) {
            n = 0;
        }
    };
    std::for_each(data.cbegin(), data.cend(), lambda);
    return static_cast<int64_t>(hash);
}

const char* SaveException::what() const noexcept {
    return str.data();
}

SaveException::SaveException(std::string message, std::optional<GameInfo> inf)
    : str(std::move(message)), g_info(std::move(inf)) {}

const std::optional<GameInfo>& SaveException::getInfo() const noexcept {
    return g_info;
}