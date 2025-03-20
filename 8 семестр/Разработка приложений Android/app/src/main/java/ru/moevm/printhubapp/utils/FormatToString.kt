package ru.moevm.printhubapp.presentation.client.utils

import com.google.firebase.Timestamp
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale

fun Timestamp.formatToString(pattern: String = "dd.MM.yyyy HH:mm"): String {
    val date = Date(seconds * 1000 + nanoseconds / 1000000)
    val formatter = SimpleDateFormat(pattern, Locale.getDefault())
    return formatter.format(date)
}