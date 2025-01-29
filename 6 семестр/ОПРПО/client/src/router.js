import { createRouter, createWebHistory } from 'vue-router'

const routes = [
    { path: '/', redirect: '/e.moevm.statistics/auth'},
    { path: '/e.moevm.statistics/auth', name: 'Authorization', component: () => import('./components/Pages/AuthorizationPage.vue')},
    { path: '/e.moevm.statistics/statistics', name: 'Statistics', component: () => import('./components/Pages/StatisticsPage.vue')},
    { path: '/e.moevm.statistics/user', name: 'CreateUser', component: () => import('./components/Pages/CreateUserPage.vue')},
    { path: '/e.moevm.statistics/all-users', name: 'AllUsers', component: () => import('./components/Pages/AllUsersPage.vue')}
]

const router = createRouter({
    history: createWebHistory(),
    routes
})

export default router