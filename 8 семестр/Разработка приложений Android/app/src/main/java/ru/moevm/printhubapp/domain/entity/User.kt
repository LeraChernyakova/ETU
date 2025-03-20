package ru.moevm.printhubapp.domain.entity

data class User(
    val id: String,
    val mail: String,
    val password: String,
    val role: Role,
    val nameCompany: String = "",
    val address: String = "",
    val statisticId: String = ""
)
