<template>
  <AuthForm
      :title="title"
      :width="containerWidth"
  >
    <DataForm fast-fail @submit.prevent="signIn">
      <DataInput
          v-model="email"
          label="Почта"
          :rules="emailRules"
          id="email-input"
      ></DataInput>
      <DataInput
          :append-inner-icon="show1 ? 'mdi-eye' : 'mdi-eye-off'"
          v-model="password"
          label="Пароль"
          :type="show1 ? 'text' : 'password'"
          @click:append-inner="show1 = !show1"
          :rules="passwordRules"
          id="password-input">
      </DataInput>
      <p class="problems">В случае проблем пишите на admin@mail.ru</p>
      <DataButton id="sign-in-button" title='вход'></DataButton>
    </DataForm>
  </AuthForm>
</template>

<script>
import DataInput from "@/components/Data/DataInput.vue";
import DataForm from "@/components/Data/DataForm.vue";
import DataButton from "@/components/Data/DataButton.vue";
import AuthForm from "@/components/AuthForm.vue";

import axios from 'axios';

const SIGN_IN_URL = '/api/auth/sign-in'

export default {
  name: "Authorization",
  components: {AuthForm, DataButton, DataForm, DataInput},

  data() {
    return {
      title: 'e.moevm statistics',
      containerWidth: '31%',
      email: '',
      password: '',
      show1: false,
      emailRules: [
        value => {
          if (value.length === 0)
            return 'Данное поле обязательно для заполнения'
          if (/^[a-z0-9.-]+@[a-z.-]+\.[a-z]+$/i.test(value)) return true
          else return 'Введен неккоректный адрес почты'
        },
      ],
      passwordRules: [
        value => {
          if (value) return true
          return 'Данное поле обязательно для заполнения.'
        },
      ],
    };
  },

  beforeMount() {
    window.sessionStorage.clear();
  },

  methods: {
    async signIn() {
      const userData = {
        email: this.email,
        password: this.password
      };

      try {
        const response = await axios.post(SIGN_IN_URL, userData);
        console.log('Вход в систему выполнен успешно!', response.data);
        const userName = `${response.data.name} ${response.data.surname}`;
        sessionStorage.setItem("name", userName);
        sessionStorage.setItem("position", response.data.position);
        this.$router.push('/e.moevm.statistics/statistics');
      } catch (error) {
        const errorCode = error.message;
        const errorDetail = error.response.data.detail || error.response.data.message;
        const errorAlert = `${errorCode}. ${errorDetail}`
        alert(errorAlert);
        console.error('Ошибка при входе в систему.', error);
      }
    }
  }
};
</script>

<style>
@import '@/colors.css';

.problems {
  font-family: Inter, sans-serif;
  font-size: 14px;
  font-weight: 300;
  color: var(--blue-3);
  padding-bottom: 3%;
  padding-top: 0;
  text-align: center;
  background-color: var(--white-1);
}
</style>