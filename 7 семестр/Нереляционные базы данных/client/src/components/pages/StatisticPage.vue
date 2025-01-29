<template>
  <Navbar />
  <div class="page-layout">
    <div class="sidebar">
      <div class="side-form">
        <img src="../../../public/logo.png" alt="Plant Shop Logo" class="logo"/>
        <div class="inputs-labels" id="statistic-label">
          Параметры статистики
        </div>
        <div class="inputs-labels">
          Тип статистики
        </div>
        <div class="select-sort">
          <select class="custom-select-stat" v-model="statType">
            <option disabled value="">Статистика</option>
            <option value="plants">По растениям</option>
            <option value="ads">По объявлениям</option>
            <option value="buy">По продажам</option>
            <option value="trade">По обменам</option>
          </select>
        </div>
        <div class="inputs-labels">
          Период времени
          <div style="display: flex; justify-content: space-between">
            <div style="display: flex; flex-direction: column; margin-right: 1%">
              <label style="font-weight: 500; font-size: 13px">С</label>
              <input
                  class="inputs"
                  v-model="dateFrom"
                  id="dateFrom"
                  type="date"
                  :max="new Date().toISOString().split('T')[0]"
                  @change="updateDateLimits()"
                  required
              />
            </div>
            <div style="display: flex; flex-direction: column">
              <label style="font-weight: 500; font-size: 13px">По</label>
              <input
                  class="inputs"
                  v-model="dateTo"
                  id="dateTo"
                  type="date"
                  min=""
                  max=""
                  disabled
                  required
              />
            </div>
          </div>
        </div>
        <div v-if="statType === 'plants'">
          <div class="inputs-labels">Типы растений</div>
          <div class="scrollable-checkboxes">
            <label v-for="type in types" :key="type" class="checkbox-labels">
              <input v-model="selectedTypes" type="checkbox" :value="type" :disabled="statType !== 'plants'" />
              {{ type }}
              <br>
            </label>
          </div>
          <div class="inputs-labels">Условия освещения</div>
          <label class="checkbox-labels"><input v-model="lighting" type="checkbox" value="Тенелюбивые" :disabled="statType !== 'plants'"/> Тенелюбивые</label>
          <br>
          <label class="checkbox-labels"><input v-model="lighting" type="checkbox" value="Полутеневые" :disabled="statType !== 'plants'"/> Полутеневые</label>
          <br>
          <label class="checkbox-labels"><input v-model="lighting" type="checkbox" value="Светолюбивые" :disabled="statType !== 'plants'"/> Светолюбивые</label>
        </div>
        <button style="margin-top: 2%" class="green-button-white-text" @click="getStatistic">Отобразить</button>
        <div class="inputs-labels">
          Работа с базой данных
        </div>
        <button style="margin-top: 2%" class="white-button-green-text" @click="getData">Экспортировать</button>
        <input
            type="file"
            ref="fileInput"
            @change="addDB"
            style="display: none"
        />
        <button style="margin-top: 2%" class="green-button-white-text" @click="triggerFileInput($event)">Импортировать</button>
      </div>
    </div>

    <div class="plant-container">
        <Bar v-if="chart===true" :data="data" :options="options" style="height: 500px"/>
    </div>
  </div>
</template>

<script>
import Navbar from "@/components/Navbar.vue";
import axios from "axios";
import {
  Chart as ChartJS,
  Title,
  Tooltip,
  Legend,
  BarElement,
  CategoryScale,
  LinearScale,
} from 'chart.js'
import zoomPlugin from 'chartjs-plugin-zoom';
import { Bar } from 'vue-chartjs'

ChartJS.register(CategoryScale, LinearScale, BarElement, Title, Tooltip, Legend, zoomPlugin)

export default {
  name: "Statistic",
  components: { Navbar, Bar },

  data() {
    return {
      statType: '',
      dateFrom: '',
      dateTo: '',
      lighting: [],
      chart: false,
      types: [],
      selectedTypes: [],
      data: {
        labels: [],
        datasets: []
      },
      options: {
        responsive: true,
        maintainAspectRatio: false,
        plugins: {
          title: {
            display: true,
            text: 'Мой график',
            font: {
              size: 18,
              weight: 'bold'
            },
            padding: {
              top: 10,
              bottom: 20
            },
            align: 'center',
            color: '#333'
          },
          legend: {
            display: true,
            position: 'top'
          },
          zoom: {
            zoom: {
              wheel: {
                enabled: true
              },
              pinch: {
                enabled: true
              },
              mode: 'x'
            },
            pan: {
              enabled: true,
              mode: 'x'
            }
          }
        },
        scales: {
          y: {
            ticks: {
              drawBorder: false,
              display: false
            },
            grid: {
              drawBorder: false,
              display: false
            }
          },
          x: {
            grid: {
              drawBorder: false
            }
          }
        }
      }
    };
  },

  created() {
    axios
        .get(`/api/plants/types/typesArray`)
        .then((response) => {
          response.data.types.forEach(elem => {
            this.types.push(elem);
          });
        })
  },

  methods: {
    updateDateLimits() {
      const today = new Date().toISOString().split("T")[0];
      const dateFrom = document.getElementById("dateFrom");
      const dateTo = document.getElementById("dateTo");
      dateFrom.setAttribute("max", today);

      if (dateFrom.value) {
        dateTo.removeAttribute("disabled");
        dateTo.setAttribute("min", dateFrom.value);
        dateTo.setAttribute("max", today);
      } else {
        dateTo.setAttribute("disabled", true);
      }
    },

    formatTimeFrom(dateString) {
      return `${dateString}T00:00:00Z`;
    },

    formatTimeTo(dateString) {
      return `${dateString}T23:59:59Z`;
    },

    getStatistic() {
      this.chart = false;
      let filter = {};
      if (this.statType === "plants") {
        filter = {
          filter: {
            timeFrom: this.formatTimeFrom(this.dateFrom),
            timeTo: this.formatTimeTo(this.dateTo),
          },
          type: this.selectedTypes,
          lightCondition: this.lighting
        }
      } else {
        filter = {
          filter: {
            timeFrom: this.formatTimeFrom(this.dateFrom),
            timeTo: this.formatTimeTo(this.dateTo)
          }
        }
      }
      this.data = { datasets: [], labels: [] };
      axios
          .post(`/api/stats/${this.statType}`, filter)
          .then((response) => {
            if (this.statType === 'plants') {
              if (Object.keys(response.data).length === 0) {
                this.options.plugins.title.text = `Данных за указанный период не найдено!`;
                this.chart = true
                return;
              }
              const plantsCount = response.data.count;
              this.options.plugins.title.text = `Данные по видам публикуемых растений. Количество записей: ${plantsCount}`;
              this.data.datasets = [
                {
                  label: 'Растения',
                  backgroundColor: '#89A758',
                  data: []
                }
              ];
              response.data.stats.forEach(elem => {
                this.data.datasets[0].data.push(elem.count);
                this.data.labels.push(elem.species)
              });
              this.chart = true
            } else if (this.statType === 'ads') {
              if (Object.keys(response.data).length  === 0) {
                this.options.plugins.title.text = `Данных за указанный период не найдено!`;
                this.chart = true
                return;
              }
              const plantsCount = response.data.count;
              this.options.plugins.title.text = `Данные по опубликованным объявлениям. Количество записей: ${plantsCount}`;
              this.data.datasets = [
                {
                  label: 'Объявления',
                  backgroundColor: '#89A758',
                  data: []
                }
              ];
              response.data.stats.forEach(elem => {
                this.data.datasets[0].data.push(elem.count);
                this.data.labels.push(elem.date.split('T')[0])
              });
              this.chart = true
            } else if (this.statType === 'buy') {
              if (Object.keys(response.data).length  === 0) {
                this.options.plugins.title.text = `Данных за указанный период не найдено!`;
                this.chart = true
                return;
              }
              const plantsCount = response.data.count;
              this.options.plugins.title.text = `Данные по продажам. Количество записей: ${plantsCount}`;
              this.data.datasets = [
                {
                  label: 'Продано',
                  backgroundColor: '#89A758',
                  data: []
                }
              ];
              response.data.stats.forEach(elem => {
                this.data.labels.push(elem.date.split('T')[0]);
                this.data.datasets[0].data.push(elem.count);
              });
              this.chart = true
            } else {
              if (Object.keys(response.data).length  === 0) {
                this.options.plugins.title.text = `Данных за указанный период не найдено!`;
                this.chart = true
                return;
              }
              const plantsCount = response.data.count;
              this.options.plugins.title.text = `Данные по обменам. Количество записей: ${plantsCount}`;
              let pend = [];
              let accept = [];
              let reject = [];
              response.data.stats.forEach(elem => {
                const label = elem.date.split('T')[0];
                let labelInd = this.data.labels.indexOf(label);
                if (labelInd === -1) {
                  labelInd = this.data.labels.length;
                }
                this.data.labels[labelInd] = elem.date.split('T')[0];
                const tradeStatus = elem.status;
                if (tradeStatus === "1") {
                  pend[labelInd] = elem.count;
                  accept[labelInd] = (accept[labelInd] === 0 || !accept[labelInd]) ? 0 : accept[labelInd] ;
                  reject[labelInd] = (reject[labelInd] === 0 || !reject[labelInd]) ? 0 : reject[labelInd] ;
                } else if (tradeStatus === "2") {
                  pend[labelInd] = (pend[labelInd] === 0 || !pend[labelInd]) ? 0 : pend[labelInd] ;
                  accept[labelInd] = elem.count;
                  reject[labelInd] = (reject[labelInd] === 0 || !reject[labelInd]) ? 0 : reject[labelInd] ;
                } else {
                  pend[labelInd] = (pend[labelInd] === 0 || !pend[labelInd]) ? 0 : pend[labelInd] ;
                  accept[labelInd] = (accept[labelInd] === 0 || !accept[labelInd]) ? 0 : accept[labelInd] ;
                  reject[labelInd] = elem.count;
                }
              });
              this.data.datasets = [
                {
                  label: 'Создано',
                  backgroundColor: 'rgba(137,167,88,0.59)',
                  data: pend
                },
                {
                  label: 'Согласовано',
                  backgroundColor: '#a9ce6d',
                  data: accept
                },
                {
                  label: 'Отменено',
                  backgroundColor: 'rgb(88,105,58)',
                  data: reject
                },
              ];
              this.chart = true
            }
          })
    },

    async getData() {
      try {
        const response = await axios.get(`/api/data`, {});
        const jsonString = atob(response.data.db);

        const byteArray = new Uint8Array(jsonString.length);
        for (let i = 0; i < jsonString.length; i++) {
          byteArray[i] = jsonString.charCodeAt(i);
        }

        const decodedString = new TextDecoder("utf-8").decode(byteArray);

        const blob = new Blob([decodedString], { type: "application/json" });

        const url = URL.createObjectURL(blob);
        const link = document.createElement("a");
        link.href = url;
        link.download = "data.json";
        document.body.appendChild(link);
        link.click();

        document.body.removeChild(link);
        URL.revokeObjectURL(url);
      } catch (error) {
        this.errorExport();
      }
    },

    addDB(event) {
      const reader = new FileReader();
      const file = event.target.files[0];
      reader.readAsDataURL(file);

      reader.onload = () => {
        const base64Data = reader.result.split(',')[1];

        fetch('/api/data', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({
            db: base64Data
          }),
        })
            .then(response => response.json())
            .then(data => {
              this.successImport();
            })
            .catch(error => {
              this.errorImport();
            });
      };

      reader.onerror = (error) => {
        console.error('Ошибка при чтении файла:', error);
      };
    },

    triggerFileInput(event) {
      event.preventDefault();
      this.$refs.fileInput.click();
    },

    errorExport() {
      this.$notify({
        title: "Ошибка!",
        text: "Произошла ошибка при импортировании базы данных.",
        type: 'error'
      });
    },

    successImport() {
      this.$notify({
        title: "Получилось!",
        text: "База данных успешно экспортирована.",
        type: 'success'
      });
    },

    errorImport() {
      this.$notify({
        title: "Ошибка!",
        text: "Произошла ошибка при экспортировании базы данных.",
        type: 'error'
      });
    },
  }
}
</script>

<style scoped>
@import "../../../main.css";
@import "../../../plants.css";

.page-layout {
  display: flex;
}

#statistic-label {
  color: #89A758;
}

.custom-select-stat {
  font-family: 'Century Gothic', sans-serif;
  font-size: 13px;
  color: #000000;
  padding: 10px;
  border: 1px solid #EEECEC;
  background-color: #eeecec;
  appearance: none;
  -webkit-appearance: none;
  -moz-appearance: none;
  cursor: pointer;
  width: 100%;
  border-radius: 10px;
}

.custom-select-stat:focus {
  border-color: transparent;
  outline: none;
}

.custom-select-stat::after {
  position: absolute;
  border: 2px solid transparent;
  right: 10px;
  top: 50%;
  transform: translateY(-50%);
  pointer-events: none;
}

.custom-select-stat option {
  font-weight: 400;
  color: #000000;
  padding: 10px;
  background-color: #FFFFFF;
}

.scrollable-checkboxes {
  max-height: 120px;
  overflow-y: auto;
  border: 1px solid #ccc;
  padding: 10px;
  border-radius: 4px;
}
</style>