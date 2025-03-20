package ru.moevm.printhubapp.navigation

sealed class Screen(val route: String) {
    object SplashScreen : Screen(ROUTER_SPLASH)
    object AuthScreen : Screen(ROUTER_AUTH)
    object RegistrationScreen : Screen(ROUTER_REGISTRATION)

    object AboutScreen : Screen(ROUTER_ABOUT)

    object MainClientScreen : Screen(ROUTER_MAIN_CLIENT_SCREEN)
    object AddOrderScreen : Screen(ROUTER_ADD_ORDER_SCREEN)
    object AddOrderParametersScreen : Screen(ROUTER_ADD_ORDER_PARAMETERS_SCREEN)
    object SuccessScreen : Screen(ROUTER_SUCCESS_SCREEN)
    object OrderDetailsScreen : Screen(ROUTER_ORDER_DETAILS_SCREEN)
    object ClientProfileScreen : Screen(ROUTER_CLIENT_PROFILE_SCREEN)

    object MainPrinthubScreen : Screen(ROUTER_MAIN_PRINTHUB_SCREEN)
    object PrinthubProfileScreen : Screen(ROUTER_PRINTHUB_PROFILE_SCREEN)
    object StatisticScreen : Screen(ROUTER_STATISTIC_SCREEN)
    object OrderDetailsPrinthubScreen : Screen(ROUTER_ORDER_DETAILS_PRINTHUB_SCREEN)

    companion object {
        private const val ROUTER_SPLASH = "splash_screen"
        private const val ROUTER_AUTH = "auth_screen"
        private const val ROUTER_REGISTRATION = "registration_screen"

        private const val ROUTER_ABOUT = "about_screen"

        private const val ROUTER_MAIN_CLIENT_SCREEN = "main_client_screen"
        private const val ROUTER_ADD_ORDER_SCREEN = "add_order_screen"
        private const val ROUTER_ADD_ORDER_PARAMETERS_SCREEN = " add_order_parameters_screen"
        private const val ROUTER_SUCCESS_SCREEN = "success_screen"
        private const val ROUTER_ORDER_DETAILS_SCREEN = "order_details_screen"
        private const val ROUTER_CLIENT_PROFILE_SCREEN = "client_profile_screen"

        private const val ROUTER_MAIN_PRINTHUB_SCREEN = "main_printhub_screen"
        private const val ROUTER_PRINTHUB_PROFILE_SCREEN = "printhub_profile_screen"
        private const val ROUTER_STATISTIC_SCREEN = "statistic_screen"
        private const val ROUTER_ORDER_DETAILS_PRINTHUB_SCREEN = "order_details_printhub_screen"
    }
}