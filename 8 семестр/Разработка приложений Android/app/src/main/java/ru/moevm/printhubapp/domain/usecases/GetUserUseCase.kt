package ru.moevm.printhubapp.domain.usecases

import ru.moevm.printhubapp.domain.entity.User
import ru.moevm.printhubapp.domain.repository.AuthRepository
import javax.inject.Inject

class GetUserUseCase @Inject constructor(private val authRepository: AuthRepository) {
    operator fun invoke(callback: (User) -> Unit) = authRepository.getUser(callback)
}