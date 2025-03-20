package ru.moevm.printhubapp.presentation.printhub.components

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.hilt.navigation.compose.hiltViewModel
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.presentation.printhub.state.StatisticState
import ru.moevm.printhubapp.presentation.printhub.viewmodels.StatisticViewModel
import ru.moevm.printhubapp.ui.theme.AppTheme

@Composable
fun StatisticScreen(
    onBack: () -> Unit,
    onAbout: () -> Unit
) {

    val viewModel: StatisticViewModel = hiltViewModel()
    val state by viewModel.state.collectAsState()

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
                    verticalAlignment = Alignment.CenterVertically,
                    horizontalArrangement = Arrangement.SpaceBetween
                ) {
                    Row(
                        verticalAlignment = Alignment.CenterVertically,
                    ) {
                        Icon(
                            modifier = Modifier.clickable { onBack() },
                            painter = painterResource(R.drawable.back_arrow_ic),
                            contentDescription = null,
                            tint = AppTheme.colors.black9
                        )
                        Spacer(modifier = Modifier.width(12.dp))
                        Text(
                            text = String.format(
                                stringResource(R.string.statistic_screen_title),
                            ),
                            fontSize = 24.sp,
                            fontWeight = FontWeight.SemiBold,
                            color = AppTheme.colors.black9
                        )
                    }
                    Icon(
                        modifier = Modifier.clickable { onAbout() },
                        painter = painterResource(R.drawable.info_ic),
                        contentDescription = null,
                        tint = AppTheme.colors.black9
                    )
                }
                HorizontalDivider(
                    color = AppTheme.colors.black9
                )
            }
        },
    ) { paddingValues ->
        Box(
            modifier = Modifier
                .fillMaxSize()
                .padding(paddingValues)
        ) {
            when (state) {
                is StatisticState.Success -> {
                    val statistic = (state as StatisticState.Success).statistic
                    Column(
                        modifier = Modifier
                            .padding(16.dp)
                            .background(AppTheme.colors.gray1, RoundedCornerShape(16.dp))
                            .padding(start = 16.dp, end = 16.dp, bottom = 16.dp)
                    ) {
                        InfoRow(
                            titleId = R.string.list_title,
                            isList = true,
                            formats = statistic.formatsCount
                        )
                        InfoRow(
                            titleId = R.string.toner_title,
                            param = (statistic.totalPaperCount * 1).toString()
                        )
                        InfoRow(
                            titleId = R.string.profit_title,
                            param = statistic.profit.toString()
                        )
                        InfoRow(
                            titleId = R.string.price_printer_title,
                        )
                        Text(
                            modifier = Modifier.padding(top = 16.dp),
                            text = "*До окупаемости принтера - ${5000 - statistic.profit}",
                            color = AppTheme.colors.black9
                        )
                    }
                }
                is StatisticState.Loading -> {
                    Box(
                        modifier = Modifier.fillMaxSize(),
                        contentAlignment = Alignment.Center
                    ) {
                        CircularProgressIndicator(
                            color = AppTheme.colors.orange10,
                        )
                    }
                }

                else -> {}
            }
        }
    }
}


@Composable
private fun InfoRow(
    titleId: Int,
    param: String = "",
    color: Color = AppTheme.colors.black9,
    isList: Boolean = false,
    formats: Map<String, Int> = mapOf()
) {
    Column(
        modifier = Modifier.fillMaxWidth()
    ) {
        Row(
            modifier = Modifier
                .padding(vertical = 16.dp)
                .fillMaxWidth(),
            verticalAlignment = Alignment.CenterVertically,
            horizontalArrangement = Arrangement.SpaceBetween
        ) {
            Text(
                text = String.format(stringResource(titleId), param),
                fontSize = 20.sp,
                fontWeight = FontWeight.Medium,
                color = color
            )
        }
        if (isList) {
            Column(
                modifier = Modifier.fillMaxWidth()
            ) {
                Text(
                    modifier = Modifier.padding(horizontal = 16.dp, vertical = 4.dp),
                    text = "A1: ${formats["A1"]} штук",
                    fontSize = 16.sp,
                    fontWeight = FontWeight.Normal,
                    color = color
                )
                Text(
                    modifier = Modifier.padding(horizontal = 16.dp, vertical = 4.dp),
                    text = "A2: ${formats["A2"]} штук",
                    fontSize = 16.sp,
                    fontWeight = FontWeight.Normal,
                    color = color
                )
                Text(
                    modifier = Modifier.padding(horizontal = 16.dp, vertical = 4.dp),
                    text = "A3: ${formats["A3"]} штук",
                    fontSize = 16.sp,
                    fontWeight = FontWeight.Normal,
                    color = color
                )
                Text(
                    modifier = Modifier.padding(horizontal = 16.dp, vertical = 4.dp),
                    text = "A4: ${formats["A4"]} штук",
                    fontSize = 16.sp,
                    fontWeight = FontWeight.Normal,
                    color = color
                )
                Text(
                    modifier = Modifier.padding(horizontal = 16.dp, vertical = 4.dp),
                    text = "A5: ${formats["A5"]} штук",
                    fontSize = 16.sp,
                    fontWeight = FontWeight.Normal,
                    color = color
                )
                Text(
                    modifier = Modifier.padding(horizontal = 16.dp, vertical = 4.dp),
                    text = "A6: ${formats["A6"]} штук",
                    fontSize = 16.sp,
                    fontWeight = FontWeight.Normal,
                    color = color
                )
            }
            Spacer(Modifier.height(16.dp))
        }
        HorizontalDivider(color = AppTheme.colors.black9)
    }
}

@Preview(showBackground = true)
@Composable
private fun StatisticScreenPreview() {
    StatisticScreen({}, {})
}