package ru.moevm.printhubapp.data.repository

import android.content.SharedPreferences
import android.util.Log
import ru.moevm.printhubapp.data.mapper.toEntity
import ru.moevm.printhubapp.data.model.UserDto
import ru.moevm.printhubapp.domain.entity.User
import ru.moevm.printhubapp.domain.repository.UserRepository
import ru.moevm.printhubapp.utils.Constants.UID_STRING
import com.google.firebase.firestore.FirebaseFirestore
import com.google.firebase.firestore.toObject

class UserRepositoryImpl(
    private val db: FirebaseFirestore,
    private val sharedPreferences: SharedPreferences
) : UserRepository {
    private val users = db.collection("users")

    override fun getUser(callback: (User) -> Unit) {
        val userUid = sharedPreferences.getString(UID_STRING, "") ?: ""
        Log.d("TAG", userUid)
        users.document(userUid).get().addOnSuccessListener { data ->
            callback(
                data.toObject<UserDto>()?.toEntity() ?: throw RuntimeException("user not found")
            )
        }
    }
}