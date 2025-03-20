package ru.moevm.printhubapp.presentation.printhub.components

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import ru.moevm.printhubapp.domain.entity.Order
import ru.moevm.printhubapp.presentation.client.utils.formatToString
import ru.moevm.printhubapp.ui.theme.AppTheme

@Composable
fun DateOrderCard(
    order: Order
) {
    Card(
        modifier = Modifier.fillMaxWidth(),
        colors = CardDefaults.cardColors(
            containerColor = AppTheme.colors.orange3 ,
            contentColor = AppTheme.colors.black9,
        ),
    ) {
        Column(
            modifier = Modifier.padding(16.dp)
        ) {
            Text(
                text = "Дата создания: ${order.createdAt.formatToString()}",
                fontSize = 16.sp,
            )
            Spacer(Modifier.height(8.dp))
            Text(
                text = "Дата обновления: ${order.updatedAt.formatToString()}",
                fontSize = 16.sp,
            )
        }
    }
}

@Preview(showBackground = true)
@Composable
private fun DateOrderCardPreview() {
    val order = Order(
        id = "1",
        status = "В процессе"
    )
    DateOrderCard(order = order)
}