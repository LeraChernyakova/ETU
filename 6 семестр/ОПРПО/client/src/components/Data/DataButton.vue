<template>
  <v-btn class="button-custom" type="submit">{{ title }}</v-btn>
</template>

<script>
export default {
  name: 'DataButton',
  props: ['title']
};
</script>

<style>
@import '@/colors.css';

v-btn{
  background-color: var(--white-1);
}

.button-custom {
  font-family: Inter, sans-serif;
  font-size: 14px;
  font-weight: 300;
  width: 37%;
  color: var(--white-1);
  background-color: var(--blue-1);
  letter-spacing: -0.3px;
  border-radius: 5px;
  align-self: center;
}
</style>
