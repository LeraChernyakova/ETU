package ru.moevm.printhubapp.domain.entity

import com.google.firebase.Timestamp

data class Order(
    val id: String = "",
    val clientId: String = "",
    val companyId: String = "",
    val clientMail: String = "",
    val number: Int = 0,
    val format: String = "",
    val paperCount: Int = 0,
    val files: String = "print_file.pdf",
    val totalPrice: Int = 0,
    val comment: String = "",
    val status: String = "",
    val rejectReason: String = "",
    val createdAt: Timestamp = Timestamp.now(),
    val updatedAt: Timestamp = Timestamp.now()
){
    var nameCompany: String = ""
    var address: String = ""
}