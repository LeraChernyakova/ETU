package ru.moevm.printhubapp.presentation.client.components

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.compose.ui.window.Dialog
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.ui.theme.AppTheme

@Composable
fun LogoutDialog(
    onLogout: () -> Unit,
    onDismiss: () -> Unit,
) {
    Dialog(
        onDismissRequest = onDismiss
    ) {
        Surface(
            shape = RoundedCornerShape(16.dp),
            color = AppTheme.colors.materialColors.background
        ) {
            Column(
                modifier = Modifier
                    .padding(16.dp)
            ) {
                Text(
                    modifier = Modifier.align(Alignment.CenterHorizontally),
                    text = stringResource(R.string.logout_dialog_title),
                    fontSize = 24.sp,
                    fontWeight = FontWeight.Medium,
                    color = AppTheme.colors.black9
                )
                Spacer(modifier = Modifier.height(32.dp))
                Button(
                    onClick = onLogout,
                    modifier = Modifier.fillMaxWidth(),
                    colors = ButtonDefaults.buttonColors(
                        containerColor = AppTheme.colors.orange10,
                        contentColor = AppTheme.colors.black9,
                    ),
                    shape = RoundedCornerShape(12.dp)
                ) {
                    Text(
                        modifier = Modifier.padding(vertical = 8.dp),
                        text = stringResource(R.string.logout_button),
                        fontSize = 20.sp,
                        fontWeight = FontWeight.Medium
                    )
                }
                Spacer(modifier = Modifier.height(8.dp))
                Button(
                    onClick = onDismiss,
                    modifier = Modifier.fillMaxWidth(),
                    colors = ButtonDefaults.buttonColors(
                        containerColor = AppTheme.colors.gray1,
                        contentColor = AppTheme.colors.black9,
                    ),
                    shape = RoundedCornerShape(12.dp)
                ) {
                    Text(
                        modifier = Modifier.padding(vertical = 8.dp),
                        text = stringResource(R.string.reject_button),
                        fontSize = 20.sp,
                        fontWeight = FontWeight.Medium
                    )
                }
            }
        }
    }
}

@Preview(showBackground = true)
@Composable
private fun LogoutDialogPreview() {
    LogoutDialog({}, {})
}