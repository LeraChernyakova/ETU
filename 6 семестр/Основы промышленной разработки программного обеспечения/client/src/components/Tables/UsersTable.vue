<template>
  <v-data-table
      class="custom-table-users"
      :headers="headers"
      :items="info"
      outlined
  >

    <template v-slot:[`item.actions`]="{ item }">
      <v-container v-if="item['position'] !== 'администратор'">
        <v-icon>mdi-pencil</v-icon>
        <v-icon :id="`delete-item-${item['email'].replace(/[^a-zA-Z0-9]/g, '_')}`" @click="deleteItem(item)">mdi-delete</v-icon>
      </v-container>
      <v-container v-else>
        <v-icon>mdi-pencil</v-icon>
      </v-container>
    </template>

  </v-data-table>
</template>

<script>
import axios from "axios";

export default {
  name: "UsersTable",
  props: {
    info: {
      type: Array,
      required: true,
    },
    getUsers: {
      type: Function,
      required: true
    }
  },
  data() {
    return {
      headers: [
        { title: "ФИО", key: "FIO", sortable: false, align: "center" },
        { title: "Почта", key: "email", sortable: false, align: "center" },
        { title: "Роль", key: "position", sortable: false, align: "center" },
        { title: "Действия", key: "actions", sortable: false, align: "center" },
      ]
    };
  },
  methods: {
    deleteItem(item) {
      let answer = confirm(`Пользователь ${item.FIO} будет безвозвратно удален. Вы уверены, что хотите продолжить операцию?`)
      if (answer){
        const userId = item.id;
        const DEl_USER_URL = `/api/user/${userId}`
        axios
            .delete(DEl_USER_URL)
            .then(() => {
              this.getUsers();
            })
            .catch((error) => {
              alert("Ошибка при удалении пользователя");
              console.error("Ошибка при удалении пользователя:", error);
            });
      }
    }
  }
};
</script>

<style>
.custom-table-users {
  width: 80%;
  margin: 2% auto;
}

.custom-table-users  tbody tr:nth-child(odd) {
  background-color: var(--white-3);
}

.custom-table-users  tbody tr {
  font-family: Inter, sans-serif;
  font-size: 15px;
}

.custom-table-users .v-data-table-header th {
  font-weight: bolder !important;
  font-family: Inter, sans-serif;
}

.custom-table-users  th,
.custom-table-users td {
  border: 1px solid var(--white-2);
}

.custom-table-users .v-icon {
  color: var(--grey-7);
}

.custom-table-users .v-icon + .v-icon {
  margin-left: 10px;
}

#action {
  white-space: pre-line;
}
</style>