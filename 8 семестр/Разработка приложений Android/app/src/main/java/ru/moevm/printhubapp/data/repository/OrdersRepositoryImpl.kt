package ru.moevm.printhubapp.data.repository

import android.content.SharedPreferences
import android.util.Log
import ru.moevm.printhubapp.data.mapper.toDto
import ru.moevm.printhubapp.data.mapper.toEntity
import ru.moevm.printhubapp.data.model.OrderDto
import ru.moevm.printhubapp.domain.entity.Order
import ru.moevm.printhubapp.domain.entity.result.RequestError
import ru.moevm.printhubapp.domain.entity.result.RequestResult
import ru.moevm.printhubapp.domain.repository.OrdersRepository
import ru.moevm.printhubapp.utils.Constants.UID_STRING
import com.google.firebase.Timestamp
import com.google.firebase.firestore.FirebaseFirestore
import com.google.firebase.firestore.toObject
import kotlinx.coroutines.tasks.await
import ru.moevm.printhubapp.data.model.UserDto
import ru.moevm.printhubapp.domain.entity.User

class OrdersRepositoryImpl(
    private val db: FirebaseFirestore,
    private val sharedPreferences: SharedPreferences
) : OrdersRepository {

    private val orders = db.collection("orders")
    private val users = db.collection("users")
    private val statistics = db.collection("statistics")

    private val userUid: String
        get() = sharedPreferences.getString(UID_STRING, "") ?: ""

    override suspend fun getClientOrders(): List<Order> {
        val ordersList = mutableListOf<Order>()

        try {
            val querySnapshot = orders.whereEqualTo("client_id", userUid).get().await()
            Log.d("OrderListScreen", "Found ${querySnapshot.documents.size} raw documents")

            for (document in querySnapshot.documents) {
                val orderDto = document.toObject(OrderDto::class.java)
                if (orderDto != null) {
                    val order = orderDto.toEntity()

                    if (order.companyId.isNotEmpty()) {
                        val companySnapshot = users.document(order.companyId).get().await()
                        order.nameCompany = companySnapshot.getString("nameCompany") ?: "Неизвестно"
                        order.address = companySnapshot.getString("address") ?: "Неизвестно"
                    } else {
                        Log.w("OrderListScreen", "Order has empty companyId: ${order.id}")
                        order.nameCompany = "Не указано"
                        order.address = "Адрес не указан"
                    }

                    ordersList.add(order)
                }
            }
        } catch (e: Exception) {
            Log.e("OrderListScreen", "Ошибка загрузки заказов: ${e.message}")
        }

        return ordersList
    }

    override suspend fun getPrinthubOrders(): List<Order> {
        val ordersList = mutableListOf<Order>()
        try {
            Log.d("OrderListScreenId", "printer id $userUid")
            val querySnapshot = orders.whereEqualTo("company_id", userUid).get().await()
            Log.d("OrderListScreen", "Found ${querySnapshot.documents.size} raw documents")

            for (document in querySnapshot.documents) {
                val orderDto = document.toObject(OrderDto::class.java)
                if (orderDto != null) {
                    val order = orderDto.toEntity()
                    ordersList.add(order)
                }
            }
        } catch (e: Exception) {
            Log.e("OrderListScreen", "Ошибка загрузки заказов: ${e.message}")
        }

        return ordersList
    }

    override suspend fun getOrder(id: String): Order {
        val orderDto = orders.document(id).get().await().toObject(OrderDto::class.java)
        val order = orderDto?.toEntity()
        if (order != null) {
            if (order.companyId.isNotEmpty()) {
                val companySnapshot = users.document(order.companyId).get().await()
                order.nameCompany = companySnapshot.getString("nameCompany") ?: "Неизвестно"
                order.address = companySnapshot.getString("address") ?: "Неизвестно"
            } else {
                Log.w("OrderListScreen", "Order has empty companyId: ${order.id}")
                order.nameCompany = "Не указано"
                order.address = "Адрес не указан"
            }
        }
        return order ?: throw Exception("Order not found")
    }

    private fun getUser(callback: (User) -> Unit) {
        val userUid = sharedPreferences.getString(UID_STRING, "") ?: ""
        Log.d("TAG", userUid)
        users.document(userUid).get().addOnSuccessListener { data ->
            callback(
                data.toObject<UserDto>()?.toEntity() ?: throw RuntimeException("user not found")
            )
        }
    }

    override fun createOrder(newOrder: Order, callback: (RequestResult<Unit>) -> Unit) {
        getUser { user ->
            val updatedOrder = newOrder.copy(
                clientId = userUid,
                clientMail = user.mail
            )

            Log.w("createOrder", "Client id ${userUid}, email ${user.mail}")
            val orderDto = updatedOrder.toDto()
            val documentRef = orders.document()

            documentRef.set(orderDto).addOnSuccessListener {
                documentRef.update("id", documentRef.id).addOnSuccessListener {
                    callback(RequestResult.Success(Unit))
                }.addOnFailureListener { e ->
                    callback(RequestResult.Error(RequestError.Server("Ошибка обновления ID: ${e.message}")))
                }
            }.addOnFailureListener { e ->
                callback(RequestResult.Error(RequestError.Server("Ошибка сохранения данных: ${e.message}")))
            }
        }
    }

    override fun updateOrder(updatedOrder: Order, callback: (RequestResult<Unit>) -> Unit) {
        val documentRef = orders.document(updatedOrder.id)
        val updates = mutableMapOf<String, Any>(
            "status" to updatedOrder.status,
            "updated_at" to Timestamp.now()
        )

        if (updatedOrder.rejectReason.isNotEmpty()) {
            updates["reject_reason"] = updatedOrder.rejectReason
        }

        documentRef.update(updates).addOnSuccessListener {
            if (updatedOrder.status == "Выполнен") {
                statistics.whereEqualTo("companyId", updatedOrder.companyId).get().addOnSuccessListener { querySnapshot ->
                    val statisticDocument = querySnapshot.documents.firstOrNull()
                    if (statisticDocument != null) {
                        val statisticRef = statistics.document(statisticDocument.id)
                        val currentFormatsCount = statisticDocument.get("formatsCount") as Map<String, Int>
                        val currentProfit = statisticDocument.getLong("profit")?.toInt() ?: 0
                        val currentTotalPaperCount = statisticDocument.getLong("totalPaperCount")?.toInt() ?: 0

                        val updatedFormatsCount = currentFormatsCount.toMutableMap().apply {
                            this[updatedOrder.format] = this.getOrDefault(updatedOrder.format, 0) + updatedOrder.paperCount
                        }

                        val statisticUpdates = mutableMapOf<String, Any>(
                            "formatsCount" to updatedFormatsCount,
                            "profit" to (currentProfit + updatedOrder.totalPrice),
                            "totalPaperCount" to (currentTotalPaperCount + updatedOrder.paperCount)
                        )

                        statisticRef.update(statisticUpdates).addOnSuccessListener {
                            callback(RequestResult.Success(Unit))
                        }.addOnFailureListener { e ->
                            callback(RequestResult.Error(RequestError.Server("Ошибка обновления статистики: ${e.message}")))
                        }
                    } else {
                        callback(RequestResult.Error(RequestError.Server("Статистика не найдена")))
                    }
                }.addOnFailureListener { e ->
                    callback(RequestResult.Error(RequestError.Server("Ошибка получения статистики: ${e.message}")))
                }
            } else {
                callback(RequestResult.Success(Unit))
            }
        }.addOnFailureListener { e ->
            callback(RequestResult.Error(RequestError.Server("Ошибка обновления данных: ${e.message}")))
        }
    }
}