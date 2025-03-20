package ru.moevm.printhubapp.domain.usecases

import ru.moevm.printhubapp.domain.entity.User
import ru.moevm.printhubapp.domain.repository.UserRepository
import javax.inject.Inject

class GetUserInfoUseCase @Inject constructor(private val userRepository: UserRepository) {
    operator fun invoke(callback: (User) -> Unit) = userRepository.getUser(callback)
}