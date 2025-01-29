<template>
  <Navbar />
  <div class="page-layout">
    <div class="sidebar">
      <div class="side-form">
        <img src="../../../public/logo.png" alt="Plant Shop Logo" class="logo"/>
        <div class="inputs-labels" id="create-ads">
          Создать объявление
        </div>
        <form @submit.prevent="submitForm">
          <div class="inputs-labels">
            Тип растения
            <input class="inputs" v-model="formData.type" placeholder="Наименование типа" required/>
          </div>

          <div class="inputs-labels">
            Вид растения
            <input class="inputs" v-model="formData.species" type="text" placeholder="Наименование вида" required/>
          </div>

          <div class="inputs-labels">Размер</div>
          <label class="checkbox-labels"><input v-model="formData.size" type="radio" value="Маленькие (до 20 см)" /> Маленькие (до 20 см)</label>
          <br>
          <label class="checkbox-labels"><input v-model="formData.size" type="radio" value="Средние (от 20 до 50 см)" /> Средние (от 20 до 50 см)</label>
          <br>
          <label class="checkbox-labels"><input v-model="formData.size" type="radio" value="Большие (более 50 см)" /> Большие (более 50 см)</label>

          <div class="inputs-labels">Условия освещения</div>
          <label class="checkbox-labels"><input v-model="formData.lighting" type="radio" value="Тенелюбивые" /> Тенелюбивые</label>
          <br>
          <label class="checkbox-labels"><input v-model="formData.lighting" type="radio" value="Полутеневые" /> Полутеневые</label>
          <br>
          <label class="checkbox-labels"><input v-model="formData.lighting" type="radio" value="Светолюбивые" /> Светолюбивые</label>

          <div class="inputs-labels">Частота полива</div>
          <label class="checkbox-labels"><input v-model="formData.wateringFrequency" type="radio" value="Редкий полив (раз в 2 недели)" /> Редкий полив (раз в 2 недели)</label>
          <br>
          <label class="checkbox-labels"><input v-model="formData.wateringFrequency" type="radio" value="Средний полив (1-2 раза в неделю)" /> Средний полив (1-2 раза в неделю)</label>
          <br>
          <label class="checkbox-labels"><input v-model="formData.wateringFrequency" type="radio" value="Частый полив (ежедневно)" /> Частый полив (ежедневно)</label>

          <div class="inputs-labels">Температурный режим</div>
          <label class="checkbox-labels"><input v-model="formData.temperature" type="radio" value="Холодостойкие (до 15°C)" /> Холодостойкие (до 15°C)</label>
          <br>
          <label class="checkbox-labels"><input v-model="formData.temperature" type="radio" value="Средний режим (15-22°C)" /> Средний режим (15-22°C)</label>
          <br>
          <label class="checkbox-labels"><input v-model="formData.temperature" type="radio" value="Теплолюбивые (более 22°C)" /> Теплолюбивые (более 22°C)</label>

          <div class="inputs-labels">Сложность ухода</div>
          <label class="checkbox-labels"><input v-model="formData.careLevel" type="radio" value="Для начинающих" /> Для начинающих</label>
          <br>
          <label class="checkbox-labels"><input v-model="formData.careLevel" type="radio" value="Требует среднего ухода" /> Требует среднего ухода</label>
          <br>
          <label class="checkbox-labels"><input v-model="formData.careLevel" type="radio" value="Для опытных цветоводов" /> Для опытных цветоводов</label>
          <br>

          <div class="inputs-labels">
            Описание
            <textarea class="inputs" v-model="formData.description" placeholder="Введите описание"></textarea>
          </div>

          <div class="inputs-labels">
            Город
            <input class="inputs" v-model="formData.city" type="text" placeholder="Введите город" required/>
          </div>

          <div class="inputs-labels">
            Цена, Р
            <input class="inputs" v-model="formData.price" type="number" placeholder="Введите цену" required/>
          </div>

          <div class="inputs-labels">
            Добавлено изображений: {{ formData.image === '' ? 0 : 1 }}
          </div>

          <input
              type="file"
              ref="fileInput"
              @change="addImage"
              style="display: none"
          />
          <button @click="triggerFileInput($event)"  class="white-button-green-text" style="margin-bottom: 2%">Добавить изображение</button>
          <button type="submit" class="green-button-white-text">Опубликовать</button>
        </form>
      </div>
    </div>

    <div class="plant-container">
      <header class="modal-header-ads">
        <h1 style="font-family: Century Gothic,sans-serif; margin: 0">Мои объявления</h1>
        <div style="margin-top: 1%;">
          <span
              :style="{ color: selected === 'active' ? '#000000' : '#7E7E7E', fontWeight: 'bold', fontSize: '14px', fontFamily: 'Century Gothic,sans-serif'}"
              @click="select('active')"
              class="clickable">
          Активные
        </span>
          <span
              :style="{ color: selected === 'archive' ? '#000000' : '#7E7E7E', fontWeight: 'bold', fontSize: '14px', fontFamily: 'Century Gothic,sans-serif' }"
              @click="select('archive')"
              class="clickable">
          Архивные
        </span>
        </div>
      </header>

      <div class="plant-grid">
        <div v-for="plant in plants" class="plant-card">
          <div class="plant-content">
            <img v-if="plant.image" :src="plant.image" alt="Plant Image" class="plant-image" />
            <div class="plant-info">
              <div v-if="plant.species" class="plant-title">{{ plant.species }}</div>
              <div v-if="plant.price" class="plant-price">{{ formatPrice(plant.price) }}</div>
              <div v-if="plant.place" class="plant-place">{{ plant.place }}</div>
              <div v-if="plant.createdAt" class="plant-date">{{ formatDate(plant.createdAt) }}</div>
            </div>
          </div>
        </div>
        <div
            v-for="n in (5 - (plants.length % 5))"
            v-if="plants.length % 5 !== 0"
            class="plant-card placeholder"
        ></div>
      </div>
    </div>
  </div>
</template>

<script>
import Navbar from "@/components/Navbar.vue";
import axios from "axios";

const NEW_PLANT_URL = '/api/plants/add';

export default {
  name: "Ads",
  components: { Navbar },

  data() {
    return {
      plants: [],
      selected: 'active',
      formData: {
        type: '',
        species: '',
        size: '',
        lighting: '',
        wateringFrequency: '',
        temperature: '',
        careLevel: '',
        description: '',
        city: '',
        price: null,
        image: '',
      },
      userId: ''
    };
  },

  mounted() {
    this.userId = sessionStorage.getItem("id");
    this.getActivePlants();
  },

  methods: {
    async getActivePlants() {
      this.plants = [];
      axios
          .get(`/api/plants/active/${this.userId}`)
          .then((response) => {
            response.data.plants.forEach(elem => {
              let plant = {
                image: elem.image,
                species: elem.species,
                price: elem.price,
                createdAt: elem.createdAt,
                place: elem.place
              };
              this.plants.push(plant)
            })
          })
    },

    async getArchivePlants() {
      this.plants = [];
      axios
          .get(`/api/plants/archive/${this.userId}`)
          .then((response) => {
            response.data.plants.forEach(elem => {
              let plant = {
                image: elem.image,
                species: elem.species,
                price: elem.price,
                createdAt: elem.createdAt,
                place: elem.place
              };
              this.plants.push(plant)
            })
          })
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

    successAddPlant() {
      this.$notify({
        title: "Получилось!",
        text: "Объявление успешно добавлено.",
        type: 'success'
      });
    },

    errorAddPlant() {
      this.$notify({
        title: "Ошибка!",
        text: "Произошла ошибка при добавлении объявления. Попробуйте снова.",
        type: 'error'
      });
    },

    submitForm() {
      this.createPlant();
    },

    async createPlant() {
      const plantData = {
        image: this.formData.image,
        place: this.formData.city,
        size: this.formData.size,
        price: this.formData.price,
        lightCondition: this.formData.lighting,
        wateringFrequency: this.formData.wateringFrequency,
        temperatureRegime: this.formData.temperature,
        careComplexity: this.formData.careLevel,
        description: this.formData.description,
        type: this.formData.type,
        species: this.formData.species,
        userId: this.userId
      };

      try {
        await axios.post(NEW_PLANT_URL, plantData);
        this.successAddPlant();
        this.clearForm();
        if (this.selected === "active") {
          await this.getActivePlants();
        } else {
          await this.getArchivePlants();
        }
      } catch (error) {
        this.errorAddPlant();
      }
    },

    clearForm() {
      this.formData.city = '';
      this.formData.size = '';
      this.formData.price = '';
      this.formData.lighting = '';
      this.formData.wateringFrequency = '';
      this.formData.temperature = '';
      this.formData.careLevel = '';
      this.formData.description = '';
      this.formData.type = '';
      this.formData.species = '';
      this.formData.image = ''
    },

    select(type) {
      this.selected = type;
      if (this.selected === 'active') {
        this.getActivePlants();
      } else {
        this.getArchivePlants();
      }
    },

    formatDate(date) {
      return new Date(date).toLocaleDateString("ru-RU", {
        year: 'numeric',
        month: 'long',
        day: 'numeric'
      });
    },

    formatPrice(price) {
      return `${price} ₽`;
    }
  }
}
</script>

<style scoped>
@import "../../../main.css";
@import "../../../plants.css";

.page-layout {
  display: flex;
}

#create-ads {
  color: #89A758;
}

.modal-header-ads {
  display: grid;
  align-items: center;
  border-bottom: 1px solid #ccc;
  padding-bottom: 10px;
  margin-bottom: 10px;
}
</style>