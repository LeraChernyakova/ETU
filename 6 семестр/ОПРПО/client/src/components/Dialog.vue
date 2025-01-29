<template>
  <v-dialog width="auto">
    <v-card text="Выберите файлы, которые вы хотите скачать:" title="Скачать">
      <v-container>
        <v-checkbox
          v-model="selected"
          label="Выбранная статистика в формате json"
          value="statistics"
        ></v-checkbox>
        <v-checkbox
          v-model="selected"
          label="Html-код страниц в формате json"
          value="pages"
        ></v-checkbox>
      </v-container>
      <template v-slot:actions>
        <v-btn class="ms-auto" text="Отмена" @click="$emit('close')"></v-btn>
        <v-btn
          color="primary"
          variant="tonal"
          text="Скачать"
          @click="download"
          :disabled="!selected.length"
        ></v-btn>
      </template>
    </v-card>
  </v-dialog>
</template>

<script>
import axios from "axios";
const STAT_FILE_URL = "/api/download/statistics/";
const HTMLPAGE_FILE_URL = "/api/download/sessions/";

export default {
  emits: ["close"],
  name: "Dialog",
  props: ["params"],
  data() {
    return {
      selected: ["statistics"],
    };
  },
  methods: {
    getUrl(file){
      if (file === "statistics") return STAT_FILE_URL
      return HTMLPAGE_FILE_URL
    },
    download() {
      for (let file of this.selected){
        axios
          .get(this.getUrl(file), {params: this.params})
          .then((response) => {
            const blob = new Blob([JSON.stringify(response.data)], { type: "text/json" });
            const link = document.createElement("a");
            link.href = URL.createObjectURL(blob);
            link.download = `${file}.json`;
            link.click();
            URL.revokeObjectURL(link.href);
          })
          .catch(console.error);
      }
      this.$emit("close");
    },
  },
};
</script>

<style scoped>
@import "@/colors.css";
</style>
