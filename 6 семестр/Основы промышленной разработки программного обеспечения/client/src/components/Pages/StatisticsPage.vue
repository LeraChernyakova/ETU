<template>
  <Navbar :username="name" :position="position">
    <Filters class="first-filter">
      <div class="date-time-info">
        <DateTime
            v-model="beginTimestamp"
            :max="endTimestamp || today"
            id="start-date"
        ></DateTime>
        <button id="reset-begin-date" class="reset-date" @click="resetBeginDate">Сброс</button>
        <p>—</p>
        <DateTime
            v-model="endTimestamp"
            :min="beginTimestamp"
            :max="today"
            id="end-date"
        ></DateTime>
        <button id="reset-end-date" class="reset-date" @click="resetEndDate">Сброс</button>
      </div>
      <v-btn variant="outlined" value="download" icon="mdi-download" class="download-button" @click="downloadDialog=true"></v-btn>
      <Dialog v-model="downloadDialog" @close="downloadDialog=false" :params="params"></Dialog>
      <div class="choose-type">
        <v-btn-toggle class="stat-type" v-model="selectedType" variant="outlined" color="blue">
          <v-btn value="graphic" class="graphic" icon="mdi-chart-line" id="graph-button"></v-btn>
          <v-btn value="table" icon="mdi-format-align-justify" id="table-button"></v-btn>
        </v-btn-toggle>
      </div>
    </Filters>
    <Filters class="second-filter">
      <v-col class="v-col-filters">
        <ColumnSearch id="search-id" label="ID студента" v-model="ID" :rules="idRules" @keydown.enter="startSearchFilters"></ColumnSearch>
        <ColumnSearch id="search-name" label="ФИО студента" v-model="FIO" @keydown.enter="startSearchFilters"></ColumnSearch>
      </v-col>
      <v-col class="v-col-filters">
        <ColumnSearch id="search-email" label="email" v-model="email" @keydown.enter="startSearchFilters"></ColumnSearch>
        <ColumnSearch id="search-course" label="Название курса" v-model="course" @keydown.enter="startSearchFilters"></ColumnSearch>
      </v-col>
      <v-col class="v-col-filters">
        <ColumnSearch id="search-action-type" label="Тип действия" v-model="actionType" @keydown.enter="startSearchFilters"></ColumnSearch>
        <ColumnSearch id="search-event-type" label="Тип события" v-model="eventType" @keydown.enter="startSearchFilters"></ColumnSearch>
      </v-col>
      <v-col class="v-col-filters">
        <ColumnSearch id="search-element-type" label="Тип элемента" v-model="elementType" @keydown.enter="startSearchFilters"></ColumnSearch>
        <ColumnSearch id="search-element-name" label="Название элемента" v-model="elementName" @keydown.enter="startSearchFilters"></ColumnSearch>
      </v-col>
      <div class="search-reset-button ">
        <button id="start-search" class="start-search-button" @click="startSearchFilters">Поиск</button>
        <button id="reset-search" class="reset-button" @click="resetSearch">Сброс</button>
      </div>
    </Filters>
    <StatisticsTable v-if="selectedType === 'table'" :info="statisticsInfo" v-model:search="search"></StatisticsTable>
    <Chart v-else :info="statisticsInfo"></Chart>
  </Navbar>
</template>

<script>
import Navbar from "@/components/Navbar.vue";
import StatisticsTable from "@/components/Tables/StatisticsTable.vue";
import axios from "axios";
import Filters from "@/components/Filters/Filters.vue";
import Chart from "@/components/Chart.vue";
import DateTime from "@/components/Filters/DateTime.vue";
import Dialog from "@/components/Dialog.vue";
import ColumnSearch from "@/components/Filters/ColumnSearch.vue";


const STAT_URL = "/api/statistics/";

export default {
  name: "Statistics",
  components: {ColumnSearch, DateTime, Chart, Filters, StatisticsTable, Navbar, Dialog},


  data() {
    return {
      statisticsInfo: [],
      name: "",
      search: "",
      selectedType: 'table',
      beginTimestamp: '',
      endTimestamp: '',
      today: '',
      position: '',
      downloadDialog: false,
      ID: '',
      idRules: [
        value => {
          if (/^\d+$/.test(value) || value === null || value.length === 0) return true
          else return 'Допустимые значения только цифры!'
        },
      ],
      FIO: '',
      email: '',
      course: '',
      actionType: '',
      eventType: '',
      elementType: '',
      elementName: '',
      startSearch: false,
      params: {}
    };
  },

  beforeMount() {
    this.today = new Date().toISOString().slice(0, 16);
    let name = sessionStorage.getItem("name");
    if (name) {
      this.name = name;
      this.position = sessionStorage.getItem("position");
    } else {
      const error = 'Request failed with status code 401. You are not sign in!'
      alert(error)
      console.log("Не авторизован");
      this.$router.push("/e.moevm.statistics/auth");
    }
  },

  mounted() {
    this.getStatistics();
  },

  watch: {
    beginTimestamp() {
      this.getStatistics();
    },
    endTimestamp() {
      this.getStatistics();
    },
    ID() {
      if (this.ID === null && this.startSearch === true) {
        this.getStatistics();
      }
    },
    FIO() {
      if (this.FIO === null && this.startSearch === true) {
        this.getStatistics();
      }
    },
    email() {
      if (this.email === null && this.startSearch === true) {
        this.getStatistics();
      }
    },
    course() {
      if (this.course === null && this.startSearch === true) {
        this.getStatistics();
      }
    },
    actionType() {
      if (this.actionType === null && this.startSearch === true) {
        this.getStatistics();
      }
    },
    eventType() {
      if (this.eventType === null && this.startSearch === true) {
        this.getStatistics();
      }
    },
    elementType() {
      if (this.elementType === null && this.startSearch === true) {
        this.getStatistics();
      }
    },
    elementName() {
      if (this.elementName === null && this.startSearch === true) {
        this.getStatistics();
      }
    },
  },

  methods: {
    resetBeginDate() {
      this.beginTimestamp = '';
    },

    resetEndDate() {
      this.endTimestamp = '';
    },

    startSearchFilters() {
      this.startSearch = true;
      this.getStatistics();
    },

    resetSearch() {
      this.ID = '';
      this.FIO = '';
      this.email = '';
      this.course = '';
      this.actionType = '';
      this.eventType = '';
      this.elementType = '';
      this.elementName = '';
      if (this.startSearch === true) {
        this.getStatistics();
        this.startSearch = false;
      }
    },

    getStatistics() {
      this.statisticsInfo = []
      this.params = {}
      const searchParams = {
        student_id: Number(this.ID),
        student_name: this.FIO,
        student_email: this.email,
        course_title: this.course,
        action_type: this.actionType,
        event_type: this.eventType,
        element_type: this.elementType,
        element_name: this.elementName
      }

      if (this.beginTimestamp.length === 0 && this.endTimestamp.length === 0) {
        this.params = {}
      }
      else if (this.beginTimestamp.length !== 0 && this.endTimestamp.length === 0) {
        this.params = {
          begin_timestamp: this.beginTimestamp
        }
      }
      else if (this.beginTimestamp.length === 0 && this.endTimestamp.length !== 0) {
        this.params = {
          end_timestamp: this.endTimestamp
        }
      }
      else {
        this.params = {
          begin_timestamp: this.beginTimestamp,
          end_timestamp: this.endTimestamp
        }
      }

      Object.assign(this.params, searchParams)

      axios
          .get(STAT_URL, {params: this.params})
          .then((response) => {
            console.log(response);
            response.data.forEach(element => {
              let firstLayer = {
                FIO: element.student,
                course: element.course,
                studentId: element.student_id,
                email: element.email
              };
              element.actions.forEach(action =>{
                let secondLayer = {...firstLayer};
                secondLayer.typeAction = action.action_type;
                secondLayer.eventType = action.event_type;
                secondLayer.elementType = action.element_type;
                secondLayer.elementName = action.element_name;
                const dateTime = new Date(action.timestamp);
                const hours = dateTime.getHours().toString().padStart(2, '0');
                const minutes = dateTime.getMinutes().toString().padStart(2, '0');
                const seconds = dateTime.getSeconds().toString().padStart(2, '0');
                const milliseconds = dateTime.getMilliseconds().toString().padStart(3, '0');
                secondLayer.time = `${hours}:${minutes}:${seconds}.${milliseconds}`;
                secondLayer.date = dateTime.toLocaleDateString('ru-RU');
                secondLayer.Date = dateTime;
                this.statisticsInfo.push(secondLayer);
              })
            });
          })
          .catch((error) => {
            alert("Ошибка при получении данных");
            console.error("Ошибка при получении данных:", error);
          });
    }
  }
};
</script>

<style>
@import '@/colors.css';
.second-filter {
  padding-top: 0;
  padding-bottom: 0;
}

.v-col-filters {
  padding-top: 0;
  padding-bottom: 0;
  padding-left: 0;
}

.reset-button {
  padding: 6px 10px 6px 10px;
  border-radius: 10px;
  background-color: var(--white-4);
  color: var(--blue-4);
}
.reset-button:hover {
  background-color: var(--white-5);
}

.start-search-button {
  transform: translateY(-60%);
  padding: 6px 10px 6px 10px;
  border-radius: 10px;
  background-color: var(--white-4);
  color: var(--green-1)
}
.start-search-button:hover {
  background-color: var(--white-5);
}

.search-reset-button {
  display: flex;
  flex-direction: column;
}

.date-time-info {
  margin: 0;
  display: flex;
  align-items: center;
}

.date-time-info p {
  margin-top: 1%;
  margin-right: 1%;
  margin-left: 1%;
  font-size: 16px;
  font-family: Inter, sans-serif;
  color: var(--grey-6);
}

.reset-date {
  margin-left: 1%;
  transform: translateY(12.5%);
  padding: 6px 10px 6px 10px;
  border-radius: 10px;
  background-color: var(--white-4);
  color: var(--blue-4);
}

.reset-date:hover {
  background-color: var(--white-5);
}

.choose-type {
  margin-right: 0;
}

.stat-type {
  transform: translateY(15%);
}

.stat-type .v-btn {
  color: var(--grey-7);
}

.download-button{
  border-radius: 4px;
  border: 1px solid var(--grey-1);
  color: var(--grey-7);
  transform: translateY(14%);
  margin-left: 50%;
}
</style>
  
