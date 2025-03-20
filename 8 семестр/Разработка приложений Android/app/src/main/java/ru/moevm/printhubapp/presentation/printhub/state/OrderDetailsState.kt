package ru.moevm.printhubapp.presentation.printhub.state

import ru.moevm.printhubapp.domain.entity.Order

sealed class OrderDetailsState {
    object Init : OrderDetailsState()
    object Loading : OrderDetailsState()
    data class Success(val order: Order) : OrderDetailsState()
    object Error: OrderDetailsState()
}