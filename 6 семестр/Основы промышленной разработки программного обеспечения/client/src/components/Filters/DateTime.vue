<template>
  <v-text-field
      type="datetime-local"
      density="compact"
      class="date-time-filter"
      @keydown.prevent
  ></v-text-field>
</template>

<style>
.date-time-filter {
  transform: translateY(25%);
  color: transparent;
}

.date-time-filter .v-field {
  border-radius: 7px;
  border: 1px solid var(--grey-6);
}

.date-time-filter .v-field__overlay {
  background-color: white;
  color: var(--grey-4);
}

.date-time-filter .v-field-label {
  font-size: 16px;
  font-family: Inter, sans-serif;
  font-weight: 400;
  color: var(--grey-4);
}

.date-time-filter .v-field__input {
  font-size: 16px;
  font-family: Inter, sans-serif;
  font-weight: 400;
  color: var(--grey-4);
}
</style>
