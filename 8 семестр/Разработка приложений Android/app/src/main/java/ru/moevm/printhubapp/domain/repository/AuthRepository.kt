package ru.moevm.printhubapp.domain.repository

import ru.moevm.printhubapp.domain.entity.Auth
import ru.moevm.printhubapp.domain.entity.Registration
import ru.moevm.printhubapp.domain.entity.User
import ru.moevm.printhubapp.domain.entity.result.RequestResult

interface AuthRepository {
    fun authorization(user: Auth, callback: (RequestResult<Unit>) -> Unit)
    fun registration(newUser: Registration, callback: (RequestResult<Unit>) -> Unit)
    fun checkLogin(): Boolean
    fun getUser(callback: (User) -> Unit)
    fun logout()
}