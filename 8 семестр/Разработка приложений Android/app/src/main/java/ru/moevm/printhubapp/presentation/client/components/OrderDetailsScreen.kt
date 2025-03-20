package ru.moevm.printhubapp.presentation.client.components

import androidx.compose.foundation.BorderStroke
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
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.FloatingActionButton
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
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.compose.ui.platform.LocalContext
import android.content.Context
import android.content.Intent
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.domain.entity.Order
import ru.moevm.printhubapp.presentation.client.state.OrderDetailsState
import ru.moevm.printhubapp.presentation.client.viewmodels.OrderDetailsViewModel
import ru.moevm.printhubapp.ui.theme.AppTheme
import ru.moevm.printhubapp.utils.getDisplayStatus
import ru.moevm.printhubapp.utils.getStatusColor

@Composable
fun OrderDetailsScreen(
    onBack: () -> Unit,
    onAbout: () -> Unit,
    orderId: String
) {
    val viewModel: OrderDetailsViewModel = hiltViewModel()
    val state by viewModel.state.collectAsState()
    val context = LocalContext.current

    LaunchedEffect(orderId) {
        viewModel.getOrder(orderId)
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
                        val id =
                            if (state is OrderDetailsState.Success) (state as OrderDetailsState.Success).order.number else ""
                        Text(
                            text = String.format(
                                stringResource(R.string.order_details_title),
                                id
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
        }
    ) { paddingValues ->
        Box(
            modifier = Modifier
                .fillMaxSize()
                .padding(paddingValues)
        ) {
            when (state) {
                is OrderDetailsState.Success -> {
                    val order = (state as OrderDetailsState.Success).order
                    Column(
                        modifier = Modifier.padding(16.dp)
                    ) {
                        Row(
                            verticalAlignment = Alignment.CenterVertically
                        ) {
                            Text(
                                text = "Статус заказа",
                                fontSize = 16.sp,
                                color = AppTheme.colors.gray7
                            )
                            Spacer(modifier = Modifier.width(8.dp))
                            Text(
                                modifier = Modifier
                                    .background(
                                        getStatusColor(order.status),
                                        RoundedCornerShape(10.dp)
                                    )
                                    .padding(vertical = 4.dp, horizontal = 8.dp),
                                text = getDisplayStatus(order.status),
                                fontSize = 16.sp,
                                color = Color.White
                            )
                        }
                        Spacer(modifier = Modifier.height(16.dp))
                        OrderCardDetails(order)
                        DetailsRow(
                            titleId = R.string.format_print,
                            parameter = order.format
                        )
                        DetailsRow(
                            titleId = R.string.count_list_with_param,
                            parameter = order.paperCount.toString()
                        )
                        DetailsRow(
                            titleId = R.string.file,
                            parameter = ""
                        )
                        Spacer(modifier = Modifier.height(16.dp))
                        Text(
                            modifier = Modifier
                                .align(Alignment.End)
                                .background(AppTheme.colors.orange3, RoundedCornerShape(16.dp))
                                .padding(vertical = 4.dp, horizontal = 8.dp),
                            text = "Итого: ${order.totalPrice} ₽",
                            fontSize = 20.sp,
                            fontWeight = FontWeight.SemiBold,
                            color = AppTheme.colors.black9
                        )
                        if (order.comment.isNotEmpty()) {
                            Spacer(Modifier.height(16.dp))
                            Comment(
                                titleId = R.string.placeholder_comment,
                                comment = order.comment
                            )
                        }
                        if (order.rejectReason.isNotEmpty()) {
                            Spacer(Modifier.height(16.dp))
                            Comment(
                                titleId = R.string.reason_reject,
                                comment = order.rejectReason
                            )
                        }
                    }
                    Box(
                        modifier = Modifier
                            .fillMaxSize()
                            .padding(paddingValues)
                            .padding(16.dp)
                    ) {
                        FloatingActionButton(
                            onClick = {
                                if (state is OrderDetailsState.Success) {
                                    val order = (state as OrderDetailsState.Success).order
                                    shareOrderDetails(context, order)
                                }
                            },
                            modifier = Modifier
                                .align(Alignment.BottomEnd)
                                .padding(16.dp),
                            shape = CircleShape,
                            containerColor = AppTheme.colors.orange10,
                            contentColor = AppTheme.colors.black9
                        ) {
                            Icon(
                                painter = painterResource(R.drawable.share_ic),
                                contentDescription = null
                            )
                        }
                    }
                }

                is OrderDetailsState.Loading -> {
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
private fun DetailsRow(
    titleId: Int,
    parameter: String
) {
    Button(
        modifier = Modifier
            .fillMaxWidth()
            .padding(top = 8.dp),
        enabled = false,
        onClick = {},
        shape = RoundedCornerShape(12.dp),
        colors = ButtonDefaults.buttonColors(
            disabledContentColor = AppTheme.colors.gray7,
            disabledContainerColor = AppTheme.colors.gray1,
        ),
        border = BorderStroke(1.dp, AppTheme.colors.gray7)
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(vertical = 8.dp),
            verticalAlignment = Alignment.CenterVertically
        ) {
            Text(
                text = stringResource(titleId),
                fontSize = 16.sp,
                fontWeight = FontWeight.Normal,
                color = AppTheme.colors.black9
            )
            Spacer(Modifier.width(4.dp))
            Text(
                text = parameter,
                fontSize = 16.sp,
                fontWeight = FontWeight.SemiBold,
                color = AppTheme.colors.black9
            )
        }
    }
}

@Composable
private fun Comment(
    titleId: Int,
    comment: String
) {
    Column {
        Text(
            modifier = Modifier.padding(bottom = 4.dp),
            text = stringResource(titleId),
            fontSize = 16.sp,
            color = AppTheme.colors.gray7
        )
        OutlinedTextField(
            modifier = Modifier
                .fillMaxWidth()
                .height(100.dp),
            value = comment,
            readOnly = true,
            onValueChange = {},
            textStyle = TextStyle(
                fontSize = 16.sp,
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
    }
}

private fun shareOrderDetails(context: Context, order: Order) {
    val shareText = formatOrderDetails(order)
    val sendIntent = Intent().apply {
        action = Intent.ACTION_SEND
        putExtra(Intent.EXTRA_TEXT, shareText)
        type = "text/plain"
    }
    val shareIntent = Intent.createChooser(sendIntent, null)
    context.startActivity(shareIntent)
}

private fun formatOrderDetails(order: Order): String {
    return """
        Заказ №${order.number}
        Статус: ${getDisplayStatus(order.status)}
        
        Название печатной компании: ${order.nameCompany}
        Адрес: ${order.address}
        
        Формат: ${order.format}
        Количество листов: ${order.paperCount}
        
        Итого: ${order.totalPrice} ₽
        ${if (order.comment.isNotEmpty()) "\nКомментарий: ${order.comment}" else ""}
        ${if (order.rejectReason.isNotEmpty()) "\nПричина отказа: ${order.rejectReason}" else ""}
    """.trimIndent()
}

@Preview(showBackground = true)
@Composable
private fun OrderDetailsScreenPreview() {
    OrderDetailsScreen({}, {}, orderId = "1")
}