package ru.moevm.printhubapp.presentation.printhub.components

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.domain.entity.Order
import ru.moevm.printhubapp.presentation.client.utils.formatToString
import ru.moevm.printhubapp.ui.theme.AppTheme
import ru.moevm.printhubapp.utils.getStatusColor

@Composable
fun OrderPrinthubCard(
    order: Order,
    openDetails: (String) -> Unit
) {
    Card(
        modifier = Modifier.fillMaxWidth(),
        onClick = { openDetails(order.id) },
        colors = CardDefaults.cardColors(
            containerColor = AppTheme.colors.orange3 ,
            contentColor = AppTheme.colors.black9,
        ),
    ) {
        Column(
            modifier = Modifier.padding(16.dp)
        ) {
            Text(
                modifier = Modifier
                    .background(getStatusColor(order.status), RoundedCornerShape(10.dp))
                    .padding(vertical = 4.dp, horizontal = 8.dp),
                text = if (order.status == "Создан") "Новый" else order.status,
                fontSize = 16.sp,
                color = Color.White
            )
            Spacer(Modifier.height(8.dp))
            Text(
                text = String.format(stringResource(R.string.order_number), order.number),
                fontSize = 16.sp,
            )
            Spacer(Modifier.height(8.dp))
            Text(
                text = String.format("Клиент: %s", order.clientMail),
                fontSize = 16.sp,
            )
            Spacer(Modifier.height(8.dp))
            Text(
                text = String.format("Файл: %s", order.files),
                fontSize = 16.sp,
            )
            Spacer(Modifier.height(8.dp))
            Text(
                text = String.format(
                    stringResource(R.string.date_of_create),
                    order.createdAt.formatToString()
                ),
                fontSize = 16.sp
            )
            Spacer(Modifier.height(8.dp))
            Text(
                text = String.format(
                    stringResource(R.string.date_of_last_change),
                    order.updatedAt.formatToString()
                ),
                fontSize = 16.sp,
            )
        }
    }
}

@Preview
@Composable
private fun OrderPrinthubCardPreview() {
    val order = Order(
        id = "1",
        status = "В процессе"
    )
    OrderPrinthubCard(order = order, {})
}