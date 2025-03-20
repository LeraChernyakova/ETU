package ru.moevm.printhubapp.presentation.client.viewmodels

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import ru.moevm.printhubapp.domain.usecases.GetOrderUseCase
import ru.moevm.printhubapp.presentation.client.state.OrderDetailsState
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class OrderDetailsViewModel @Inject constructor(
    private val getOrderUseCase: GetOrderUseCase
) : ViewModel() {

    private val _state = MutableStateFlow<OrderDetailsState>(OrderDetailsState.Init)
    val state: StateFlow<OrderDetailsState> get() = _state.asStateFlow()

    fun getOrder(orderId: String) {
        viewModelScope.launch {
            _state.value = OrderDetailsState.Loading
            try {
                val order = getOrderUseCase(orderId)
                _state.value = OrderDetailsState.Success(order)
            } catch (e: Exception) {
                _state.value = OrderDetailsState.Error
            }
        }
    }
}