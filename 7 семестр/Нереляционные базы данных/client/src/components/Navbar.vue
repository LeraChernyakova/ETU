<template>
  <div class="navbar">

    <div class="menu-icons">
      <i v-if="role === 0" class="icon fa fa-chart-bar" @click="navigate(0)"></i>
      <i class="icon fa fa-search" @click="navigate(role === 0 ? 1 : 0)"></i>
      <i class="icon fa fa-leaf" @click="navigate(role === 0 ? 2 : 1)"></i>
      <i class="icon fa fa-bell" @click="openModal" ></i>
      <i class="icon fa fa-user-circle" @click="navigate(role === 0 ? 3 : 2)"></i>
    </div>

    <button class="my-ads-button" @click="navigate(role === 0 ? 4 : 3)">Мои объявления</button>

    <div v-if="isOpen" class="modal-overlay" @click="close">
      <div class="trade-modal-content" @click.stop>
        <header class="trade-modal-header">
          <div style="display: flex; justify-content: space-between; width: 100%;">
            <h2 style="font-family: 'Century Gothic', sans-serif; color: black">Запросы</h2>
            <button @click="closeModal" class="close-button">X</button>
          </div>
          <div style="margin-top: 2%;">
            <span :style="{ fontWeight: selected === 'in' ? 'bold' : 'normal', color: 'black', fontSize: '14px'}"
                  @click="select('in')" class="clickable">
              Входящие
            </span>
            <span :style="{ fontWeight: selected === 'out' ? 'bold' : 'normal', color: 'black', fontSize: '14px' }" @click="select('out')" class="clickable">
              Исходящие
            </span>
          </div>
        </header>

        <section v-if="selected === 'in'" class="modal-body" v-for="(trades, index) in inT" :key="index">
          <div style="display: flex;flex-direction: row">
            <div style="display: flex;flex-direction: row">
              <img v-if="trades.plant_in_image" :src="trades.plant_in_image" alt="Plant Image" class="trade-plant-image" />
              <i class="icon fa fa-arrows-h"
                 style="color: #7E7E7E; display: flex; justify-content: center; align-items: center; margin-left: 2%; margin-right: 2%"
              ></i>
              <img v-if="trades.plant_out_image" :src="trades.plant_out_image" alt="Plant Image" class="trade-plant-image" />
            </div>
            <div style="margin-left: 4%">
              <p :style="{fontWeight: 'bold'}">{{ trades.offerer }} предлагает</p>
              <p>{{ trades.plant_in }}</p>
              <p :style="{fontWeight: 'bold'}">В обмен на</p>
              <p>{{ trades.plant_out }}</p>
              <div style="margin-top: 2%; display: flex; gap: 10px;">
                <button class="trade-button" @click="acceptTrade(trades.id)">Согласиться</button>
                <button class="trade-button" @click="rejectTrade(trades.id)">Отказаться</button>
              </div>
            </div>
          </div>
          <hr style="margin-top: 10px; border: 1px solid #ccc;" />
        </section>

        <section v-if="selected === 'out'" class="modal-body" v-for="(trades, index) in outT" :key="index">
          <div style="display: flex;flex-direction: row">
            <div style="display: flex;flex-direction: row">
              <img v-if="trades.plant_out_image" :src="trades.plant_in_image" alt="Plant Image" class="trade-plant-image" />
              <i class="icon fa fa-arrows-h"
                 style="color: #7E7E7E; display: flex; justify-content: center; align-items: center; margin-left: 2%; margin-right: 2%"
              ></i>
              <img v-if="trades.plant_in_image" :src="trades.plant_out_image" alt="Plant Image" class="trade-plant-image" />
            </div>
            <div style="margin-left: 4%">
              <p :style="{fontWeight: 'bold'}">Вы предложили</p>
              <p>{{ trades.plant_out }}</p>
              <p :style="{fontWeight: 'bold'}">В обмен на</p>
              <p>{{ trades.plant_in }}</p>
              <p :style="{fontWeight: 'bold', color: '#89A758'}">Статус</p>
              <p>{{ trades.status }}</p>
            </div>
          </div>
          <hr style="margin-top: 10px; border: 1px solid #ccc;" />
        </section>
      </div>
    </div>
  </div>
</template>

<script>
import axios from "axios";

export default {
  name: "Navbar",

  data() {
    return {
      role: null,
      id: '',
      currentType: 'in',
      inT: [],
      outT: [],
      selected: 'in',
      isOpen: false,
      adminItems: [
        { path: '/plants/statistics' },
        { path: '/plants/sale' },
        { path: '/plants/care'},
        { path: '/plants/user' },
        { path: '/plants/ads' }
      ],
      regularItems: [
        { path: '/plants/sale' },
        { path: '/plants/care'},
        { path: '/plants/user' },
        { path: '/plants/ads' }
      ]
    };
  },

  beforeMount() {
    const string_role = sessionStorage.getItem("role");
    if (string_role === "ROLE_ADMIN") {
      this.role = 0
    } else {
      this.role = 1
    }
    this.id = sessionStorage.getItem("id");
  },

  computed: {
    menuItems() {
      return this.role === 0 ? this.adminItems : this.regularItems;
    }
  },

  methods: {
    navigate(index) {
      const target = this.menuItems[index];
      if (target) {
        this.$router.push(target.path);
      }
    },

    openModal() {
      this.isOpen = true;
      this.getIn();
      this.getOut();
    },

    closeModal() {
      this.isOpen = false;
    },

    select(type) {
      this.selected = type;
    },

    reject() {
      this.$notify({
        title: "Отклонено!",
        text: "Вы отклонили предложение по обмену.",
        type: 'error'
      });
    },

    accept() {
      this.$notify({
        title: "Принято!",
        text: "Обмен растениями успешно совершен.",
        type: 'success'
      });
    },

    async getIn() {
      axios
          .get(`/api/trade/in/${this.id}`)
          .then((response) => {
            this.inT = [];
            response.data.trade.forEach(elem => {
              let in_trade = {
                offerer: elem.offerer.name,
                plant_in: elem.offerer.plant.name,
                plant_in_image: elem.offerer.plant.image,
                plant_out: elem.accepter.plant.name,
                plant_out_image: elem.accepter.plant.image,
                id: elem.id
              };
              this.inT.push(in_trade)
            })
          })
    },

    async getOut() {
      axios
          .get(`/api/trade/out/${this.id}`)
          .then((response) => {
            this.outT = [];
            response.data.trade.forEach(elem => {
              let trade_status = '';
              switch (elem.status) {
                case 'STATUS_UNSPECIFIED':
                  trade_status = 'Неизвестный статус';
                  break;
                case 'STATUS_PENDING':
                  trade_status = 'Ожидает подтверждения';
                  break;
                case 'STATUS_ACCEPTED':
                  trade_status = 'Согласовано';
                  break;
                case 'STATUS_REJECTED':
                  trade_status = 'Отклонено';
                  break;
              }
              let out_trade = {
                plant_out: elem.offerer.plant.name,
                plant_in: elem.accepter.plant.name,
                plant_out_image: elem.accepter.plant.image,
                plant_in_image: elem.offerer.plant.image,
                status: trade_status
              };
              this.outT.push(out_trade)
            })
          })
    },

    async acceptTrade(trade_id) {
      axios
          .post(`/api/trade/accept/${trade_id}`)
          .then((response) => {
            this.accept();
            this.getIn();
          })
    },

    async rejectTrade(trade_id) {
      axios
          .post(`/api/trade/reject/${trade_id}`)
          .then((response) => {
            this.reject();
            this.getIn();
          })
    },
  }
}
</script>

<style scoped>
@import "../../main.css";
@import "../../modal.css";

.navbar {
  display: flex;
  align-items: center;
  padding: 10px 20px;
  background-color: #333;
  color: #fff;
  position: fixed;
  top: 0;
  left: 0;
  width: 98%;
  z-index: 1000;
  box-shadow: 0 2px 10px rgba(0, 0, 0, 0.3);
}

.menu-icons {
  display: flex;
  gap: 15px;
  align-items: center;
  margin-left: auto;
}

.icon {
  font-size: 18px;
  cursor: pointer;
  color: #fff;
}

.my-ads-button {
  font-family: 'Century Gothic', sans-serif;
  padding: 8px 16px;
  background-color: #89A758;
  color: #fff;
  border: none;
  border-radius: 5px;
  cursor: pointer;
  font-size: 14px;
  margin-left: 20px;
  font-weight: bold;
}

.my-ads-button:hover {
  background-color: #77934a;
}

.clickable {
  cursor: pointer;
  margin-right: 10px;
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
  max-height: 80vh; /* Максимальная высота модального окна */
  overflow-y: auto;
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

.trade-button {
  font-size: 12px;
  font-weight: bold;
  color: #2E2E2E;
  background-color: transparent;
  border: 2px solid #89A758;
  border-radius: 10px;
  padding: 10px 15px;
  cursor: pointer;
  display: inline-flex;
  align-items: center;
  position: relative;
}

.trade-plant-image {
  width: 110px;
  height: 110px;
}

span {
  font-family: 'Century Gothic', sans-serif;
}
</style>
