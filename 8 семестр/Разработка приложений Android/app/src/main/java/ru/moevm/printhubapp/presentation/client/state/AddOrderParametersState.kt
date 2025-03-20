package ru.moevm.printhubapp.presentation.client.state

sealed class AddOrderParametersState {
    object Init : AddOrderParametersState()
    object Loading : AddOrderParametersState()
    object ServerError : AddOrderParametersState()
    object Success : AddOrderParametersState()
}