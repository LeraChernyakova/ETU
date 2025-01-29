<template>
  <Navbar />
  <div class="page-layout">
    <div style="flex-direction: column; align-items: center; padding-top: 50px; width: 20%">
      <div>
        <img src="../../../public/logo.png" alt="Plant Shop Logo" class="logo"/>
        <form @submit.prevent="submitFilter">
          <div class="inputs-labels">
            Тип растения
            <input class="inputs" v-model="filter.type" type="text" placeholder="Наименование типа" />
          </div>

          <div class="inputs-labels">Условия освещения</div>
          <label class="checkbox-labels"><input v-model="filter.lightCondition" type="checkbox" value="Тенелюбивые" /> Тенелюбивые</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.lightCondition" type="checkbox" value="Полутеневые" /> Полутеневые</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.lightCondition" type="checkbox" value="Светолюбивые" /> Светолюбивые</label>

          <div class="inputs-labels">Температурный режим</div>
          <label class="checkbox-labels"><input v-model="filter.temperatureRegime" type="checkbox" value="Холодостойкие (до 15°C)" /> Холодостойкие (до 15°C)</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.temperatureRegime" type="checkbox" value="Средний режим (15-22°C)" /> Средний режим (15-22°C)</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.temperatureRegime" type="checkbox" value="Теплолюбивые (более 22°C)" /> Теплолюбивые (более 22°C)</label>

          <div class="inputs-labels">
            Слова в правилах ухода
            <textarea class="inputs" v-model="filter.description" placeholder="Что-то важное для вас"></textarea>
          </div>

          <button type="submit" class="green-button-white-text">Отфильтровать</button>
          <button class="white-button-green-text" @click="isAddOpen = true">Добавить информацию</button>
        </form>
      </div>
    </div>

    <div class="plant-container">
      <div class="search-plants" style="margin-bottom: 1%">
        <input class="search-input" v-model="filter.species" type="text" placeholder="Поиск растений"/>
        <button class="green-button-white-text" id="search-button" @click="submitFilter">Найти</button>
      </div>

      <div class="plant-grid">
        <div v-for="(care, index) in carePlants" :key="index" class="plant-card">
          <div class="plant-content">
            <img v-if="care.image" :src="care.image" alt="Plant Image" class="plant-image" @click="getCare(care.species, care.id)"/>
            <div class="plant-info">
              <div v-if="care.species" class="plant-title">{{ care.species }}</div>
              <div v-if="care.type" class="plant-place">{{ care.type }}</div>
            </div>
          </div>
        </div>
        <div
            v-for="n in (5 - (carePlants.length % 5))"
            v-if="carePlants.length % 5 !== 0"
            class="plant-card placeholder"
        ></div>
      </div>

      <div style="display: flex; position: sticky;">
        <vue-awesome-paginate
            :total-items="careCount"
            :items-per-page="15"
            :max-pages-shown="Math.ceil(careCount / 15)"
            v-model="currentPage"
            @click="getCarePlants"
        />
      </div>
    </div>
  </div>

  <div v-if="isAddOpen" class="modal-overlay" @click="close">
    <div class="trade-modal-content" @click.stop>
      <header class="trade-modal-header">
        <div style="display: flex; justify-content: space-between; width: 100%;">
          <h2 style="font-family: 'Century Gothic', sans-serif; color: black">Информация по уходу</h2>
          <button @click="closeAddModal" class="close-button">X</button>
        </div>
        <div style="margin-top: 2%;">
          <h3 style="font-family: 'Century Gothic', sans-serif; color: black; margin: 0">Заполните основную информацию по уходу</h3>
        </div>
      </header>

      <form @submit.prevent="submitForm">
        <div class="inputs-labels">
          Тип растения
          <input class="inputs" v-model="formData.type" placeholder="Наименование типа" required/>
        </div>

        <div class="inputs-labels">
          Вид растения
          <input class="inputs" v-model="formData.species" type="text" placeholder="Наименование вида" required/>
        </div>

        <div class="inputs-labels">Условия освещения</div>
        <label class="checkbox-labels"><input v-model="formData.lightCondition" type="radio" value="Тенелюбивые" /> Тенелюбивые</label>
        <br>
        <label class="checkbox-labels"><input v-model="formData.lightCondition" type="radio" value="Полутеневые" /> Полутеневые</label>
        <br>
        <label class="checkbox-labels"><input v-model="formData.lightCondition" type="radio" value="Светолюбивые" /> Светолюбивые</label>

        <div class="inputs-labels">Температурный режим</div>
        <label class="checkbox-labels"><input v-model="formData.temperatureRegime" type="radio" value="Холодостойкие (до 15°C)" /> Холодостойкие (до 15°C)</label>
        <br>
        <label class="checkbox-labels"><input v-model="formData.temperatureRegime" type="radio" value="Средний режим (15-22°C)" /> Средний режим (15-22°C)</label>
        <br>
        <label class="checkbox-labels"><input v-model="formData.temperatureRegime" type="radio" value="Теплолюбивые (более 22°C)" /> Теплолюбивые (более 22°C)</label>

        <div class="inputs-labels">
          Описание
          <textarea class="inputs" v-model="formData.descriptionAddition" placeholder="Описание ухода"></textarea>
        </div>

        <div class="inputs-labels">
          Добавлено изображений: {{ formData.image === '' ? 0 : 1 }}
        </div>

        <div style="display: flex; align-items: center; justify-content: flex-end">
          <input
              type="file"
              ref="fileInput"
              @change="addImage"
              style="display: none"
          />
          <button @click="triggerFileInput($event)"  class="white-button-green-text" style="width: 40%; margin-top: 0; margin-right: 1%">Добавить изображение</button>
          <button type="submit" class="green-button-white-text" style="width: 30%">Опубликовать</button>
        </div>
      </form>
    </div>
  </div>

  <div v-if="isCareOpen" class="modal-overlay" @click="close">
    <div class="modal-content-care" @click.stop>
      <header class="care-modal-header">
        <h2>{{ this.curCareSpec }}. Правила ухода.</h2>
        <button @click="closeCareModal" class="close-button">X</button>
      </header>
      <section class="modal-body-care" v-for="(care, index) in currentCare" :key="index">
        <p>{{ care.description }}</p>
        <p class="author">{{ care.author }} {{ formatDate(care.createdAt) }}</p>
        <hr style="margin-top: 10px; border: 1px solid #ccc;" />
      </section>
    </div>
  </div>
</template>

<script>
import Navbar from "@/components/Navbar.vue";
import axios from "axios";
import {VueAwesomePaginate} from "vue-awesome-paginate";
import {ref} from "vue";
const POST_CARE_URL = '/api/care/new';

export default {
  name: "Care",
  components: { VueAwesomePaginate, Navbar },

  data() {
    return {
      carePlants: [],
      isAddOpen: false,
      filter: {
        species: '',
        type: '',
        lightCondition: [],
        temperatureRegime: [],
        description: ''
      },
      currentPage: ref(1),
      careCount: 0,
      formData: {
        type: '',
        species: '',
        image: '',
        temperatureRegime: '',
        descriptionAddition: '',
        lightCondition: ''
      },
      type: '',
      species: '',
      image: '',
      temperatureRegime: '',
      lightCondition: '',
      userId: '',
      currentCare: [],
      curCareSpec: '',
      isCareOpen: false
    };
  },

  mounted() {
    this.getCarePlants();
    this.userId = sessionStorage.getItem("id");
  },

  methods: {
    successAdd() {
      this.$notify({
        title: "Получилось!",
        text: "Описание ухода успешно добавлено.",
        type: 'success'
      });
    },

    errorAdd() {
      this.$notify({
        title: "Ошибка!",
        text: "Произошла ошибка при добавлении описания ухода. Попробуйте снова.",
        type: 'error'
      });
    },

    closeCareModal() {
      this.isCareOpen = false;
    },

    submitForm() {
      this.postCare();
    },

    closeAddModal() {
      this.isAddOpen = false;
      this.clearForm();
    },

    clearForm() {
      this.formData.lightCondition = '';
      this.formData.type = '';
      this.formData.species = '';
      this.formData.image = '';
      this.formData.temperatureRegime = '';
      this.formData.descriptionAddition = ''
    },

    submitFilter() {
      this.currentPage = ref(1);
      this.getCarePlants();
    },

    async getCarePlants() {
      this.carePlants = [];

      const careFilter = {
        filter: {
          species: this.filter.species,
          type: this.filter.type,
          lightCondition: this.filter.lightCondition,
          temperatureRegime: this.filter.temperatureRegime,
          description: this.filter.description
        }
      }

      axios
          .post(`/api/care/${this.currentPage}/15`, careFilter)
          .then((response) => {
            response.data.plants.forEach(elem => {
              let plant = {
                image: elem.image,
                species: elem.species,
                id: elem.ruleId,
                type: elem.type
              };
              this.carePlants.push(plant)
            })
            this.careCount = parseInt(response.data.count);
          });
    },

    triggerFileInput(event) {
      event.preventDefault();
      this.$refs.fileInput.click();
    },

    addImage(event) {
      const file = event.target.files[0];
      if (file) {
        const reader = new FileReader();
        reader.onload = (e) => {
          this.formData.image = e.target.result;
        };
        reader.readAsDataURL(file);
      }
    },

    async postCare() {
      const careData = {
        species: this.formData.species,
        descriptionAddition: this.formData.descriptionAddition,
        type: this.formData.type,
        lightCondition: this.formData.lightCondition,
        temperatureRegime: this.formData.temperatureRegime,
        image: this.formData.image,
        userId: this.userId
      }
      try {
        await axios.post(POST_CARE_URL, careData);
        this.successAdd();
        this.closeAddModal();
        await this.getCarePlants();
      } catch (error) {
        this.errorAdd();
      }
    },

    async getCare(species, id) {
      this.currentCare = [];
      this.curCareSpec = species;
      axios
          .get(`/api/care/${id}`)
          .then((response) => {
            response.data.careRules.forEach(elem => {
              const str1 = elem.user.userSurname;
              const str2 = elem.user.userName;
              const str3 = elem.user.userFatherName;
              const result = `${str1} ${str2} ${str3}`;
              let care = {
                description: elem.description,
                createdAt: elem.createdAt,
                author: result
              };
              this.currentCare.push(care)
            })
          })
      this.isCareOpen = true;
    },

    formatDate(dateString) {
      const date = new Date(dateString);
      const options = {
        day: '2-digit',
        month: '2-digit',
        year: 'numeric',
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit',
      };
      const formattedDate = date.toLocaleString('ru-RU', options);
      return formattedDate.replace(',', ' в');
    }
  }
}
</script>

<style>
@import "../../../main.css";
@import "../../../plants.css";
@import "../../../modal.css";

#search-button {
  margin-left: 1%;
  width: 8%;
}

.author {
  color: #666;
  font-size: 0.9em;
  margin-top: 15px;
  text-align: right;
}

.care-modal-header {
  display: flex;
  justify-content: space-between;
  align-items: flex-start;
  border-bottom: 1px solid #ccc;
  padding-bottom: 10px;
  margin-bottom: 10px;
}

.trade-modal-header {
  display: flex;
  justify-content: space-between;
  align-items: flex-start;
  border-bottom: 1px solid #ccc;
  padding-bottom: 10px;
  margin-bottom: 10px;
  flex-direction: column;
}

.trade-modal-header h2 {
  font-size: 1.5em;
  margin: 0;
}

.trade-modal-content {
  background: #fff;
  width: 60%;
  max-width: 500px;
  padding: 20px;
  border-radius: 8px;
  position: relative;
}

.modal-body p {
  margin: 1px 0;
  line-height: 1.2;
  font-size: 14px;
  color: black;
}
</style>
