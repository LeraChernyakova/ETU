package ru.moevm.printhubapp.presentation.printhub.viewmodels

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import ru.moevm.printhubapp.domain.entity.Order
import ru.moevm.printhubapp.domain.usecases.GetPrinthubOrdersUseCase
import ru.moevm.printhubapp.presentation.printhub.state.MainPrinthubState
import javax.inject.Inject

@HiltViewModel
class MainPrinthubViewModel @Inject constructor(
    private val getPrinthubOrdersUseCase: GetPrinthubOrdersUseCase
) : ViewModel() {
    private val _state = MutableStateFlow<MainPrinthubState>(MainPrinthubState.Init)
    val state: StateFlow<MainPrinthubState> get() = _state.asStateFlow()

    private var initialLoadComplete = false
    private var originalOrders: List<Order>? = null
    private var currentStatusFilters: Set<String> = emptySet()
    private var currentMinPrice: Int? = null
    private var currentMaxPrice: Int? = null
    private var currentFormatFilters: Set<String> = emptySet()
    private var currentSearchQuery: String = ""
    private var currentSortOption = SortOption.UPDATED_NEWEST_FIRST

    private val _minPrice = MutableStateFlow("0")
    val minPrice: StateFlow<String> = _minPrice

    private val _maxPrice = MutableStateFlow("10000")
    val maxPrice: StateFlow<String> = _maxPrice

    private val _priceFilterApplied = MutableStateFlow(false)
    val priceFilterApplied: StateFlow<Boolean> = _priceFilterApplied

    private val _formatFilterApplied = MutableStateFlow(false)
    val formatFilterApplied: StateFlow<Boolean> = _formatFilterApplied

    private val _selectedStatuses = MutableStateFlow<Set<String>>(emptySet())
    val selectedStatuses: StateFlow<Set<String>> = _selectedStatuses

    private val _formatFilters = MutableStateFlow<Set<String>>(emptySet())
    val formatFilters: StateFlow<Set<String>> = _formatFilters

    init {
        getPrinthubOrders()
    }

    fun getPrinthubOrders() {
        viewModelScope.launch {
            _state.value = MainPrinthubState.Loading
            try {
                val orders = getPrinthubOrdersUseCase()
                originalOrders = orders
                applyAllFilters()
                initialLoadComplete = true
            } catch (e: Exception) {
                Log.e("OrderViewModel", "Error getting orders: ${e.message}", e)
                _state.value = MainPrinthubState.Error
            }
        }
    }

    enum class SortOption {
        CREATED_NEWEST_FIRST,
        CREATED_OLDEST_FIRST,
        UPDATED_NEWEST_FIRST,
        UPDATED_OLDEST_FIRST
    }

    fun getCurrentSortOption(): SortOption {
        return currentSortOption
    }

    fun sortOrders(sortOption: SortOption) {
        if (!initialLoadComplete) return
        currentSortOption = sortOption
        applyAllFilters()
    }

    fun searchOrders(query: String) {
        try {
            currentSearchQuery = query
            applyAllFilters()
        } catch (e: Exception) {
            Log.e("OrderViewModel", "Error searching orders: ${e.message}", e)
            _state.value = MainPrinthubState.Error
        }
    }

    fun filterByStatuses(statuses: Set<String>) {
        if (!initialLoadComplete) return
        try {
            currentStatusFilters = statuses
            _selectedStatuses.value = statuses
            applyAllFilters()
        } catch (e: Exception) {
            Log.e("OrderViewModel", "Error filtering orders: ${e.message}", e)
            _state.value = MainPrinthubState.Error
        }
    }

    fun filterByPriceRange(minPriceText: String, maxPriceText: String) {
        if (!initialLoadComplete) return
        try {
            val min = minPriceText.toIntOrNull() ?: 0
            val max = maxPriceText.toIntOrNull() ?: 10000

            _minPrice.value = minPriceText
            _maxPrice.value = maxPriceText

            currentMinPrice = min
            currentMaxPrice = max

            val isFilterActive = (min != 0 || max != 10000)
            updatePriceFilterApplied(isFilterActive)
            applyAllFilters()
        } catch (e: Exception) {
            Log.e("OrderViewModel", "Error filtering by price: ${e.message}", e)
            _state.value = MainPrinthubState.Error
        }
    }

    fun filterByFormats(formats: Set<String>) {
        if (!initialLoadComplete) return
        try {
            currentFormatFilters = formats
            _formatFilters.value = formats
            updateFormatFilterApplied(formats.isNotEmpty())
            applyAllFilters()
        } catch (e: Exception) {
            Log.e("OrderViewModel", "Error filtering by format: ${e.message}", e)
            _state.value = MainPrinthubState.Error
        }
    }

    fun updatePriceFilterApplied(isApplied: Boolean) {
        _priceFilterApplied.value = isApplied
    }

    fun updateFormatFilterApplied(isApplied: Boolean) {
        _formatFilterApplied.value = isApplied
    }

    private fun applyAllFilters() {
        val orders = originalOrders ?: return

        var filteredOrders = orders

        if (currentStatusFilters.isNotEmpty()) {
            filteredOrders = filteredOrders.filter { order ->
                currentStatusFilters.contains(order.status)
            }
        }

        if (currentMinPrice != null || currentMaxPrice != null) {
            filteredOrders = filteredOrders.filter { order ->
                val minMatch = currentMinPrice?.let { order.totalPrice >= it } ?: true
                val maxMatch = currentMaxPrice?.let { order.totalPrice <= it } ?: true
                minMatch && maxMatch
            }
        }

        if (currentFormatFilters.isNotEmpty()) {
            filteredOrders = filteredOrders.filter { order ->
                currentFormatFilters.contains(order.format)
            }
        }

        if (currentSearchQuery.isNotEmpty()) {
            filteredOrders = filteredOrders.filter { order ->
                order.number.toString().contains(currentSearchQuery) ||
                order.files.contains(currentSearchQuery, ignoreCase = true) ||
                order.clientMail.contains(currentSearchQuery, ignoreCase = true)
            }
        }

        filteredOrders = when (currentSortOption) {
            SortOption.CREATED_NEWEST_FIRST -> filteredOrders.sortedByDescending { it.createdAt }
            SortOption.CREATED_OLDEST_FIRST -> filteredOrders.sortedBy { it.createdAt }
            SortOption.UPDATED_NEWEST_FIRST -> filteredOrders.sortedByDescending { it.updatedAt }
            SortOption.UPDATED_OLDEST_FIRST -> filteredOrders.sortedBy { it.updatedAt }
        }

        _state.value = MainPrinthubState.Success(filteredOrders)
    }
}