package ru.moevm.printhubapp.domain.usecases

import ru.moevm.printhubapp.domain.entity.Auth
import ru.moevm.printhubapp.domain.entity.result.RequestResult
import ru.moevm.printhubapp.domain.repository.AuthRepository
import javax.inject.Inject

class AuthorizationUseCase @Inject constructor(private val authRepository: AuthRepository) {
    operator fun invoke(user: Auth, callback: (RequestResult<Unit>) -> Unit) =
        authRepository.authorization(user, callback)
}