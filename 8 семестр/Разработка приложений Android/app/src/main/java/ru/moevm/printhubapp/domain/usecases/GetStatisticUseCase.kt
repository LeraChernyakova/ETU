package ru.moevm.printhubapp.domain.usecases

import ru.moevm.printhubapp.domain.entity.Statistic
import ru.moevm.printhubapp.domain.repository.PrinthubsRepository
import javax.inject.Inject

class GetStatisticUseCase @Inject constructor (
    private val printhubsRepository: PrinthubsRepository
){
    suspend operator fun invoke(): Statistic {
        return printhubsRepository.getStatistic()
    }
}