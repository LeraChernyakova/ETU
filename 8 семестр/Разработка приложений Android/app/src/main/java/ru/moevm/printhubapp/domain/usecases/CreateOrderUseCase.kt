package ru.moevm.printhubapp.domain.usecases

import ru.moevm.printhubapp.domain.entity.Order
import ru.moevm.printhubapp.domain.entity.result.RequestResult
import ru.moevm.printhubapp.domain.repository.OrdersRepository
import javax.inject.Inject

class CreateOrderUseCase @Inject constructor(private val ordersRepository: OrdersRepository) {
    operator fun invoke(newOrder: Order, callback: (RequestResult<Unit>) -> Unit) =
        ordersRepository.createOrder(newOrder, callback)
}