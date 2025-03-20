package ru.moevm.printhubapp.presentation.client.components

import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.navigation.Screen

sealed class NavigationItem(
    val titleResId: Int,
    val screen: Screen
) {

    object Home : NavigationItem(
        titleResId =  R.string.navigation_item_home,
        screen = Screen.MainClientScreen
    )

    object Profile : NavigationItem(
        titleResId =  R.string.navigation_item_profile,
        screen = Screen.ClientProfileScreen
    )
}