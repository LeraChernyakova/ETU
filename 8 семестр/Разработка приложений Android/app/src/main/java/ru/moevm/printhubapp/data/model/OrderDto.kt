package ru.moevm.printhubapp.data.model
import com.google.firebase.Timestamp

data class OrderDto(
    val id: String = "",
    val client_id: String = "",
    val client_mail: String = "",
    val company_id: String = "",
    val number: Int = 0,
    val format: String = "",
    val paper_count: Int = 0,
    val files: String = "",
    val total_price: Int = 0,
    val comment: String = "",
    val status: String = "",
    val reject_reason: String = "",
    val created_at: Timestamp = Timestamp.now(),
    val updated_at: Timestamp = Timestamp.now()
)