package ru.moevm.printhubapp.domain.usecases

import ru.moevm.printhubapp.domain.repository.AuthRepository
import javax.inject.Inject

class LogoutUseCase @Inject constructor(
    private val authRepository: AuthRepository
) {
    operator fun invoke() {
        authRepository.logout()
    }
} 