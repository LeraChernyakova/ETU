package ru.moevm.printhubapp.presentation.auth.components

import android.content.Context
import android.widget.Toast
import androidx.compose.foundation.Image
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
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.OutlinedTextFieldDefaults
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
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.input.PasswordVisualTransformation
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.hilt.navigation.compose.hiltViewModel
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.domain.entity.Auth
import ru.moevm.printhubapp.presentation.auth.state.AuthState
import ru.moevm.printhubapp.presentation.auth.viewmodels.AuthViewModel
import ru.moevm.printhubapp.ui.theme.AppTheme

@Composable
fun AuthScreen(
    onLoginTo: () -> Unit,
    onRegistration: () -> Unit,
    onAbout: () -> Unit,
    onLoginToPrintHub: () -> Unit
) {
    val viewModel: AuthViewModel = hiltViewModel()
    val state by viewModel.state.collectAsState()

    val context = LocalContext.current
    var login by remember { mutableStateOf("") }
    var password by remember { mutableStateOf("") }

    LaunchedEffect(state) {
        if (state != AuthState.Init && state != AuthState.Loading) {
            showToast(context, state)
        }

        when (state) {
            AuthState.SuccessClient -> onLoginTo()
            AuthState.SuccessPrintHub -> onLoginToPrintHub()
            else -> {}
        }
    }

    if (state == AuthState.Loading) {
        Box(
            modifier = Modifier.fillMaxSize(),
            contentAlignment = Alignment.Center
        ) {
            CircularProgressIndicator(color = AppTheme.colors.orange10)
        }
    } else {
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(
                    top = 32.dp,
                    bottom = 48.dp,
                    start = 16.dp,
                    end = 16.dp
                ),
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.SpaceBetween
        ) {
            Column(
                modifier = Modifier.fillMaxWidth(),
            ) {
                Icon(
                    painter = painterResource(R.drawable.info_ic),
                    contentDescription = null,
                    modifier = Modifier
                        .align(Alignment.End)
                        .clickable { onAbout() },
                    tint = AppTheme.colors.gray7
                )
                Spacer(modifier = Modifier.height(20.dp))
                Image(
                    painter = painterResource(R.drawable.logo_ic),
                    contentDescription = null,
                    modifier = Modifier.align(Alignment.CenterHorizontally),
                )
                Spacer(modifier = Modifier.height(50.dp))
                OutlinedTextField(
                    modifier = Modifier.fillMaxWidth(),
                    value = login,
                    onValueChange = {
                        login = it
                    },
                    placeholder = {
                        Text(
                            text = stringResource(R.string.placeholder_mail),
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
                Spacer(modifier = Modifier.height(16.dp))
                OutlinedTextField(
                    modifier = Modifier.fillMaxWidth(),
                    value = password,
                    onValueChange = {
                        password = it
                    },
                    placeholder = {
                        Text(
                            text = stringResource(R.string.placeholder_password),
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
                    visualTransformation = PasswordVisualTransformation(),
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
            val isEnable = (login.isNotEmpty() && password.isNotEmpty())
            Button(
                onClick = {
                    viewModel.authorization(
                        Auth(
                            mail = login,
                            password = password
                        )
                    )
                },
                modifier = Modifier.fillMaxWidth(),
                enabled = isEnable,
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
                    text = stringResource(R.string.logint_button_text),
                    fontSize = 20.sp,
                    fontWeight = FontWeight.Medium
                )
            }
            Row(
                verticalAlignment = Alignment.CenterVertically,
            ) {
                HorizontalDivider(
                    modifier = Modifier.weight(1f),
                    color = AppTheme.colors.gray7
                )
                Text(
                    text = stringResource(R.string.no_profile_text),
                    modifier = Modifier.weight(2f),
                    textAlign = TextAlign.Center,
                    fontSize = 20.sp,
                    fontWeight = FontWeight.Normal,
                    color = AppTheme.colors.gray7
                )
                HorizontalDivider(
                    modifier = Modifier.weight(1f),
                    color = AppTheme.colors.gray7
                )
            }
            Button(
                onClick = { onRegistration() },
                modifier = Modifier.fillMaxWidth(),
                colors = ButtonDefaults.buttonColors(
                    containerColor = AppTheme.colors.gray2,
                    contentColor = AppTheme.colors.black9
                ),
                shape = RoundedCornerShape(12.dp)
            ) {
                Text(
                    modifier = Modifier.padding(vertical = 8.dp),
                    text = stringResource(R.string.registration_button_text),
                    fontSize = 20.sp,
                    fontWeight = FontWeight.Medium
                )
            }
        }
    }
}

private fun showToast(context: Context, state: AuthState) {
    when (state) {
        is AuthState.UserNotFound -> Toast.makeText(
            context,
            "Пользователь с такой почтой не найден",
            Toast.LENGTH_LONG
        ).show()

        is AuthState.ServerError -> Toast.makeText(
            context,
            "Неверная почта или пароль",
            Toast.LENGTH_LONG
        ).show()

        is AuthState.IncorrectMailFormat -> Toast.makeText(
            context,
            "Некорректный формат почты",
            Toast.LENGTH_LONG
        ).show()

        is AuthState.ShortPassword -> Toast.makeText(
            context,
            "Пароль должен быть не менее 6 символов",
            Toast.LENGTH_LONG
        ).show()

        is AuthState.NetworkError -> Toast.makeText(
            context,
            "Ошибка подключения. Проверьте сеть Интернета",
            Toast.LENGTH_LONG
        ).show()

        is AuthState.InvalidPassword -> Toast.makeText(
            context,
            "Неверный пароль",
            Toast.LENGTH_LONG
        ).show()

        else -> {}
    }
}

@Preview(showBackground = true)
@Composable
private fun AuthScreenPreview() {
    AuthScreen({}, {}, {}, {})
}