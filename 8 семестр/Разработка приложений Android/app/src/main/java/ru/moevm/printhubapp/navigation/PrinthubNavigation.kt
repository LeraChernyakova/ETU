package ru.moevm.printhubapp.navigation

import androidx.navigation.NavGraphBuilder
import androidx.navigation.NavHostController
import androidx.navigation.NavType
import androidx.navigation.compose.composable
import androidx.navigation.navArgument
import ru.moevm.printhubapp.presentation.printhub.components.MainPrinthubScreen
import ru.moevm.printhubapp.presentation.printhub.components.OrderDetailsPrinthubScreen
import ru.moevm.printhubapp.presentation.printhub.components.ProfilePrinthubScreen
import ru.moevm.printhubapp.presentation.printhub.components.StatisticScreen

fun NavGraphBuilder.printhubNavigation(
    navController: NavHostController,
    onLogout: () -> Unit
) {
    composable(
        route = Screen.MainPrinthubScreen.route
    ) {
        MainPrinthubScreen(
            navHostController = navController,
            onAbout = {
                navController.navigate(Screen.AboutScreen.route)
            },
            onOrderDetails = { orderId ->
                navController.navigate("${Screen.OrderDetailsPrinthubScreen.route}/$orderId")
            }
        )
    }

    composable(
        route = Screen.PrinthubProfileScreen.route
    ) {
        ProfilePrinthubScreen(
            navHostController = navController,
            onAbout = {
                navController.navigate(Screen.AboutScreen.route)
            },
            onStatistic = {
                navController.navigate(Screen.StatisticScreen.route)
            },
            onLogout = onLogout
        )
    }

    composable(
        route = Screen.StatisticScreen.route
    ) {
        StatisticScreen(
            onBack = {
                navController.popBackStack()
            },
            onAbout = {
                navController.navigate(Screen.AboutScreen.route)
            }
        )
    }

    composable(
        route = "${Screen.OrderDetailsPrinthubScreen.route}/{orderId}",
        arguments = listOf(navArgument("orderId") { type = NavType.StringType })
    ) { backStackEntry ->
        val orderId = backStackEntry.arguments?.getString("orderId") ?: "1"
        OrderDetailsPrinthubScreen(
            onBack = {
                navController.popBackStack()
            },
            onAbout = {
                navController.navigate(Screen.AboutScreen.route)
            },
            orderId = orderId
        )
    }
}