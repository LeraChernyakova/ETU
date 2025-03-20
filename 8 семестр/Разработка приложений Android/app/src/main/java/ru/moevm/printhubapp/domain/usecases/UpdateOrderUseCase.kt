package ru.moevm.printhubapp.domain.usecases

import ru.moevm.printhubapp.domain.entity.Order
import ru.moevm.printhubapp.domain.entity.result.RequestResult
import ru.moevm.printhubapp.domain.repository.OrdersRepository
import javax.inject.Inject

class UpdateOrderUseCase @Inject constructor(private val ordersRepository: OrdersRepository) {
    operator fun invoke(updatedOrder: Order, callback: (RequestResult<Unit>) -> Unit) =
        ordersRepository.updateOrder(updatedOrder, callback)
}