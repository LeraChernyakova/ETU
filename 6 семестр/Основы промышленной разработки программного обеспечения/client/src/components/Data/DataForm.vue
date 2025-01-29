<template>
  <v-form class="custom-form">
    <slot></slot>
  </v-form>
</template>

<script>
export default {
  name: 'DataForm',
};
</script>

<style>
@import '@/colors.css';

.custom-form {
  text-align: center;
  background-color: var(--white-1);
}
</style>