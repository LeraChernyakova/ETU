package ru.moevm.printhubapp.data.repository

import android.content.SharedPreferences
import android.util.Log
import ru.moevm.printhubapp.data.mapper.toEntity
import ru.moevm.printhubapp.data.model.OrderDto
import ru.moevm.printhubapp.data.model.StatisticDto
import ru.moevm.printhubapp.data.model.UserDto
import ru.moevm.printhubapp.domain.entity.Statistic
import ru.moevm.printhubapp.domain.entity.User
import ru.moevm.printhubapp.domain.repository.PrinthubsRepository
import ru.moevm.printhubapp.utils.Constants.UID_STRING
import com.google.firebase.firestore.FirebaseFirestore
import kotlinx.coroutines.tasks.await

class PrinthubsRepositoryImpl (
    private val db: FirebaseFirestore,
    private val sharedPreferences: SharedPreferences
) : PrinthubsRepository {

    private val users = db.collection("users")
    private val statistics = db.collection("statistics")

    override suspend fun getPrinthubs(): List<User> {
        val querySnapshot = users.whereEqualTo("role", "printhub").get().await()
        val printhubs = querySnapshot.documents.mapNotNull { it.toObject(UserDto::class.java)?.toEntity() }
        if (printhubs.isNotEmpty()) {
            return printhubs
        } else {
            throw Exception("Printhub not found")
        }
    }

    override suspend fun getStatistic(): Statistic {
        val userUid = sharedPreferences.getString(UID_STRING, "") ?: ""
        val querySnapshot = statistics.whereEqualTo("companyId", userUid).get().await()
        val statisticDto = querySnapshot.documents.firstOrNull()?.toObject(StatisticDto::class.java)
        Log.d("PrinthubsRepositoryImpl", "Fetched statisticDto: $statisticDto")
        val statistic = statisticDto?.toEntity()
        Log.d("PrinthubsRepositoryImpl", "Converted to entity: $statistic")
        if (statistic != null) {
            return statistic
        } else {
            throw Exception("Printhub not found")
        }
    }
}