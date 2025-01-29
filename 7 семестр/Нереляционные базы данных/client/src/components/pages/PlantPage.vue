<template>
  <Navbar />
  <div class="page-layout">
    <div class="sidebar">
      <div class="side-form">
        <img src="../../../public/logo.png" alt="Plant Shop Logo" class="logo"/>
        <h2 style="color: #7E7E7E; font-family: 'Century Gothic', sans-serif">Продавец</h2>
        <div class="user-info">
          <img :src="photo" alt="User Photo" class="user-photo">
          <div class="user-details">
            <p>{{ lastName }}</p>
            <p>{{ firstName }}</p>
            <p>{{ patronymic }}</p>
          </div>
        </div>
      </div>
    </div>

    <div class="plant-container">
      <div class="search-plants">
        <input class="search-input" type="text" v-model="search" placeholder="Поиск по объявлениям"/>
        <button class="green-button-white-text" id="search-button" @click="Search">Найти</button>
      </div>

      <div class="plant-info-grid">
        <div>
          <h2 style="color: #89A758; font-family: 'Century Gothic', sans-serif">{{ accepterPlant.species }}</h2>
          <img :src="accepterPlant.image" alt="Plant Photo" class="specific-plant-photo">
        </div>
        <div style="margin-left: 2%">
          <h2 style="color: #000000; font-family: 'Century Gothic', sans-serif; margin-bottom: 0">{{ formatPrice(accepterPlant.price) }}</h2>
          <p style="color: #6f6f6f; font-size: 14px; margin-bottom: 0; margin-top: 0; font-weight: bold">{{ accepterPlant.place }}</p>
          <p class="plant-date" style="margin: 0">Дата размещения: {{ formatDate(accepterPlant.createdAt) }}</p>
          <p style="color: #000000; font-size: 16px; font-weight: bold; margin-bottom: 0">Характеристики</p>
          <p style="color: #000000; font-size: 16px; margin-bottom: 0; margin-top: 0">Размер: {{accepterPlant.size}}</p>
          <p style="color: #000000; font-size: 16px; margin-bottom: 0; margin-top: 0">Условия освещения: {{accepterPlant.lighting}}</p>
          <p style="color: #000000; font-size: 16px; margin-bottom: 0; margin-top: 0">Частота полива: {{accepterPlant.wateringFrequency}}</p>
          <p style="color: #000000; font-size: 16px; margin-bottom: 0; margin-top: 0">Температурный режим: {{accepterPlant.temperature}}</p>
          <p style="color: #000000; font-size: 16px; margin-bottom: 0; margin-top: 0">Сложность ухода: {{accepterPlant.careLevel}}</p>
          <p style="color: #000000; font-size: 16px; font-weight: bold; margin-bottom: 0">Описание</p>
          <p style="color: #000000; font-size: 16px; margin-bottom: 0; margin-top: 0">{{ accepterPlant.description }}</p>
          <p style="color: #000000; font-size: 16px; font-weight: bold; margin-bottom: 0">Тип</p>
          <p style="color: #000000; font-size: 16px; margin-bottom: 0; margin-top: 0">{{ accepterPlant.type }}</p>
          <div>
            <button class="white-button-green-text-sale" @click="buyPlant">Купить</button>
            <button class="white-button-green-text-sale" @click="openModal">Обменяться</button>
          </div>
        </div>
      </div>
    </div>
  </div>

  <div v-if="isOpen" class="modal-overlay" @click="close">
    <div class="trade-modal-content" @click.stop>
      <header class="trade-modal-header">
        <div style="display: flex; justify-content: space-between; width: 100%;">
          <h2 style="font-family: 'Century Gothic', sans-serif; color: black">Обмен</h2>
          <button @click="closeModal" class="close-button">X</button>
        </div>
        <div style="margin-top: 2%;">
            <span :style="{ fontWeight: 'bold', color: 'black', fontSize: '14px'}">
              Выберете одно из своих объявлений для совершения обмена
            </span>
        </div>
      </header>

      <section class="modal-body" v-for="(ads, index) in plants_for_trade" :key="index">
        <div style="display: flex;flex-direction: row">
          <div style="display: flex;flex-direction: row">
            <input v-model="trade_plant_id" type="radio" :value="ads.id"/>
            <img v-if="ads.image" :src="ads.image" alt="Plant Image" class="trade-plant-image" />
          </div>
          <div style="margin-left: 4%">
            <p class="plant-title" style="color: #89A758">{{ ads.species }}</p>
            <p class="plant-price">{{ formatPrice(ads.price) }}</p>
            <p class="plant-place">{{ ads.place }}</p>
            <p class="plant-date">{{ formatDate(ads.createdAt) }}</p>
          </div>
        </div>
        <hr style="margin-top: 10px; border: 1px solid #ccc;" />
      </section>
      <div style="display: flex; align-items: center; justify-content: flex-end">
        <button type="submit" class="green-button-white-text" style="width: 30%" @click="createTrade">Отправить</button>
      </div>
    </div>
  </div>
</template>

<script>
import Navbar from "@/components/Navbar.vue";
import axios from "axios";

export default {
  name: "Plant",
  components: { Navbar },

  data() {
    return {
      search: '',
      lastName: '',
      firstName: '',
      patronymic: '',
      photo: '',
      accepterPlant: {
        id: '',
        type: '',
        species: '',
        size: '',
        lighting: '',
        wateringFrequency: '',
        temperature: '',
        careLevel: '',
        description: '',
        place: '',
        image: '',
        price: null
      },
      accepterID: '',
      offererID: '',
      isOpen: false,
      userAds: [],
      trade_plant_id: '',
      plants_for_trade: []
    };
  },

  mounted() {
    this.accepterPlant.id = sessionStorage.getItem("plant");
    this.offererID = sessionStorage.getItem("id");
    this.getPlant();
  },

  methods: {
    Search() {
      sessionStorage.setItem("search", this.search);
      this.$router.push('/plants/sale');
    },

    errorBuy() {
      this.$notify({
        title: "Ошибка!",
        text: "Произошла ошибка при покупке, попробуйте еще раз.",
        type: 'error'
      });
    },

    successBuy() {
      this.$notify({
        title: "Получилось!",
        text: "Вы приобрели новое растение.",
        type: 'success'
      });
    },

    errorTrade() {
      this.$notify({
        title: "Ошибка!",
        text: "Произошла ошибка при отправке запроса на обмен, попробуйте еще раз.",
        type: 'error'
      });
    },

    successTrade() {
      this.$notify({
        title: "Получилось!",
        text: "Вы отправили запрос на обмен.",
        type: 'success'
      });
    },

    async getPlant() {
      axios
          .get(`/api/plants/${this.accepterPlant.id}`)
          .then((response) => {
            this.accepterPlant.species = response.data.plant.species;
            this.accepterPlant.type = response.data.plant.type;
            this.accepterPlant.size = response.data.plant.size;
            this.accepterPlant.lighting = response.data.plant.lightCondition;
            this.accepterPlant.wateringFrequency = response.data.plant.wateringFrequency;
            this.accepterPlant.temperature = response.data.plant.temperatureRegime;
            this.accepterPlant.careLevel = response.data.plant.careComplexity;
            this.accepterPlant.description = response.data.plant.description;
            this.accepterPlant.place = response.data.plant.place;
            this.accepterPlant.image = response.data.plant.image;
            this.accepterPlant.price = parseInt(response.data.plant.price);
            this.accepterPlant.createdAt = response.data.plant.createdAt;
            this.firstName = response.data.user.name;
            this.lastName = response.data.user.surname;
            this.patronymic = response.data.user.fatherName;
            this.photo = response.data.user.photo;
            this.accepterID = response.data.user.id;
          })
    },

    openModal() {
      this.getPlantsForTrade();
      this.isOpen = true
    },

    formatPrice(price) {
      return `${price} ₽`;
    },

    errorGetPlantsForTrade() {
      this.$notify({
        title: "Ошибка!",
        text: "У вас нет доступных растений для обмена.",
        type: 'error'
      });
    },

    async getPlantsForTrade() {
      this.plants_for_trade = [];
      axios
          .get(`/api/plants/trade/${this.offererID}`)
          .then((response) => {
            if (response.data.plants.length === 0) {
              this.errorGetPlantsForTrade();
            } else {
              response.data.plants.forEach(elem => {
                let plant = {
                  id: elem.id,
                  image: elem.image,
                  species: elem.species,
                  price: parseInt(elem.price),
                  createdAt: elem.createdAt,
                  place: elem.place
                };
                this.plants_for_trade.push(plant);
              });
            }
          })
    },

    async buyPlant() {
      const buyData ={
        sellerId: this.accepterID,
        buyerId: this.offererID,
        plantId: this.accepterPlant.id,
        species: this.accepterPlant.species,
        price: this.accepterPlant.price
      }

      try {
        await axios.post(`/api/plants/buy`, buyData);
        this.successBuy();
        setTimeout(() => {
          this.$router.push('/plants/sale');
        }, 2000);
      } catch (error) {
        this.errorBuy();
      }
    },

    formatDate(date) {
      return new Date(date).toLocaleDateString("ru-RU", {
        year: 'numeric',
        month: 'long',
        day: 'numeric'
      });
    },

    async createTrade() {
      const tradeData ={
        offererId: this.offererID,
        offererPlantId: this.trade_plant_id,
        accepterId: this.accepterID,
        accepterPlantId: this.accepterPlant.id
      }
      try {
        await axios.post(`/api/trade`, tradeData);
        this.successTrade();
        this.closeModal();
        setTimeout(() => {
          this.$router.push('/plants/sale');
        }, 2000);
      } catch (error) {
        this.errorTrade();
      }
    },

    closeModal() {
      this.isOpen = false;
    }
  }
}
</script>

<style>
@import "../../../main.css";
@import "../../../plants.css";
@import "../../../user.css";
@import "../../../modal.css";

.trade-plant-image {
  width: 110px;
  height: 110px;
}

.trade-modal-content {
  max-height: 80vh;
  overflow-y: auto;
  background: #fff;
  width: 60%;
  max-width: 500px;
  padding: 20px;
  border-radius: 8px;
  position: relative;
}

.trade-modal-header {
  display: flex;
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
</style>