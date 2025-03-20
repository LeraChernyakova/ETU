package ru.moevm.printhubapp.presentation.client.components

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
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.domain.entity.Order
import ru.moevm.printhubapp.domain.entity.Role
import ru.moevm.printhubapp.domain.entity.User
import ru.moevm.printhubapp.presentation.client.viewmodels.AddOrderViewModel
import ru.moevm.printhubapp.ui.theme.AppTheme
import kotlin.random.Random

@Composable
fun PrintHubCard(
    printhub: User,
    format: String,
    paperCount: Int,
    comment: String,
    totalPrice: Int,
    onSuccess: () -> Unit,
    viewModel: AddOrderViewModel
) {
    Card(
        modifier = Modifier.fillMaxWidth(),
        onClick = {
            viewModel.createOrder(
                Order(
                    id = "",
                    clientId = "",
                    companyId = printhub.id,
                    number = Random.nextInt(1000000),
                    format = format,
                    paperCount = paperCount,
                    files = "print_file.pdf",
                    totalPrice = totalPrice,
                    comment = comment,
                    status = "Создан",
                    rejectReason = "",
                ),
                onSuccess
            )
        },
        colors = CardDefaults.cardColors(
            containerColor = AppTheme.colors.orange3 ,
            contentColor = AppTheme.colors.black9,
        ),
    ) {
        Column(
            modifier = Modifier.padding(16.dp)
        ) {
            Text(
                text = String.format(stringResource(R.string.print_hub_name), printhub.nameCompany),
                fontSize = 16.sp,
            )
            Spacer(Modifier.height(8.dp))
            Text(
                text = String.format(stringResource(R.string.address_print_hub), printhub.address),
                fontSize = 16.sp,
            )
        }
    }
}

@Preview(showBackground = true)
@Composable
private fun PrintHubCardPreview() {
    val printhub = User(
        nameCompany = "PrintHub",
        address = "ул. Пушкина, д. Колотушкина",
        id = "",
        mail = "",
        password = "",
        role = Role.PRINTHUB,
        statisticId = ""
    )

    val previewViewModel = androidx.lifecycle.viewmodel.compose.viewModel<AddOrderViewModel>()

    PrintHubCard(
        printhub = printhub,
        format = "A4",
        paperCount = 1,
        comment = "Test comment",
        totalPrice = 100,
        onSuccess = {},
        viewModel = previewViewModel
    )
}