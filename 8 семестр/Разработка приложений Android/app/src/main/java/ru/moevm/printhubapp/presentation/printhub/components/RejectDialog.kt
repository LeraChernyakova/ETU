package ru.moevm.printhubapp.presentation.printhub.components

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.OutlinedTextFieldDefaults
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.compose.ui.window.Dialog
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.ui.theme.AppTheme
import ru.moevm.printhubapp.utils.LIMIT_CHAR_REJECT

@Composable
fun RejectDialog(
    onDismiss: () -> Unit,
    onChangeStatus: (String) -> Unit
) {
    var comment by remember { mutableStateOf("") }
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
                    text = stringResource(R.string.reject_dialog_title),
                    fontSize = 24.sp,
                    fontWeight = FontWeight.Medium,
                    color = AppTheme.colors.black9
                )
                Spacer(Modifier.height(16.dp))
                Text(
                    modifier = Modifier.padding(bottom = 4.dp),
                    text = stringResource(R.string.required_param),
                    fontSize = 16.sp,
                    color = AppTheme.colors.gray7
                )
                OutlinedTextField(
                    modifier = Modifier
                        .fillMaxWidth()
                        .height(100.dp),
                    value = comment,
                    onValueChange = {
                        comment = if(comment.length < LIMIT_CHAR_REJECT) {
                            it
                        } else {
                            it.take(LIMIT_CHAR_REJECT)
                        }
                    },
                    placeholder = {
                        Text(
                            modifier = Modifier
                                .fillMaxSize()
                                .align(Alignment.Start),
                            text = stringResource(R.string.placeholder_comment),
                            fontSize = 16.sp,
                            fontWeight = FontWeight.Normal,
                            color = AppTheme.colors.gray7
                        )
                    },
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
                Spacer(modifier = Modifier.height(4.dp))
                Text(
                    modifier = Modifier.align(Alignment.End),
                    text = "${comment.length} / $LIMIT_CHAR_REJECT",
                    fontSize = 14.sp,
                    color = AppTheme.colors.gray7
                )
                Spacer(modifier = Modifier.height(32.dp))
                val isEnable = comment.isNotEmpty()
                Button(
                    onClick = {
                        onChangeStatus(comment)
                        onDismiss()
                    },
                    enabled = isEnable,
                    modifier = Modifier.fillMaxWidth(),
                    colors = ButtonDefaults.buttonColors(
                        containerColor = AppTheme.colors.orange10,
                        contentColor = AppTheme.colors.black9,
                        disabledContainerColor = AppTheme.colors.gray1,
                        disabledContentColor = AppTheme.colors.gray7
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
private fun RejectDialogPreview() {
    RejectDialog({}, {})
}