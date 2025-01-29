<template>
  <v-container class="filters">
    <slot></slot>
  </v-container>
</template>

<script>
export default {
  name: 'Filters'
};
</script>

<style>
@import '@/colors.css';
.filters {
  max-width: 95%;
  padding-left: 0;
  padding-right: 0;
  justify-self: center;
  display: flex;
  align-items: center;
  justify-content: space-between;
}
</style>
