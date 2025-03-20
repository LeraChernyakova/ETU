package ru.moevm.printhubapp.navigation

import androidx.hilt.navigation.compose.hiltViewModel
import androidx.navigation.NavGraphBuilder
import androidx.navigation.NavHostController
import androidx.navigation.NavType
import androidx.navigation.compose.composable
import androidx.navigation.navArgument
import ru.moevm.printhubapp.presentation.client.components.AddOrderParametersScreen
import ru.moevm.printhubapp.presentation.client.components.AddOrderScreen
import ru.moevm.printhubapp.presentation.client.components.ClientProfileScreen
import ru.moevm.printhubapp.presentation.client.components.MainClientScreen
import ru.moevm.printhubapp.presentation.client.components.OrderDetailsScreen
import ru.moevm.printhubapp.presentation.client.components.SuccessOrderScreen
import ru.moevm.printhubapp.presentation.client.viewmodels.AddOrderParametersViewModel

fun NavGraphBuilder.clientNavigation(navHostController: NavHostController) {
    composable(route = Screen.MainClientScreen.route) {
        MainClientScreen(
            navHostController = navHostController,
            onAbout = {
                navHostController.navigate(Screen.AboutScreen.route)
            },
            addOrder = {
                navHostController.navigate(Screen.AddOrderParametersScreen.route)
            },
            showOrderDetails = { orderId ->
                navHostController.navigate("${Screen.OrderDetailsScreen.route}/$orderId")
            }
        )
    }


    composable(route = Screen.AddOrderParametersScreen.route) {
        val viewModel: AddOrderParametersViewModel = hiltViewModel()
        AddOrderParametersScreen(
            onAbout = {
                navHostController.navigate(Screen.AboutScreen.route)
            },
            onBack = {
                navHostController.popBackStack()
            },
            onNext = { format, paperCount, comment, totalPrice ->
                navHostController.navigate(
                    "${Screen.AddOrderScreen.route}/$format/$paperCount/$comment/$totalPrice"
                )
            },
            viewModel = viewModel
        )
    }

    composable(
        route = "${Screen.AddOrderScreen.route}/{format}/{paperCount}/{comment}/{totalPrice}",
        arguments = listOf(
            navArgument("format") { type = NavType.StringType },
            navArgument("paperCount") { type = NavType.IntType },
            navArgument("comment") { type = NavType.StringType },
            navArgument("totalPrice") { type = NavType.IntType }
        )
    ) { backStackEntry ->
        val format = backStackEntry.arguments?.getString("format") ?: "A4"
        val paperCount = backStackEntry.arguments?.getInt("paperCount") ?: 1
        val comment = backStackEntry.arguments?.getString("comment") ?: ""
        val totalPrice = backStackEntry.arguments?.getInt("totalPrice") ?: 0

        AddOrderScreen(
            onAbout = {
                navHostController.navigate(Screen.AboutScreen.route)
            },
            onBack = {
                navHostController.popBackStack()
            },
            onSuccess = {
                navHostController.navigate(Screen.SuccessScreen.route)
            },
            format = format,
            paperCount = paperCount,
            comment = comment,
            totalPrice = totalPrice
        )
    }

    composable(
        route = Screen.SuccessScreen.route
    ) {
        SuccessOrderScreen(
            onNavigateHome = {
                navHostController.navigate(Screen.MainClientScreen.route) {
                    popUpTo(Screen.SuccessScreen.route) {
                        inclusive = true
                    }
                }
            }
        )
    }

    composable(
        route = "${Screen.OrderDetailsScreen.route}/{orderId}",
        arguments = listOf(navArgument("orderId") { type = NavType.StringType })
    ) { backStackEntry ->
        val orderId = backStackEntry.arguments?.getString("orderId") ?: "1"
        OrderDetailsScreen(
            onBack = {
                navHostController.popBackStack()
            },
            onAbout = {
                navHostController.navigate(Screen.AboutScreen.route)
            },
            orderId = orderId
        )
    }

    composable(
        route = Screen.ClientProfileScreen.route
    ) {
        ClientProfileScreen(
            navHostController = navHostController,
            onAbout = {
                navHostController.navigate(Screen.AboutScreen.route)
            },
            onLogout = {
                navHostController.navigate(Screen.AuthScreen.route) {
                    popUpTo(Screen.ClientProfileScreen.route) {
                        inclusive = true
                    }
                }
            }
        )
    }
}