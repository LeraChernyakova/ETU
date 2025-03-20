package ru.moevm.printhubapp.presentation.auth.viewmodels

import android.content.SharedPreferences
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import ru.moevm.printhubapp.domain.entity.Registration
import ru.moevm.printhubapp.domain.entity.Role
import ru.moevm.printhubapp.domain.entity.result.RequestError
import ru.moevm.printhubapp.domain.entity.result.RequestResult
import ru.moevm.printhubapp.domain.usecases.RegistrationUseCase
import ru.moevm.printhubapp.presentation.auth.state.RegistrationState
import ru.moevm.printhubapp.utils.ValidateError
import ru.moevm.printhubapp.utils.validateCredentials
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class RegistrationViewModel @Inject constructor(
    private val registrationUseCase: RegistrationUseCase,
    private val sharedPreferences: SharedPreferences
) : ViewModel() {
    private val _state = MutableStateFlow<RegistrationState>(RegistrationState.Init)
    val state: StateFlow<RegistrationState> get() = _state.asStateFlow()

    fun registration(newUser: Registration) {
        viewModelScope.launch {
            _state.value = RegistrationState.Loading
            val validationError = validateCredentials(newUser.mail, newUser.password)

            when(validationError) {
                ValidateError.MAIL -> {
                    _state.value = RegistrationState.IncorrectMailFormat
                    return@launch
                }
                ValidateError.PASSWORD -> {
                    _state.value = RegistrationState.ShortPassword
                    return@launch
                }
                ValidateError.SUCCESS -> {
                    registrationUseCase(newUser) { result ->
                        when (result) {
                            is RequestResult.Success -> {
                                when (newUser.role) {
                                    Role.CLIENT -> _state.value = RegistrationState.SuccessClient
                                    Role.PRINTHUB -> _state.value = RegistrationState.SuccessPrintHub
                                    else -> _state.value = RegistrationState.ServerError
                                }
                            }
                            is RequestResult.Error -> {
                                when (result.error) {
                                    is RequestError.UserAlreadyExists -> _state.value = RegistrationState.UserAlreadyExists
                                    is RequestError.InvalidCredentials -> _state.value = RegistrationState.ServerError
                                    is RequestError.Server -> _state.value = RegistrationState.ServerError
                                    else -> _state.value = RegistrationState.ServerError
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}