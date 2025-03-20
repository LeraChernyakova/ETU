package ru.moevm.printhubapp.domain.entity

data class Registration(
    val mail: String,
    val password: String,
    val role: Role,
    val nameCompany: String = "",
    val address: String = ""
)
