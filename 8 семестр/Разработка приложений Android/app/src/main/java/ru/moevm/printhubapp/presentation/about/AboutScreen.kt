package ru.moevm.printhubapp.presentation.about

import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.ui.theme.AppTheme

@Composable
fun AboutScreen(
    onBack: () -> Unit
) {
    Scaffold(
        topBar = {
            Column(
                modifier = Modifier
                    .fillMaxWidth()
                    .background(AppTheme.colors.orange10)
                    .padding(top = 32.dp)
            ) {
                Row(
                    modifier = Modifier
                        .fillMaxWidth()
                        .padding(16.dp),
                    verticalAlignment = Alignment.CenterVertically
                ) {
                    Icon(
                        modifier = Modifier.clickable { onBack() },
                        painter = painterResource(R.drawable.back_arrow_ic),
                        contentDescription = null,
                        tint = AppTheme.colors.black9
                    )
                    Spacer(modifier = Modifier.width(16.dp))
                    Text(
                        text = stringResource(R.string.title_about),
                        fontSize = 24.sp,
                        fontWeight = FontWeight.SemiBold,
                        color = AppTheme.colors.black9
                    )
                }
                HorizontalDivider(
                    color = AppTheme.colors.black9
                )
            }
        }
    ) { paddingValues ->
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(paddingValues)
                .padding(32.dp),
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            Image(
                painter = painterResource(R.drawable.logo_ic),
                contentDescription = null,
            )
            Spacer(modifier = Modifier.height(32.dp))
            Text(
                text = stringResource(R.string.subtitle_developers),
                fontSize = 20.sp,
                fontWeight = FontWeight.SemiBold,
                color = AppTheme.colors.gray8
            )
            Spacer(modifier = Modifier.height(16.dp))
            Text(
                text = stringResource(R.string.developer_1),
                fontSize = 20.sp,
                fontWeight = FontWeight.Medium,
                color = AppTheme.colors.gray8
            )
            Spacer(modifier = Modifier.height(8.dp))
            Text(
                text = stringResource(R.string.developer_2),
                fontSize = 20.sp,
                fontWeight = FontWeight.Medium,
                color = AppTheme.colors.gray8
            )
            Spacer(modifier = Modifier.height(8.dp))
            Text(
                text = stringResource(R.string.developer_3),
                fontSize = 20.sp,
                fontWeight = FontWeight.Medium,
                color = AppTheme.colors.gray8
            )
        }
    }
}

@Preview(showBackground = true)
@Composable
fun AboutScreenPreview() {
    AboutScreen({})
}