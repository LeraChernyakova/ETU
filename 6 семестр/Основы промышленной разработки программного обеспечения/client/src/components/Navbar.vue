<template>
  <v-app>
    <v-app-bar app color="white accent-4" dark ref="appBar">
      <v-menu rounded="0">
        <template v-slot:activator="{ props }">
          <v-btn icon="mdi-menu" class="menu" v-bind="props"></v-btn>
        </template>
        <v-list v-if="position === 'admin'" rounded="0">
          <v-list-item
              class="custom-list-item"
              v-for="(item, i) in adminItems"
              :key="i"
              @click="navigateTo(item.path)"
          >
            <v-list-item-title>{{ item.title }}</v-list-item-title>
          </v-list-item>
        </v-list>
        <v-list v-if="position === 'regular'" rounded="0">
          <v-list-item
              class="custom-list-item"
              v-for="(item, i) in regularItems"
              :key="i"
              @click="navigateTo(item.path)"
          >
            <v-list-item-title>{{ item.title }}</v-list-item-title>
          </v-list-item>
        </v-list>
      </v-menu>
      <v-img src="/moevm.jpg" alt="Image Description" max-width="55px" max-height="50px"></v-img>
      <v-toolbar-title class="site-title">moevm statistics</v-toolbar-title>
      <v-spacer></v-spacer>
      <span class="custom-text">{{ username }}</span>
      <v-icon size="36" class="user">mdi-account-circle</v-icon>
    </v-app-bar>
    <div class="container" :style="{ marginTop: appBarHeight }">
      <slot></slot>
    </div>
  </v-app>
</template>

<script>
export default {
  name: 'Navbar',
  props: ['username', 'position'],
  data() {
    return {
      adminItems: [
        { title: "Просмотр статистики", path: '/e.moevm.statistics/statistics' },
        { title: "Добавить пользователя", path: '/e.moevm.statistics/user' },
        { title: "Просмотр пользователей", path: '/e.moevm.statistics/all-users'},
        { title: "Выход", path: '/e.moevm.statistics/auth' },
      ],
      regularItems: [
        { title: "Выход", path: '/e.moevm.statistics/auth' }
      ],
      appBarHeight: 0
    };
  },
  mounted() {
    this.appBarHeight = this.$refs.appBar.$el.clientHeight + 'px';
  },
  methods: {
    navigateTo(path) {
      this.$router.push(path);
    }
  }
}
</script>

<style scoped>
@import '@/colors.css';
.menu {
  color: var(--blue-2);
  border-radius: 0 !important;
}
.custom-list-item {
  font-family: Inter, sans-serif;
  font-size: 20px;
  color: var(--black-1);
  font-weight: 400;
  border-radius: 0;
}
.site-title {
  font-family: Inter, sans-serif;
  font-size: 23px;
  color: var(--blue-2);
  font-weight: 300;
}
.custom-text {
  font-family: Inter, sans-serif;
  font-size: 19px;
  color: var(--black-1);
  font-weight: 300;
}
.user {
  color: var(--grey-2);
  margin: 10px;
}
</style>
