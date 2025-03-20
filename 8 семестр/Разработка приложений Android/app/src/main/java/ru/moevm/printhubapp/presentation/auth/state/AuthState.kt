package ru.moevm.printhubapp.presentation.auth.state

sealed class AuthState {
    object Init : AuthState()
    object Loading : AuthState()
    object UserNotFound : AuthState()
    object InvalidPassword : AuthState()
    object IncorrectMailFormat : AuthState()
    object ShortPassword : AuthState()
    object ServerError : AuthState()
    object NetworkError : AuthState()
    object SuccessClient : AuthState()
    object SuccessPrintHub : AuthState()
}