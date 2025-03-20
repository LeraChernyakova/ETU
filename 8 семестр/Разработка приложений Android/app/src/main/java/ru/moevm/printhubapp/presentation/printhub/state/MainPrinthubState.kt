package ru.moevm.printhubapp.presentation.printhub.state

import ru.moevm.printhubapp.domain.entity.Order

sealed class MainPrinthubState {
    object Init : MainPrinthubState()
    object Loading : MainPrinthubState()
    data class Success(val orders: List<Order>) : MainPrinthubState()
    object Error: MainPrinthubState()
}