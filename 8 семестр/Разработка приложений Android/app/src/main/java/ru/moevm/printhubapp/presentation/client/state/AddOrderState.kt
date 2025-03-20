package ru.moevm.printhubapp.presentation.client.state

import ru.moevm.printhubapp.domain.entity.User

sealed class AddOrderState {
    object Init : AddOrderState()
    object Loading : AddOrderState()
    class Success(val printhubs: List<User>) : AddOrderState()
    object Error : AddOrderState()
}