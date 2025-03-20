package ru.moevm.printhubapp.utils

import androidx.compose.runtime.Composable
import androidx.compose.ui.graphics.Color
import ru.moevm.printhubapp.ui.theme.AppTheme

@Composable
fun getStatusColor(status: String): Color {
    return when (status) {
        "В работе" -> AppTheme.colors.yellow
        "Ожидает получения" -> AppTheme.colors.green8
        "Отказ" -> AppTheme.colors.red
        "Выполнен" -> AppTheme.colors.green9
        else -> AppTheme.colors.gray7
    }
}