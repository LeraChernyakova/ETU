package ru.moevm.printhubapp.navigation

import androidx.hilt.navigation.compose.hiltViewModel
import androidx.navigation.NavGraphBuilder
import androidx.navigation.NavHostController
import androidx.navigation.compose.composable
import ru.moevm.printhubapp.domain.entity.Role
import ru.moevm.printhubapp.presentation.auth.components.AuthScreen
import ru.moevm.printhubapp.presentation.auth.components.RegistrationScreen
import ru.moevm.printhubapp.presentation.auth.viewmodels.RegistrationViewModel

fun NavGraphBuilder.authNavigation(navHostController: NavHostController) {
    composable(
        route = Screen.AuthScreen.route
    ) {
        AuthScreen(
            onLoginTo = {
                navHostController.navigate(Screen.MainClientScreen.route) {
                    popUpTo(Screen.AuthScreen.route) {
                        inclusive = true
                    }
                }
            },
            onLoginToPrintHub = {
                navHostController.navigate(Screen.MainPrinthubScreen.route) {
                    popUpTo(Screen.AuthScreen.route) {
                        inclusive = true
                    }
                }
            },
            onRegistration = {
                navHostController.navigate(Screen.RegistrationScreen.route)
            },
            onAbout = {
                navHostController.navigate(Screen.AboutScreen.route)
            }
        )
    }

    composable(
        route = Screen.RegistrationScreen.route
    ) {
        val viewModel: RegistrationViewModel = hiltViewModel()
        RegistrationScreen(
            viewModel = viewModel,
            onRegistration = { role ->
                when (role) {
                    Role.CLIENT -> {
                        navHostController.navigate(Screen.MainClientScreen.route) {
                            popUpTo(Screen.RegistrationScreen.route) {
                                inclusive = true
                            }
                        }
                    }
                    Role.PRINTHUB -> {
                        navHostController.navigate(Screen.MainPrinthubScreen.route) {
                            popUpTo(Screen.RegistrationScreen.route) {
                                inclusive = true
                            }
                        }
                    }
                    else -> {}
                }
            },
            onAbout = {
                navHostController.navigate(Screen.AboutScreen.route)
            }
        )
    }
}