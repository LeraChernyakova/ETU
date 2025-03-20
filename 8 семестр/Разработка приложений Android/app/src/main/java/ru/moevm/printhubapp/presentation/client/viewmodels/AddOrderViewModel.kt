package ru.moevm.printhubapp.presentation.client.viewmodels

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import ru.moevm.printhubapp.domain.entity.Order
import ru.moevm.printhubapp.domain.entity.User
import ru.moevm.printhubapp.domain.entity.result.RequestResult
import ru.moevm.printhubapp.domain.usecases.CreateOrderUseCase
import ru.moevm.printhubapp.domain.usecases.GetPrinthubsUseCase
import ru.moevm.printhubapp.presentation.client.state.AddOrderState
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class AddOrderViewModel @Inject constructor(
    private val getPrinthubsUseCase: GetPrinthubsUseCase,
    private val createOrderUseCase: CreateOrderUseCase
) : ViewModel() {
    private val _state = MutableStateFlow<AddOrderState>(AddOrderState.Init)
    val state: StateFlow<AddOrderState> get() = _state.asStateFlow()

    private var allPrinthubs: List<User> = emptyList()

    init {
        getPrinthubs()
    }

    private fun getPrinthubs() {
        viewModelScope.launch {
            _state.value = AddOrderState.Loading
            try {
                val printhubs = getPrinthubsUseCase()
                allPrinthubs = printhubs
                _state.value = AddOrderState.Success(printhubs)
            } catch (e: Exception) {
                _state.value = AddOrderState.Error
            }
        }
    }

    fun searchPrinthubs(query: String) {
        viewModelScope.launch {
            try {
                val filteredPrinthubs = allPrinthubs.filter { it.address.contains(query, ignoreCase = true) }
                _state.value = AddOrderState.Success(filteredPrinthubs)
            } catch (e: Exception) {
                _state.value = AddOrderState.Error
            }
        }
    }

    fun createOrder(order: Order, onSuccess: () -> Unit) {
        viewModelScope.launch {
            createOrderUseCase(order) { result ->
                when (result) {
                    is RequestResult.Success -> onSuccess()
                    is RequestResult.Error -> {
                        Log.e("AddOrderViewModel", "Order creation failed: ${result.error}")
                    }
                }
            }
        }
    }
}