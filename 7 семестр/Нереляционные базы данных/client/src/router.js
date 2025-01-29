import { createRouter, createWebHistory } from 'vue-router'

const routes = [
    { path: '/', redirect: '/plants/start'},
    { path: '/plants/start', name: 'Start', component: () => import('./components/pages/StartPage.vue')},
    { path: '/plants/sale', name: 'AllPlants', component: () => import('./components/pages/AllPlantsPage.vue')},
    { path: '/plants/sale/:species', name: 'Plant', component: () => import('./components/pages/PlantPage.vue')},
    { path: '/plants/care', name: 'Care', component: () => import('./components/pages/CarePage.vue')},
    { path: '/plants/user', name: 'User', component: () => import('./components/pages/UserPage.vue')},
    { path: '/plants/ads', name: 'Ads', component: () => import('./components/pages/MyAdsPage.vue')},
    { path: '/plants/statistics', name: 'Statistic', component: () => import('./components/pages/StatisticPage.vue')}
]

const router = createRouter({
    history: createWebHistory(),
    routes
})

export default router