package ru.moevm.printhubapp.domain.repository

import ru.moevm.printhubapp.domain.entity.Order
import ru.moevm.printhubapp.domain.entity.result.RequestResult

interface OrdersRepository {
    suspend fun getClientOrders() : List<Order>
    suspend fun getPrinthubOrders() : List<Order>
    suspend fun getOrder(id: String) : Order
    fun createOrder(newOrder: Order, callback: (RequestResult<Unit>) -> Unit)
    fun updateOrder(updatedOrder: Order, callback: (RequestResult<Unit>) -> Unit)
}