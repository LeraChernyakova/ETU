package ru.moevm.printhubapp.presentation.splash

import androidx.lifecycle.ViewModel
import ru.moevm.printhubapp.domain.entity.AuthState
import ru.moevm.printhubapp.domain.usecases.CheckAuthAndRoleUseCase
import ru.moevm.printhubapp.domain.usecases.LogoutUseCase
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import javax.inject.Inject

@HiltViewModel
class SplashViewModel @Inject constructor(
    private val checkAuthAndRoleUseCase: CheckAuthAndRoleUseCase,
    private val logoutUseCase: LogoutUseCase
) : ViewModel() {
    private val _state = MutableStateFlow<SplashState>(SplashState.Loading)
    val state: StateFlow<SplashState> get() = _state.asStateFlow()

    init {
        checkAuthState()
    }

    private fun checkAuthState() {
        when (checkAuthAndRoleUseCase()) {
            AuthState.NotAuthenticated -> _state.value = SplashState.NavigateToAuth
            AuthState.AuthenticatedClient -> _state.value = SplashState.NavigateToClientMain
            AuthState.AuthenticatedPrintHub -> _state.value = SplashState.NavigateToPrintHubMain
        }
    }

    fun logout() {
        logoutUseCase()
        _state.value = SplashState.NavigateToAuth
    }
}

sealed class SplashState {
    object Loading : SplashState()
    object NavigateToAuth : SplashState()
    object NavigateToClientMain : SplashState()
    object NavigateToPrintHubMain : SplashState()
} 