<template>
  <router-view/>
  <notifications position="bottom right" width="20%"/>
</template>

<script>
export default {
  name: 'App',
  data: () => ({}),
}
</script>

<style>
.vue-notification {
  font-family: 'Century Gothic', sans-serif;
  font-size: 13px;
  font-weight: 400;
  padding: 15px;
  border-radius: 5px;
  box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
}
</style>
