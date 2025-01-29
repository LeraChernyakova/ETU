<template>
  <Navbar :username="username" :position="position">
    <AuthForm
        :title="title"
        :width="containerWidth"
        :height="containerHeight"
    >
      <DataForm fast-fail>
        <DataInput v-model="email" label="Почта" id="email-input"></DataInput>
        <DataInput v-model="surname" label="Фамилия" id="surname-input"></DataInput>
        <DataInput v-model="name" label="Имя" id="name-input"></DataInput>
        <DataInput v-model="lastname" label="Отчество" id="lastname-input"></DataInput>
        <DataInput
            :append-inner-icon="show1 ? 'mdi-eye' : 'mdi-eye-off'"
            v-model="password"
            label="Пароль"
            :type="show1 ? 'text' : 'password'"
            @click:append-inner="show1 = !show1"
            id="password-input">
        </DataInput>
        <DataButton title='готово' @click="createUser" id="create-button"></DataButton>
        <DataButton class="cancel" title='отмена' @click="cancel"></DataButton>
      </DataForm>
    </AuthForm>
  </Navbar>
</template>

<script>
import DataInput from "@/components/Data/DataInput.vue";
import DataForm from "@/components/Data/DataForm.vue";
import DataButton from "@/components/Data/DataButton.vue";
import AuthForm from "@/components/AuthForm.vue";

import axios from 'axios';
import Navbar from "@/components/Navbar.vue";

const CREATE_URL = '/api/user/'

export default {
  name: "CreateUser",
  components: {Navbar, AuthForm, DataButton, DataForm, DataInput},

  data() {
    return {
      username: '',
      position: '',
      title: 'Регистрация',
      containerWidth: '27%',
      containerHeight: '75%',
      email: '',
      surname: '',
      name: '',
      lastname: '',
      password: '',
      show1: false
    };
  },

  beforeMount() {
    let name = sessionStorage.getItem("name");
    if (name) {
      const position = sessionStorage.getItem("position");
      if (position === "regular") {
        const error = 'Request failed. You dont have enough rights to perform the action!'
        alert(error)
        console.log("Недостаточно прав");
        this.$router.push("/e.moevm.statistics/statistics");
      }
      else {
        this.username = name;
        this.position = position;
      }
    } else {
      const error = 'Request failed with status code 401. You are not sign in!'
      alert(error)
      console.log("Не авторизован");
      this.$router.push("/e.moevm.statistics/auth");
    }
  },

  methods: {
    createUser() {
      const userData = {
        email: this.email,
        surname: this.surname,
        name: this.name,
        lastname: this.lastname,
        password: this.password
      };

      axios
          .post(CREATE_URL, userData)
          .then((response) => {
            console.log('Пользователь успешно создан:', response.data);
            this.cancel();
          })
          .catch((error) => {
            console.error('Ошибка при создании пользователя:', error);
            this.cancel();
          });
    },

    cancel() {
      this.email = '';
      this.surname = '';
      this.name = '';
      this.lastname = '';
      this.password = '';
    }
  }
};
</script>

<style>
@import '@/colors.css';

.cancel {
  background-color: var(--grey-5);
  margin-left: 2%;
}
</style>
