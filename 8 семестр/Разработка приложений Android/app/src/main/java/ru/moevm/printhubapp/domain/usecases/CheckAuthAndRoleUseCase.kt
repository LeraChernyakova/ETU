package ru.moevm.printhubapp.domain.usecases

import android.content.SharedPreferences
import ru.moevm.printhubapp.domain.entity.AuthState
import ru.moevm.printhubapp.utils.Constants.UID_STRING
import ru.moevm.printhubapp.utils.Constants.USER_ROLE
import javax.inject.Inject

class CheckAuthAndRoleUseCase @Inject constructor(
    private val sharedPreferences: SharedPreferences
) {
    operator fun invoke(): AuthState {
        val isLoggedIn = sharedPreferences.contains(UID_STRING)
        if (!isLoggedIn) return AuthState.NotAuthenticated

        return when (sharedPreferences.getString(USER_ROLE, "")?.lowercase()) {
            "client" -> AuthState.AuthenticatedClient
            "printhub" -> AuthState.AuthenticatedPrintHub
            else -> AuthState.NotAuthenticated
        }
    }
}

