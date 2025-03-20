package ru.moevm.printhubapp.domain.usecases

import ru.moevm.printhubapp.domain.entity.User
import ru.moevm.printhubapp.domain.repository.PrinthubsRepository
import javax.inject.Inject

class GetPrinthubsUseCase @Inject constructor(
    private val printhubsRepository: PrinthubsRepository
) {
    suspend operator fun invoke(): List<User> {
        return printhubsRepository.getPrinthubs()
    }
}