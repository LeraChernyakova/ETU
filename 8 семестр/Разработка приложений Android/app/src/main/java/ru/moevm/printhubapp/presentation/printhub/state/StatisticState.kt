package ru.moevm.printhubapp.presentation.printhub.state

import ru.moevm.printhubapp.domain.entity.Statistic

sealed class StatisticState {
    object Init : StatisticState()
    object Loading : StatisticState()
    data class Success(val statistic: Statistic) : StatisticState()
    object Error : StatisticState()
}