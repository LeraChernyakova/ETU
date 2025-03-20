package ru.moevm.printhubapp.domain.repository

import ru.moevm.printhubapp.domain.entity.User

interface UserRepository {
    fun getUser(callback: (User) -> Unit)
}