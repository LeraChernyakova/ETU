package ru.moevm.printhubapp.presentation.client.components

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.OutlinedTextFieldDefaults
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.hilt.navigation.compose.hiltViewModel
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.presentation.client.state.AddOrderState
import ru.moevm.printhubapp.presentation.client.viewmodels.AddOrderViewModel
import ru.moevm.printhubapp.ui.theme.AppTheme
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.collectLatest
import kotlinx.coroutines.flow.debounce
import kotlinx.coroutines.time.debounce

@Composable
fun AddOrderScreen(
    onAbout: () -> Unit,
    onBack: () -> Unit,
    onSuccess: () -> Unit,
    format: String,
    paperCount: Int,
    comment: String,
    totalPrice: Int
) {
    var search by remember { mutableStateOf("") }
    val searchQuery = remember { MutableStateFlow("") }

    val viewModel: AddOrderViewModel = hiltViewModel()
    val state by viewModel.state.collectAsState()

    LaunchedEffect(searchQuery) {
        searchQuery
            .debounce(500)
            .collectLatest { query ->
                viewModel.searchPrinthubs(query)
            }
    }

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
                            text = stringResource(R.string.add_order_title),
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
        Column(
            modifier = Modifier
                .fillMaxWidth()
                .padding(paddingValues),
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            Text(
                modifier = Modifier
                    .align(Alignment.Start)
                    .padding(start = 16.dp, top = 16.dp, bottom = 8.dp),
                text = stringResource(R.string.choose_printhub),
                fontSize = 16.sp,
                color = AppTheme.colors.gray7
            )
            OutlinedTextField(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(horizontal = 16.dp),
                value = search,
                onValueChange = {
                    search = it
                    searchQuery.value = it
                },
                placeholder = {
                    Text(
                        text = stringResource(R.string.placeholder_choose_address),
                        fontSize = 20.sp,
                        fontWeight = FontWeight.Normal,
                        color = AppTheme.colors.gray7
                    )
                },
                singleLine = true,
                textStyle = TextStyle(
                    fontSize = 20.sp,
                    fontWeight = FontWeight.Normal,
                    color = AppTheme.colors.black9
                ),
                shape = RoundedCornerShape(12.dp),
                colors = OutlinedTextFieldDefaults.colors(
                    unfocusedContainerColor = AppTheme.colors.gray1,
                    focusedContainerColor = AppTheme.colors.gray1,
                    disabledContainerColor = AppTheme.colors.gray1,
                    disabledBorderColor = AppTheme.colors.gray7,
                    unfocusedBorderColor = AppTheme.colors.gray7,
                    focusedBorderColor = AppTheme.colors.gray7
                )
            )
            when (state) {
                is AddOrderState.Success -> {
                    val printhubs = (state as AddOrderState.Success).printhubs
                    Box {
                        LazyColumn(
                            contentPadding = PaddingValues(
                                top = 16.dp,
                                start = 16.dp,
                                end = 16.dp,
                                bottom = 16.dp
                            ),
                            verticalArrangement = Arrangement.spacedBy(8.dp)
                        ) {
                            items(printhubs.size) { index ->
                                PrintHubCard(
                                    printhub = printhubs[index],
                                    format = format,
                                    paperCount = paperCount,
                                    comment = comment,
                                    totalPrice = totalPrice,
                                    onSuccess = onSuccess,
                                    viewModel = viewModel
                                )
                            }
                        }

                    }
                }
                AddOrderState.Loading -> {
                    Box(
                        modifier = Modifier.fillMaxSize(),
                        contentAlignment = Alignment.Center
                    ){
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

@Preview(showBackground = true)
@Composable
private fun AddOrderScreenPreview() {
    AddOrderScreen(
        onAbout = {},
        onBack = {},
        onSuccess = {},
        format = "A4",
        paperCount = 1,
        comment = "",
        totalPrice = 100
    )
}