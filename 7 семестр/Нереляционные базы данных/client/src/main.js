import { createApp } from 'vue'
import Notifications from '@kyvg/vue3-notification'
import App from './App.vue'
import router from "@/router"
import VueAwesomePaginate from "vue-awesome-paginate";
import "vue-awesome-paginate/dist/style.css";
import '@fortawesome/fontawesome-free/css/all.min.css'

createApp(App).use(router).use(Notifications).use(VueAwesomePaginate).mount('#app')