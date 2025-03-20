package ru.moevm.printhubapp.presentation.client.components

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.ui.theme.AppTheme
import kotlinx.coroutines.delay

@Composable
fun SuccessOrderScreen(
    onNavigateHome: () -> Unit
) {
    LaunchedEffect(Unit) {
        delay(3000L)
        onNavigateHome()
    }
    Column(
        modifier = Modifier.padding(16.dp).fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Image(
            painter = painterResource(R.drawable.success_ic),
            contentDescription = null
        )
        Spacer(modifier = Modifier.height(70.dp))
        Text(
            text = stringResource(R.string.success),
            fontSize = 32.sp,
            fontWeight = FontWeight.Medium,
            color = AppTheme.colors.gray7,
            textAlign = TextAlign.Center
        )
    }
}

@Preview(showBackground = true)
@Composable
private fun SuccessOrderScreenPreview() {
    SuccessOrderScreen({})
}