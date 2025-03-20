package ru.moevm.printhubapp.presentation.auth.viewmodels

import android.content.SharedPreferences
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import ru.moevm.printhubapp.domain.entity.Auth
import ru.moevm.printhubapp.domain.entity.result.RequestError
import ru.moevm.printhubapp.domain.entity.result.RequestResult
import ru.moevm.printhubapp.domain.usecases.AuthorizationUseCase
import ru.moevm.printhubapp.presentation.auth.state.AuthState
import ru.moevm.printhubapp.utils.ValidateError
import ru.moevm.printhubapp.utils.validateCredentials
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class AuthViewModel @Inject constructor(
    private val authorizationUseCase: AuthorizationUseCase,
    private val sharedPreferences: SharedPreferences
) : ViewModel() {

    private val _state = MutableStateFlow<AuthState>(AuthState.Init)
    val state: StateFlow<AuthState> get() = _state.asStateFlow()

    fun authorization(user: Auth) {
        _state.value = AuthState.Loading
        viewModelScope.launch {
            val validationError = validateCredentials(user.mail, user.password)

            when(validationError) {
                ValidateError.MAIL -> {
                    _state.value = AuthState.IncorrectMailFormat
                    return@launch
                }

                ValidateError.PASSWORD -> {
                    _state.value = AuthState.ShortPassword
                    return@launch
                }

                ValidateError.SUCCESS -> {
                    authorizationUseCase(user) { result ->
                        when (result) {
                            is RequestResult.Success -> {
                                val userRole = sharedPreferences.getString("user_role", "") ?: ""
                                when (userRole.lowercase()) {
                                    "client" -> _state.value = AuthState.SuccessClient
                                    "printhub" -> _state.value = AuthState.SuccessPrintHub
                                    else -> _state.value = AuthState.ServerError
                                }
                            }
                            is RequestResult.Error -> {
                                when (result.error) {
                                    is RequestError.UserNotFound -> _state.value = AuthState.UserNotFound
                                    is RequestError.InvalidPassword -> _state.value = AuthState.InvalidPassword
                                    is RequestError.Server -> _state.value = AuthState.ServerError
                                    else ->  _state.value = AuthState.ServerError
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}