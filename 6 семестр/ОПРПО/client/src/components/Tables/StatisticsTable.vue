<template>
  <v-data-table
    class="custom-table"
    :headers="headers"
    :items="info"
    item-value="number"
    outlined
    v-model="selected"
    show-select
  >

    <template v-slot:[`item.FIO`]="{ item }">
      <p align="start">{{ item.FIO }}</p>
    </template>

    <template v-slot:[`item.course`]="{ item }">
      <p align="start">{{ item.course }}</p>
    </template>
  </v-data-table>
</template>

<script>
export default {
  name: "StatisticsTable",
  props: {
    info: {
      type: Array,
      required: true,
    },
  },
  data() {
    return {
      selected: [],
      selectedRows: [],
      headers: [
        { title: "ID", key: "studentId", sortable: false, align: "center" },
        { title: "ФИО", key: "FIO", sortable: false, align: "center" },
        { title: "Почта", key: "email", sortable: false, align: "center" },
        { title: "Дата", key: "date", sortable: false, align: "center" },
        { title: "Время", key: "time", sortable: false, align: "center" },
        { title: "Название курса", key: "course", sortable: false, align: "center"},
        { title: "Тип действия", key: "typeAction", sortable: false, align: "center" },
        { title: "Тип события", key: "eventType", sortable: false, align: "center" },
        { title: "Тип элемента", key: "elementType", sortable: false, align: "center" },
        { title: "Название элемента", key: "elementName", sortable: false, align: "center" },
      ],
    };
  }
};
</script>

<style>
.custom-table {
  width: 96%;
  margin: 0 auto;
}

.custom-table tbody tr:nth-child(odd) {
  background-color: var(--white-3);
}

.custom-table tbody tr {
  font-family: Inter, sans-serif;
  font-size: 14px;
}

.v-data-table .v-data-table-header th {
  font-weight: bolder !important;
  font-family: Inter, sans-serif;
}

.custom-table th,
.custom-table td {
  border: 1px solid var(--white-2);
}

.custom-table,
.v-table > .v-table__wrapper > table > tbody > tr > td,
.v-table > .v-table__wrapper > table > tbody > tr > th,
.v-table > .v-table__wrapper > table > tfoot > tr > td,
.v-table > .v-table__wrapper > table > tfoot > tr > th,
.v-table > .v-table__wrapper > table > thead > tr > td,
.v-table > .v-table__wrapper > table > thead > tr > th {
  padding: 0 8px;
}

#action {
  white-space: pre-line;
}
</style>