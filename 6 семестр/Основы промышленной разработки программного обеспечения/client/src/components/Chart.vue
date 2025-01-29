<template>
  <div class="centerBox">
    <p> Количество отображенных записей: {{this.number}} </p>
    <div class="window">
      <div id="wrap">
        <button id="reset" @click="resetGraph">
          <span>Масштаб</span>
          <br>
          <span class="second-line">по умолчанию</span>
        </button>
      </div>
      <Bar ref="myChart" :data="chartData" :options="chartOptions"/>
    </div>
  </div>
</template>


<script>
/* eslint-disable */
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  TimeScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
  BarElement,
} from "chart.js";
import { Bar } from "vue-chartjs";
import "chartjs-adapter-moment";
import zoomPlugin from "chartjs-plugin-zoom";

ChartJS.register(
  CategoryScale,
  LinearScale,
  TimeScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
  BarElement,
  zoomPlugin
);
export default {
  name: "Chart",
  components: { Bar },
  props: {
    info: {
      type: Array,
      required: true,
    },
  },
  data() {
    return {
      zoom: 1,
      chartOptions: {
        animations: false,
        scales: {
          x: {
            type: "time",
            time: {
              displayFormats: {
                day: "DD MMM YYYY HH:mm:ss.sss",
              },
            },
            barThickness: 10,
            title: {
              display: true,
              text: "Временной промежуток",
            },
            display: true,
            ticks: {
              maxTicksLimit: 20,
              minRotation: 45,
            },
          },
          y: {
            title: {
              display: true,
              text: "Количество событий",
            },
            suggestedMin: 0,
            display: true,
            ticks: {
              stepSize: 1,
            },
          },
        },
        plugins: {
          tooltip: {
            callbacks: {
              title: function (tooltipItem) {
                let options = {
                    year: 'numeric',
                    month: 'numeric',
                    day: 'numeric',
                    hour: 'numeric',
                    minute: 'numeric',
                    second: 'numeric',
                }
                let date = new Date(tooltipItem[0].parsed.x);
                return date.toLocaleString('ru-RU', options) + "." + date.getMilliseconds().toString().padStart(3, '0');; //toLocaleString
              },
            },
          },
          zoom: {
            zoom: {
              wheel: {
                enabled: true,
              },
              mode: "xy",
              onZoom: ({chart})=>{
                this.zoom = chart.getZoomLevel();
              },
            },
            pan: {
              enabled: true,
              mode: "xy",
            },
            limits: {
              x: { min: 0},
              y: { min: 0},
            },
          },
        },
        responsive: true,
      },
    };
  },
  computed: {
    chartData() {
      let labels = [];
      let data = [];
      function compareDate(a, b) {
        if (a.Date < b.Date) return -1;
        if (a.Date > b.Date) return 1;
        return 0;
      }

      let cloneInfo = this.info.slice()

      cloneInfo.sort(compareDate);
      let arr = cloneInfo;
      let limit = 200;
      let delta = 100;
      let min = cloneInfo.at(0).Date;
      let max = cloneInfo.at(-1).Date;
      delta = (max - min) / (limit * this.zoom);
    

      const dateCount = [];
      arr.forEach((action) => {
        let key = +action.Date;
        let ind = dateCount.findIndex((element) => Math.abs(element[0] - key) < delta);
        if (ind < 0) {
          dateCount.push([key, 1]);
        } else {
          dateCount[ind][1] += 1;
        }
      });
      dateCount.forEach(([key, value]) => {
        labels.push(key);
        data.push(new Date(value));
      });
      console.log(data);
      return {
        labels,
        datasets: [
          {
            data,
            showLine: true,
            backgroundColor: "#5e93b9",
            label: "график",
            label: "активность",
            barThickness: 4,
          },
        ],
      };
    },
    number(){
      return this.info.length;
    }
  },
  methods: {
    resetGraph(){
      this.$refs.myChart.chart.resetZoom();
      this.zoom = 1;
    },
  },
};
</script>


<style>
.window {
  width: 75%;
  display: flex;
  align-items: stretch;
  flex-direction: row;
  justify-content: center;
  margin-left: auto;
  margin-right: auto;
}


#reset{
  font-size: 13px;
  padding: 3px 7px 3px 7px;
  border-radius: 10px;
  background-color: var(--white-4);
  color: var(--blue-4);
}

#reset:hover {
  background-color: var(--white-5);
}

.second-line {
  white-space: pre;
}

.centerBox{
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
}

</style>