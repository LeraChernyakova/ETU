package ru.moevm.printhubapp.presentation.client.state

import ru.moevm.printhubapp.domain.entity.Order

sealed class MainClientState {
    object Init : MainClientState()
    object Loading : MainClientState()
    data class Success(val orders: List<Order>) : MainClientState()
    object Error: MainClientState()
}