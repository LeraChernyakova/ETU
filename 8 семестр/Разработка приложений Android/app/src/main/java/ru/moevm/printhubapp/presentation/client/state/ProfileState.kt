package ru.moevm.printhubapp.presentation.client.state

import ru.moevm.printhubapp.domain.entity.User

sealed class ProfileState {
    object Init : ProfileState()
    object Loading : ProfileState()
    data class Success(val user: User) : ProfileState()
    object Error: ProfileState()
}