package ru.moevm.printhubapp.presentation.auth.components

import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.domain.entity.Role

enum class RegistrationDropDownItem(val value: Int, val role: Role) {
    CLIENT(R.string.client_role, Role.CLIENT),
    PRINTHUB(R.string.printhub_role, Role.PRINTHUB)
}