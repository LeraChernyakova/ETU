package ru.moevm.printhubapp.presentation.printhub.viewmodels

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import ru.moevm.printhubapp.domain.usecases.GetStatisticUseCase
import ru.moevm.printhubapp.presentation.printhub.state.StatisticState
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class StatisticViewModel @Inject constructor(
    private val getStatisticUseCase: GetStatisticUseCase
) : ViewModel() {
    private val _state = MutableStateFlow<StatisticState>(StatisticState.Init)
    val state: StateFlow<StatisticState> get() = _state.asStateFlow()

    init {
        getStatistic()
    }

    fun getStatistic() {
        viewModelScope.launch {
            _state.value = StatisticState.Loading
            try {
                val statistic = getStatisticUseCase()
                _state.value = StatisticState.Success(statistic)
            } catch (e: Exception) {
                _state.value = StatisticState.Error
            }
        }
    }
}