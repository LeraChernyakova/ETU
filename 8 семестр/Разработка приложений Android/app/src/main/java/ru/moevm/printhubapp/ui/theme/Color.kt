package ru.moevm.printhubapp.ui.theme

import androidx.compose.material3.ColorScheme
import androidx.compose.material3.darkColorScheme
import androidx.compose.material3.lightColorScheme
import androidx.compose.runtime.Composable
import androidx.compose.runtime.Stable
import androidx.compose.ui.graphics.Color

@Stable
@Suppress("unused")
data class AppColors(
    val gray1: Color,
    val gray2: Color,
    val gray7: Color,
    val gray8: Color,
    val black9: Color,
    val orange3: Color,
    val orange10: Color,
    val green8: Color,
    val green9: Color,
    val yellow: Color,
    val red: Color,
    val textTitleDialog: Color,
    val materialColors: ColorScheme
)

@Composable
fun appColors(darkTheme: Boolean): AppColors =
    if (darkTheme) darkAppColors else lightAppColors

fun defaultAppColors() = lightAppColors

private val darkAppColors = AppColors(
    gray1 = AppCustomColors.Gray1,
    gray2 = AppCustomColors.Gray2,
    gray7 = AppCustomColors.Gray7,
    gray8 = AppCustomColors.Gray8,
    black9 = AppCustomColors.Black9,
    orange3 = AppCustomColors.Orange3,
    orange10 = AppCustomColors.Orange10,
    green8 = AppCustomColors.Green8,
    green9 = AppCustomColors.Green9,
    yellow = AppCustomColors.Yellow,
    red = AppCustomColors.Red,
    textTitleDialog = AppCustomColors.Gray1,
    materialColors = darkColorScheme(
        background = AppCustomColors.Black9
    )
)

private val lightAppColors = AppColors(
    gray1 = AppCustomColors.Gray1,
    gray2 = AppCustomColors.Gray2,
    gray7 = AppCustomColors.Gray7,
    gray8 = AppCustomColors.Gray8,
    black9 = AppCustomColors.Black9,
    orange3 = AppCustomColors.Orange3,
    orange10 = AppCustomColors.Orange10,
    green8 = AppCustomColors.Green8,
    green9 = AppCustomColors.Green9,
    yellow = AppCustomColors.Yellow,
    red = AppCustomColors.Red,
    textTitleDialog = AppCustomColors.Black9,
    materialColors = lightColorScheme(
        background = Color.White
    )
)

private object AppCustomColors {
    val Gray1 = Color(0xFFF3F3F3)
    val Gray2 = Color(0xFFEEEEF2)
    val Gray7 = Color(0xFF7E7F83)
    val Gray8 = Color(0xFF807E7E)

    val Black9 = Color(0xFF14110F)

    val Orange3 = Color(0xFFFCDA9E)
    val Orange10 = Color(0xFFFBB02D)

    val Green8 = Color(0xFF299F0B)
    val Green9 = Color(0xFF166D00)

    val Yellow = Color(0xFFEDC218)

    val Red = Color(0xFFC22225)
}