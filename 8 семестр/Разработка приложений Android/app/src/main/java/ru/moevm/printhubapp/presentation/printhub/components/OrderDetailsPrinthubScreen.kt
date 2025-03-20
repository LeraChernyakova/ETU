package ru.moevm.printhubapp.presentation.printhub.components

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
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
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
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.hilt.navigation.compose.hiltViewModel
import com.google.firebase.Timestamp
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.presentation.client.state.OrderDetailsState
import ru.moevm.printhubapp.presentation.printhub.viewmodels.OrderDetailsViewModel
import ru.moevm.printhubapp.ui.theme.AppTheme
import ru.moevm.printhubapp.utils.getStatusColor

@Composable
fun OrderDetailsPrinthubScreen(
    orderId: String,
    onBack: () -> Unit,
    onAbout: () -> Unit
) {
    var status by remember { mutableStateOf(OrderPrinthubStatus.NEW) }
    var isVisibleRejectDialog by remember { mutableStateOf(false) }

    val viewModel: OrderDetailsViewModel = hiltViewModel()
    val state by viewModel.state.collectAsState()

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
                        val id = if(state is OrderDetailsState.Success) (state as OrderDetailsState.Success).order.number else ""
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
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(paddingValues)
                .padding(16.dp),
            verticalArrangement = Arrangement.SpaceBetween
        ) {
            Column(
                modifier = Modifier.fillMaxWidth()
            ) {
                when (state) {
                    is OrderDetailsState.Success -> {
                        val order = (state as OrderDetailsState.Success).order
                        status = safeValueOf(order.status)
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
                                text = if (order.status == "Создан") "Новый" else order.status,
                                fontSize = 16.sp,
                                color = Color.White
                            )
                        }
                        Spacer(modifier = Modifier.height(16.dp))
                        DateOrderCard(order)
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
                        if(order.comment.isNotEmpty()) {
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
                    is OrderDetailsState.Loading -> {
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

            if(status == OrderPrinthubStatus.NEW) {
                Column(
                    modifier = Modifier.fillMaxWidth()
                ) {
                    Button(
                        onClick = {
                            status = OrderPrinthubStatus.INWORK
                            val updatedOrder = (state as? OrderDetailsState.Success)?.order?.copy(
                                status = "В работе",
                                updatedAt = Timestamp.now()
                            )
                            if (updatedOrder != null) {
                                viewModel.updateOrder(updatedOrder)
                            }
                        },
                        modifier = Modifier.fillMaxWidth(),
                        colors = ButtonDefaults.buttonColors(
                            containerColor = AppTheme.colors.orange10,
                            contentColor = AppTheme.colors.black9,
                        ),
                        shape = RoundedCornerShape(12.dp)
                    ) {
                        Text(
                            modifier = Modifier.padding(vertical = 8.dp),
                            text = stringResource(R.string.take_order_button_text),
                            fontSize = 20.sp,
                            fontWeight = FontWeight.Medium
                        )
                    }
                    Spacer(Modifier.height(16.dp))
                    Button(
                        onClick = { isVisibleRejectDialog = true },
                        modifier = Modifier.fillMaxWidth(),
                        colors = ButtonDefaults.buttonColors(
                            containerColor = AppTheme.colors.gray2,
                            contentColor = AppTheme.colors.black9
                        ),
                        shape = RoundedCornerShape(12.dp)
                    ) {
                        Text(
                            modifier = Modifier.padding(vertical = 8.dp),
                            text = stringResource(R.string.reject_order_button),
                            fontSize = 20.sp,
                            fontWeight = FontWeight.Medium
                        )
                    }
                }
            }
            if(status == OrderPrinthubStatus.INWORK) {
                Button(
                    onClick = {
                        status = OrderPrinthubStatus.AWAIT
                        val updatedOrder = (state as? OrderDetailsState.Success)?.order?.copy(
                            status = "Ожидает получения",
                            updatedAt = Timestamp.now()
                        )
                        if (updatedOrder != null) {
                            viewModel.updateOrder(updatedOrder)
                        }
                    },
                    modifier = Modifier.fillMaxWidth(),
                    colors = ButtonDefaults.buttonColors(
                        containerColor = AppTheme.colors.orange10,
                        contentColor = AppTheme.colors.black9,
                    ),
                    shape = RoundedCornerShape(12.dp)
                ) {
                    Text(
                        modifier = Modifier.padding(vertical = 8.dp),
                        text = stringResource(R.string.finish_button),
                        fontSize = 20.sp,
                        fontWeight = FontWeight.Medium
                    )
                }
            }
            if(status == OrderPrinthubStatus.AWAIT) {
                Button(
                    onClick = {
                        status = OrderPrinthubStatus.READE
                        val updatedOrder = (state as? OrderDetailsState.Success)?.order?.copy(
                            status = "Выполнен",
                            updatedAt = Timestamp.now()
                        )
                        if (updatedOrder != null) {
                            viewModel.updateOrder(updatedOrder)
                        }
                    },
                    modifier = Modifier.fillMaxWidth(),
                    colors = ButtonDefaults.buttonColors(
                        containerColor = AppTheme.colors.orange10,
                        contentColor = AppTheme.colors.black9,
                    ),
                    shape = RoundedCornerShape(12.dp)
                ) {
                    Text(
                        modifier = Modifier.padding(vertical = 8.dp),
                        text = stringResource(R.string.finish_order_button),
                        fontSize = 20.sp,
                        fontWeight = FontWeight.Medium
                    )
                }
            }
        }
    }
    if (isVisibleRejectDialog) {
        RejectDialog(
            onDismiss = {
                isVisibleRejectDialog = false
            },
            onChangeStatus = { comment ->
                status = OrderPrinthubStatus.REJECT
                val updatedOrder = (state as? OrderDetailsState.Success)?.order?.copy(
                    status = "Отказ",
                    rejectReason = comment,
                    updatedAt = Timestamp.now()
                )
                if (updatedOrder != null) {
                    viewModel.updateOrder(updatedOrder)
                }
            }
        )
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
    comment: String,
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

private fun safeValueOf(status: String): OrderPrinthubStatus {
    return try {
        when (status) {
            "Создан" -> OrderPrinthubStatus.NEW
            "В работе" -> OrderPrinthubStatus.INWORK
            "Ожидает получения" -> OrderPrinthubStatus.AWAIT
            "Выполнен" -> OrderPrinthubStatus.READE
            "Отказ" -> OrderPrinthubStatus.REJECT
            else -> OrderPrinthubStatus.NEW
        }
    } catch (e: IllegalArgumentException) {
        OrderPrinthubStatus.NEW
    }
}

@Preview(showBackground = true)
@Composable
private fun OrderDetailsPrinthubScreenPreview() {
    OrderDetailsPrinthubScreen(orderId = "1", {}, {})
}