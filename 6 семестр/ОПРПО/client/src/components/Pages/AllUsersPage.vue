<template>
  <Navbar :username="name" :position="position">
    <UsersTable :info="usersInfo" :get-users="getUsers"></UsersTable>
  </Navbar>
</template>

<script>
import Navbar from "@/components/Navbar.vue";
import axios from "axios";
import UsersTable from "@/components/Tables/UsersTable.vue";

const USERS_URL = "/api/user/";

export default {
  name: "AllUsers",
  components: {UsersTable, Navbar },

  data() {
    return {
      usersInfo: [],
      name: '',
      position: ''
    };
  },
  beforeMount() {
    let name = sessionStorage.getItem("name");
    if (name) {
      this.name = name;
      const position = sessionStorage.getItem("position");
      if (position === "regular") {
        const error = 'Request failed. You dont have enough rights to perform the action!'
        alert(error)
        console.log("Недостаточно прав");
        this.$router.push("/e.moevm.statistics/statistics");
      }
      else {
        this.position = sessionStorage.getItem("position");
      }
    } else {
      const error = 'Request failed with status code 401. You are not sign in!'
      alert(error)
      console.log("Не авторизован");
      this.$router.push("/e.moevm.statistics/auth");
    }
  },
  mounted() {
    this.getUsers();
  },
  methods: {
    getUsers() {
      this.usersInfo = [];

      axios
          .get(USERS_URL)
          .then((response) => {
            response.data.forEach(element => {
              const FIO = `${element.surname} ${element.name} ${element.lastname}`;
              const position = element.position === "admin" ? "администратор" : "пользователь";
              let user = {
                id: element.id,
                FIO: FIO,
                email: element.email,
                position: position,
                password: element.password,
                actions: ''
              };
              this.usersInfo.push(user);
            });
          })
          .catch((error) => {
            alert("Ошибка при получении данных");
            console.error("Ошибка при получении данных:", error);
          });
    }
  }
};
</script>

<style>
</style>
