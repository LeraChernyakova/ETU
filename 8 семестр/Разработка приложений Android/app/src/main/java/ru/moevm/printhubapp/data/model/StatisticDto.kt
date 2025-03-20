package ru.moevm.printhubapp.data.model

data class StatisticDto (
    val companyId: String = "",
    val formatsCount: Map<String, Int> = mapOf(
        "A1" to 0,
        "A2" to 0,
        "A3" to 0,
        "A4" to 0,
        "A5" to 0,
        "A6" to 0
    ),
    val profit: Int = 0,
    val totalPaperCount: Int = 0
)