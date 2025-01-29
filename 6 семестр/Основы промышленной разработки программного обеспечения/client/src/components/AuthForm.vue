<template>
  <div ref="containerRef" class="auth-container" :style="{ width: width }">
    <div class="content">
      <p class="title"> {{ title }} </p>
      <v-container class="content-input">
        <slot></slot>
      </v-container>
    </div>
  </div>
</template>

<script>
export default {
  name: 'AuthForm',
  props: ['title', 'width'],
  mounted() {
    this.setContainerHeight();
  },
  methods: {
    setContainerHeight() {
      const container = this.$refs.containerRef;
      const contentHeight = container.querySelector('.content').offsetHeight;
      container.style.height = contentHeight + 'px';
    }
  }
}
</script>

<style>
@import '@/colors.css';

.auth-container {
  margin: auto;
  padding: 0;
  position: absolute;
  top: 0; left: 0; bottom: 0; right: 0;
  border-radius: 5px;
  background-color: var(--white-1);
  box-shadow: 0 1px 2px 0 rgba(117, 106, 106, 0.5);
}

.title {
  border-radius: 5px 5px 0 0;
  text-align: center;
  background-color: var(--orange-1);
  padding: 2%;
  font-family: Inter, sans-serif;
  font-size: 24px;
  font-weight: 300;
  color: var(--grey-4);
  margin-bottom: 5%;
}

.content-input {
  background-color: var(--white-1);
}
</style>