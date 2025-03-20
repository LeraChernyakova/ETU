package ru.moevm.printhubapp.utils

import android.util.Patterns

fun validateCredentials(mail: String, password: String): ValidateError {
    if (!Patterns.EMAIL_ADDRESS.matcher(mail).matches()) {
        return ValidateError.MAIL
    }
    if (password.length < 6) {
        return ValidateError.PASSWORD
    }
    return ValidateError.SUCCESS
}

enum class ValidateError {
    MAIL,
    PASSWORD,
    SUCCESS
}