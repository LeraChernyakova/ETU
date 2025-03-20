package ru.moevm.printhubapp.presentation.client.viewmodels

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import ru.moevm.printhubapp.domain.usecases.GetUserInfoUseCase
import ru.moevm.printhubapp.presentation.client.state.ProfileState
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class ProfileViewModel @Inject constructor(
    private val userInfoUseCase: GetUserInfoUseCase
): ViewModel() {

    private val _state = MutableStateFlow<ProfileState>(ProfileState.Init)
    val state: StateFlow<ProfileState> get() = _state.asStateFlow()

    init {
        getUser()
    }

    private fun getUser() {
        _state.value = ProfileState.Loading
        viewModelScope.launch {
            userInfoUseCase { user ->
                _state.value = ProfileState.Success(user)
            }
        }
    }
}