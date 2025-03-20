package ru.moevm.printhubapp.presentation.printhub.components

import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.navigation.Screen

sealed class PrinthubNavigationItem(
    val titleResId: Int,
    val screen: Screen
) {

    object Home : PrinthubNavigationItem(
        titleResId =  R.string.navigation_item_home,
        screen = Screen.MainPrinthubScreen
    )

    object Profile : PrinthubNavigationItem(
        titleResId =  R.string.navigation_item_profile,
        screen = Screen.PrinthubProfileScreen
    )
}