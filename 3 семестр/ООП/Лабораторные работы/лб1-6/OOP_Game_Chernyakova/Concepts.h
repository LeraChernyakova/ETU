#pragma once

#include <type_traits>
#include <concepts>

enum class CellType;

template<typename T>
concept TCellChanger = requires(T obj) {
    { obj(std::declval<CellType&>()) } -> std::convertible_to<bool>;
};

template<typename T>
concept TRandom = requires(T obj) {
    { obj() } -> std::convertible_to<bool>;
};