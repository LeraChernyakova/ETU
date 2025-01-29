<template>
  <Navbar />
  <div class="page-layout">
    <div class="sidebar">
      <div class="side-form">
        <img src="../../../public/logo.png" alt="Plant Shop Logo" class="logo"/>
        <form @submit.prevent="submitForm">
          <div class="inputs-labels">
            Тип растения
            <input class="inputs" v-model="filter.type" placeholder="Наименование типа" />
          </div>

          <div class="inputs-labels">Размер</div>
          <label class="checkbox-labels"><input v-model="filter.size" type="checkbox" value="Маленькие (до 20 см)" /> Маленькие (до 20 см)</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.size" type="checkbox" value="Средние (от 20 до 50 см)" /> Средние (от 20 до 50 см)</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.size" type="checkbox" value="Большие (более 50 см)" /> Большие (более 50 см)</label>

          <div class="inputs-labels">Условия освещения</div>
          <label class="checkbox-labels"><input v-model="filter.lighting" type="checkbox" value="Тенелюбивые" /> Тенелюбивые</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.lighting" type="checkbox" value="Полутеневые" /> Полутеневые</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.lighting" type="checkbox" value="Светолюбивые" /> Светолюбивые</label>

          <div class="inputs-labels">Частота полива</div>
          <label class="checkbox-labels"><input v-model="filter.wateringFrequency" type="checkbox" value="Редкий полив (раз в 2 недели)" /> Редкий полив (раз в 2 недели)</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.wateringFrequency" type="checkbox" value="Средний полив (1-2 раза в неделю)" /> Средний полив (1-2 раза в неделю)</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.wateringFrequency" type="checkbox" value="Частый полив (ежедневно)" /> Частый полив (ежедневно)</label>

          <div class="inputs-labels">Температурный режим</div>
          <label class="checkbox-labels"><input v-model="filter.temperature" type="checkbox" value="Холодостойкие (до 15°C)" /> Холодостойкие (до 15°C)</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.temperature" type="checkbox" value="Средний режим (15-22°C)" /> Средний режим (15-22°C)</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.temperature" type="checkbox" value="Теплолюбивые (более 22°C)" /> Теплолюбивые (более 22°C)</label>

          <div class="inputs-labels">Сложность ухода</div>
          <label class="checkbox-labels"><input v-model="filter.careLevel" type="checkbox" value="Для начинающих" /> Для начинающих</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.careLevel" type="checkbox" value="Требует среднего ухода" /> Требует среднего ухода</label>
          <br>
          <label class="checkbox-labels"><input v-model="filter.careLevel" type="checkbox" value="Для опытных цветоводов" /> Для опытных цветоводов</label>
          <br>

          <div class="inputs-labels">
            Слова в описании
            <textarea class="inputs" v-model="filter.description" placeholder="Что-то важное для вас"></textarea>
          </div>

          <div class="inputs-labels">
            Город
            <input class="inputs" v-model="filter.place" type="text" placeholder="Введите город" />
          </div>

          <div class="inputs-labels">
            Цена, Р
            <div style="display: flex; justify-content: space-between">
              <input class="inputs" style="margin-right: 2%" v-model="filter.priceFrom" type="number" placeholder="От" />
              <input class="inputs" v-model="filter.priceTo" type="number" placeholder="До" />
            </div>
          </div>

          <button type="submit" style="margin-top: 2%" class="green-button-white-text">Показать объявления</button>
        </form>
      </div>
    </div>

    <div class="plant-container">
      <div class="search-plants">
        <input class="search-input" v-model="filter.species" type="text" placeholder="Поиск по объявлениям"/>
        <button class="green-button-white-text" id="search-button" @click="submitForm">Найти</button>
      </div>

      <div class="select-sort">
        <select class="custom-select" v-model="sort_type" @change="getPlants">
          <option disabled value="">Сортировка</option>
          <option value="">По умолчанию</option>
          <option value="cheap">Дешевле</option>
          <option value="expensive">Дороже</option>
          <option value="date">По дате</option>
        </select>
      </div>

      <div class="plant-grid">
        <div v-for="plant in plants" class="plant-card">
          <div class="plant-content">
            <img @click="navigate(plant.id, plant.species)" v-if="plant.image" :src="plant.image" alt="Plant Image" class="plant-image" />
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
      <div style="display: flex; position: sticky;">
        <vue-awesome-paginate
            :total-items="plantsCount"
            :items-per-page="15"
            :max-pages-shown="Math.ceil(plantsCount / 15)"
            v-model="currentPage"
            @click="getPlants"
        />
      </div>
    </div>
  </div>
</template>

<script>
import Navbar from "@/components/Navbar.vue";
import axios from "axios";
import {VueAwesomePaginate} from "vue-awesome-paginate";
import {ref} from "vue";

export default {
  name: "AllPlants",
  components: {VueAwesomePaginate, Navbar },

  data() {
    return {
      currentPage: ref(1),
      plants: [],
      filter: {
        type: '',
        species: '',
        size: [],
        lighting: [],
        wateringFrequency: [],
        temperature: [],
        careLevel: [],
        description: '',
        place: '',
        priceFrom: null,
        priceTo: null,
      },
      sort_type: '',
      sort: '',
      isDesc: true,
      userId: '',
      plantsCount: 0
    };
  },

  mounted() {
    this.userId = sessionStorage.getItem("id");
    if (sessionStorage.getItem("search")) {
      this.filter.species = sessionStorage.getItem("search");
      sessionStorage.removeItem("search");
    }
    this.getPlants();
  },

  methods: {
    normalizePrice(price) {
      return price !== null ? price : 0;
    },

    async getPlants() {
      this.plants = [];

      if (this.sort_type === "cheap") {
        this.sort = "price";
        this.isDesc = false;
      } else if (this.sort_type === "expensive") {
        this.sort = "price";
        this.isDesc = true;
      } else if (this.sort_type === "date") {
        this.sort = "created_at";
        this.isDesc = true;
      } else {
        this.sort = "";
      }

      const plantData = {
        isDesc: this.isDesc,
        filter: {
          place: this.filter.place,
          size: this.filter.size,
          priceFrom: this.normalizePrice(this.filter.priceFrom),
          priceTo: this.normalizePrice(this.filter.priceTo),
          lightCondition: this.filter.lighting,
          wateringFrequency: this.filter.wateringFrequency,
          temperatureRegime: this.filter.temperature,
          careComplexity: this.filter.careLevel,
          description: this.filter.description,
          type: this.filter.type,
          species: this.filter.species,
        },
        userId: this.userId
      };

      axios
          .post(`/api/plants/${this.currentPage}/15/${this.sort}`, plantData)
          .then((response) => {
            response.data.plants.forEach(elem => {
              let plant = {
                id: elem.id,
                image: elem.image,
                species: elem.species,
                price: elem.price,
                createdAt: elem.createdAt,
                place: elem.place
              };
              this.plants.push(plant);
            });
            this.plantsCount = parseInt(response.data.count);
          })
    },

    submitForm() {
      this.currentPage = ref(1);
      this.getPlants();
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
    },

    navigate(plant_id, species) {
      sessionStorage.setItem("plant", plant_id);
      this.$router.push(`/plants/sale/${species}`)
    }
  }
}
</script>

<style>
@import "../../../main.css";
@import "../../../plants.css";

#search-button {
  margin-left: 1%;
  width: 8%;
}

.custom-select {
  font-family: 'Century Gothic', sans-serif;
  font-size: 13px;
  color: #000000;
  width: 200px;
  padding: 10px;
  border-color: transparent;
  background-color: #FFFFFF;
  appearance: none;
  -webkit-appearance: none;
  -moz-appearance: none;
  cursor: pointer;
}

.custom-select:focus {
  border-color: transparent;
  outline: none;
}

.custom-select::after {
  position: absolute;
  border: 2px solid transparent;
  right: 10px;
  top: 50%;
  transform: translateY(-50%);
  pointer-events: none;
}

.custom-select option {
  font-weight: 400;
  color: #000000;
  padding: 10px;
  background-color: #FFFFFF;
}
</style>