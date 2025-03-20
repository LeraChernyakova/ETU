package ru.moevm.printhubapp.domain.entity

sealed class AuthState {
    object NotAuthenticated : AuthState()
    object AuthenticatedClient : AuthState()
    object AuthenticatedPrintHub : AuthState()
} 