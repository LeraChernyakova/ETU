package ru.moevm.printhubapp.domain.usecases

import ru.moevm.printhubapp.domain.entity.Order
import ru.moevm.printhubapp.domain.repository.OrdersRepository
import javax.inject.Inject

class GetOrderUseCase @Inject constructor(
    private val ordersRepository: OrdersRepository
) {
    suspend operator fun invoke(id: String): Order {
        return ordersRepository.getOrder(id)
    }
}