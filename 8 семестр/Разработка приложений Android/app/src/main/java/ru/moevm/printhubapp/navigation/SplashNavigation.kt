package ru.moevm.printhubapp.navigation

import androidx.navigation.NavGraphBuilder
import androidx.navigation.NavHostController
import androidx.navigation.compose.composable
import ru.moevm.printhubapp.presentation.splash.SplashScreen

fun NavGraphBuilder.splashNavigation(navHostController: NavHostController) {
    composable(
        route = Screen.SplashScreen.route
    ) {
        SplashScreen(
            onNavigateToAuth = {
                navHostController.navigate(Screen.AuthScreen.route) {
                    popUpTo(Screen.SplashScreen.route) {
                        inclusive = true
                    }
                }
            },
            onNavigateToClientMain = {
                navHostController.navigate(Screen.MainClientScreen.route) {
                    popUpTo(Screen.SplashScreen.route) {
                        inclusive = true
                    }
                }
            },
            onNavigateToPrintHubMain = {
                navHostController.navigate(Screen.MainPrinthubScreen.route) {
                    popUpTo(Screen.SplashScreen.route) {
                        inclusive = true
                    }
                }
            }
        )
    }
} 