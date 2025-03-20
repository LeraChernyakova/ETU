package ru.moevm.printhubapp.presentation.auth.state

sealed class RegistrationState {
    object Init : RegistrationState()
    object Loading : RegistrationState()
    object IncorrectMailFormat : RegistrationState()
    object ShortPassword : RegistrationState()
    object ServerError : RegistrationState()
    object NetworkError : RegistrationState()
    object UserAlreadyExists : RegistrationState()
    object SuccessClient : RegistrationState()
    object SuccessPrintHub : RegistrationState()
}