package ru.moevm.printhubapp.navigation

import androidx.compose.runtime.Composable
import androidx.navigation.NavHostController
import androidx.navigation.compose.NavHost

@Composable
fun AppNavGraph(navHostController: NavHostController) {
    NavHost(
        navController = navHostController,
        startDestination = Screen.SplashScreen.route
    ) {

        splashNavigation(navHostController)
        authNavigation(navHostController)
        aboutNavigation(navHostController)
        clientNavigation(navHostController)
        printhubNavigation(
            navController = navHostController,
            onLogout = {
                navHostController.navigate(Screen.AuthScreen.route) {
                    popUpTo(Screen.PrinthubProfileScreen.route) {
                        inclusive = true
                    }
                }
            }
        )
    }
}