package ru.moevm.printhubapp.navigation

import androidx.navigation.NavGraphBuilder
import androidx.navigation.NavHostController
import androidx.navigation.compose.composable
import ru.moevm.printhubapp.presentation.about.AboutScreen

fun NavGraphBuilder.aboutNavigation(navHostController: NavHostController) {
    composable(
        route = Screen.AboutScreen.route
    ) {
        AboutScreen(
            onBack = {
                navHostController.popBackStack()
            }
        )
    }
}