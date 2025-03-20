package ru.moevm.printhubapp.presentation.client.components

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.Surface
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
import androidx.compose.ui.window.Dialog
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.ui.theme.AppTheme

@Composable
fun PriceListDialog(
    onDismiss: () -> Unit,
) {
    Dialog(
        onDismissRequest = onDismiss
    ) {
        Surface(
            shape = RoundedCornerShape(16.dp),
            color = AppTheme.colors.orange3
        ) {
            Column(
                modifier = Modifier
                    .padding(16.dp)
            ) {
                Icon(
                    modifier = Modifier.clickable { onDismiss() },
                    painter = painterResource(R.drawable.close_ic),
                    contentDescription = null,
                    tint = AppTheme.colors.black9
                )
                Spacer(modifier = Modifier.height(8.dp))
                Text(
                    modifier = Modifier.align(Alignment.CenterHorizontally),
                    text = stringResource(R.string.price_list_dialog_title),
                    fontSize = 24.sp,
                    fontWeight = FontWeight.Bold,
                    color = AppTheme.colors.black9
                )
                Spacer(modifier = Modifier.height(16.dp))
                PrintFormatItem.entries.forEach {
                    Row(
                        modifier = Modifier.fillMaxWidth(),
                        verticalAlignment = Alignment.CenterVertically,
                    ) {
                        Text(
                            text = stringResource(it.value),
                            fontSize = 24.sp,
                            fontWeight = FontWeight.Medium,
                            color = AppTheme.colors.black9
                        )
                        Spacer(modifier = Modifier.width(48.dp))
                        HorizontalDivider(
                            modifier = Modifier.weight(1f),
                            color = AppTheme.colors.black9
                        )
                        Spacer(modifier = Modifier.width(32.dp))
                        Text(
                            text = it.price.toString() + " ₽",
                            fontSize = 24.sp,
                            fontWeight = FontWeight.Medium,
                            color = AppTheme.colors.black9
                        )
                    }
                    Spacer(modifier = Modifier.height(4.dp))
                }
            }
        }
    }
}

@Preview(showBackground = true)
@Composable
private fun PriceListDialogPreview() {
    PriceListDialog({})
}