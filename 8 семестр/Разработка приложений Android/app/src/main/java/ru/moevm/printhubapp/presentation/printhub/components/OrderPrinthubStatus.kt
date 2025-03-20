package ru.moevm.printhubapp.presentation.printhub.components

import ru.moevm.printhubapp.R

enum class OrderPrinthubStatus(val value: String) {
    NEW(value = "Создан"),
    INWORK(value = "В работе"),
    AWAIT(value = "Ожидает получения"),
    READE(value = "Выполнен"),
    REJECT(value = "Отказ")
}