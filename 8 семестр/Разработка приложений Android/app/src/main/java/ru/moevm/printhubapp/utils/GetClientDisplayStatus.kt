package ru.moevm.printhubapp.utils

fun getDisplayStatus(status: String): String {
    return when (status) {
        "Ожидает получения" -> "Готов к получению"
        "Выполнен" -> "Получен"
        else -> status
    }
}