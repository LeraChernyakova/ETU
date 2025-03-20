package ru.moevm.printhubapp.domain.entity.result

sealed class RequestError {
    object UserNotFound : RequestError()
    object UserAlreadyExists : RequestError()
    object InvalidPassword : RequestError()
    object InvalidEmail : RequestError()
    object WeakPassword : RequestError()
    data class InvalidCredentials(val reason: String) : RequestError()
    data class Server(val errorMessage: String) : RequestError()
}