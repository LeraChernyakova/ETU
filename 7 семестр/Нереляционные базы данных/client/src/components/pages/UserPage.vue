<template>
  <Navbar/>
  <div class="page-layout">
    <div class="sidebar">
      <div class="side-form">
        <img src="../../../public/logo.png" alt="Plant Shop Logo" class="logo"/>
        <div class="user-info">
          <input
              type="file"
              ref="fileInput"
              @change="changePhoto"
              style="display: none"
          />
          <img @click="triggerFileInput($event)" :src="user.photo" alt="User Photo" class="user-photo">
          <div class="user-details">
            <p class="user-lastname">{{ lastName }}</p>
            <p class="user-firstname">{{ firstName }}</p>
            <p class="user-middlename">{{ patronymic }}</p>
          </div>
        </div>
        <p class="create">Cоздание аккаунта: {{ formatDate(user.accountCreationDate) }}</p>
        <p class="create">Внесение изменений: {{ formatDate(user.lastModificationDate) }}</p>
        <form @submit.prevent="submitUserChanges">
          <div class="inputs-labels">
            Фамилия
            <input class="inputs" v-model="user.lastName" :placeholder="user.lastName"/>
          </div>

          <div class="inputs-labels">
            Имя
            <input class="inputs" v-model="user.firstName" :placeholder="user.firstName"/>
          </div>

          <div class="inputs-labels">
            Отчество
            <input class="inputs" v-model="user.patronymic" :placeholder="user.patronymic"/>
          </div>

          <div class="inputs-labels">
            Почта
            <input class="inputs" v-model="user.email" :placeholder="user.email"/>
          </div>

          <div class="inputs-labels">
            Телефон
            <input class="inputs" v-model="user.phone" :placeholder="user.phone"/>
          </div>

          <button type="submit" class="white-button-green-text">Сохранить изменения</button>
        </form>
        <button class="green-button-white-text" style="margin-top: 1%" @click="entrance">Выход</button>
      </div>
    </div>

    <div class="plant-container">
      <header class="user-modal-header">
        <span
            :style="{ color: selected === 'buy' ? '#000000' : '#7E7E7E', fontWeight: 'bold', fontSize: '14px', fontFamily: 'Century Gothic,sans-serif'}"
            @click="select('buy')"
            class="clickable">
          Купленные растения
        </span>
        <span
            :style="{ color: selected === 'trade' ? '#000000' : '#7E7E7E', fontWeight: 'bold', fontSize: '14px', fontFamily: 'Century Gothic,sans-serif' }"
            @click="select('trade')"
            class="clickable">
          Совершенные обмены
        </span>
      </header>

      <div class="search-plants">
        <input class="user-search-input" v-model="filter.species" type="text" placeholder="Поиск по объявлениям"/>
        <button class="white-button-green-text" id="filter-button" @click="isOpen = true">Фильтрация</button>
        <button class="green-button-white-text" id="search-button" @click="getPlants">Найти</button>
      </div>

      <div class="plant-grid" style="margin-top: 2%">
        <div v-for="plant in plants" class="plant-card">
          <div class="plant-content">
            <img v-if="plant.image" :src="plant.image" alt="Plant Image" class="plant-image" />
            <div class="plant-info">
              <div v-if="plant.species" class="plant-title">{{ plant.species }}</div>
              <div v-if="plant.price" class="plant-price">{{ formatPrice(plant.price) }}</div>
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

  <div v-if="isOpen" class="modal-overlay" @click="close">
    <div class="modal-content-user" @click.stop>
      <header class="trade-modal-header">
        <div style="display: flex; justify-content: space-between; width: 100%;">
          <h2 style="font-family: 'Century Gothic', sans-serif; color: black">Настройка фильтрации</h2>
          <button @click="closeModal" class="close-button">X</button>
        </div>
      </header>

      <form @submit.prevent="submitFilter">
        <div style="display: flex; flex-direction: row">
          <div>
            <div class="inputs-labels">
              Тип растения
              <input class="inputs" v-model="filter.type" placeholder="Наименование типа" />
            </div>
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
          </div>
          <div>
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
          </div>
        </div>
        <div style="display: flex; align-items: center; justify-content: flex-end">
          <button type="submit" class="green-button-white-text" style="width: 30%; margin-top: 1%">Применить</button>
        </div>
      </form>
    </div>
  </div>
</template>

<script>
import axios from 'axios';
import Navbar from "@/components/Navbar.vue";
export default {
  name: "User",
  components: { Navbar },

  data() {
    return {
      lastName: '',
      firstName: '',
      patronymic: '',
      user: {
        photo: '',
        accountCreationDate: '',
        lastModificationDate: '',
        lastName: '',
        firstName: '',
        patronymic: '',
        email: '',
        phone: '',
        userId: ''
      },
      plants: [],
      selected: 'buy',
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
      isOpen: false
    };
  },

  mounted() {
    this.user.userId = sessionStorage.getItem("id");
    this.getUser();
    this.getPlants()
  },

  methods: {
    entrance() {
      this.$router.push(`/plants/start`);
      sessionStorage.clear();
    },

    async getUser() {
      const id = this.user.userId;
      axios
          .get(`/api/v1/user/${id}`)
          .then((response) => {
            const curUser = response.data;
            this.lastName = curUser.surname;
            this.firstName = curUser.name;
            this.patronymic = curUser.father_name;
            this.user.photo = curUser.photo;
            this.user.lastName = curUser.surname;
            this.user.firstName = curUser.name;
            this.user.patronymic = curUser.father_name;
            this.user.email = curUser.email;
            this.user.phone = curUser.phone_number;
            this.user.lastModificationDate = curUser.updatedAt;
            this.user.accountCreationDate = curUser.createdAt;
          })
    },

    formatDate(dateString) {
      const date = new Date(dateString);
      const options = {
        day: '2-digit',
        month: '2-digit',
        year: 'numeric',
      };
      return date.toLocaleDateString('ru-RU', options);
    },

    triggerFileInput(event) {
      event.preventDefault();
      this.$refs.fileInput.click();
    },

    changePhoto(event) {
      const file = event.target.files[0];
      if (file) {
        const reader = new FileReader();
        reader.onload = (e) => {
          this.user.photo = e.target.result;
        };
        reader.readAsDataURL(file);
      }
    },

    submitUserChanges() {
      this.postUserChanges();
    },

    successChanges() {
      this.$notify({
        title: "Получилось!",
        text: "данные успешно обновлены.",
        type: 'success'
      });
    },

    errorChanges() {
      this.$notify({
        title: "Ошибка!",
        text: "Произошла ошибка при обновлении данных. Попробуйте снова.",
        type: 'error'
      });
    },

    async postUserChanges() {
      const userData = {
        name: this.user.firstName,
        surname: this.user.lastName,
        fatherName: this.user.patronymic,
        email: this.user.email,
        phoneNumber: this.user.phone,
        photo: this.user.photo,
      };

      try {
        await axios.post(`/api/v1/user/${this.user.userId}`, userData);
        this.patronymic = this.user.patronymic;
        this.firstName = this.user.firstName;
        this.lastName = this.user.lastName;
        this.successChanges();
      } catch (error) {
        this.errorChanges();
      }
    },

    select(type) {
      this.selected = type;
      this.getPlants();
    },

    normalizePrice(price) {
      return price !== null ? price : 0;
    },

    async getPlants() {
      this.plants = [];

      const plantData = {
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
        }
      };

      axios
          .post(`/api/plants/${this.selected}/${this.user.userId}`, plantData)
          .then((response) => {
            response.data.plants.forEach(elem => {
              let plant = {
                image: elem.image,
                species: elem.species,
                price: elem.price
              };
              this.plants.push(plant);
            });
          })
    },

    formatPrice(price) {
      return `${price} ₽`;
    },

    submitFilter() {
      this.getPlants();
      this.closeModal()
    },

    closeModal() {
      this.isOpen = false;
      this.filter.place = '';
      this.filter.size = [];
      this.filter.priceFrom = null;
      this.filter.priceTo = null;
      this.filter.lightCondition = [];
      this.filter.wateringFrequency = [];
      this.filter.temperatureRegime = [];
      this.filter.careComplexity = [];
      this.filter.description = '';
      this.filter.type = '';
      this.filter.species = ''
    }
  }
};
</script>


<style>
@import "../../../main.css";
@import "../../../plants.css";
@import "../../../modal.css";
@import "../../../user.css";

#search-button {
  margin-left: 1%;
  width: 8%;
}

#filter-button {
  margin-left: 1%;
  width: 10%;
  margin-top: 0;
}
</style>