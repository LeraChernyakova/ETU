import { NgModule } from '@angular/core';
import {PreloadAllModules, RouterModule, Routes} from '@angular/router';
import { HttpClientModule } from '@angular/common/http';
import { WelcomePageComponent } from './welcome-page/welcomePage.component';
import {RegisterPageComponent} from "./register-page/registerPage.component";
import {UserPageComponent} from "./user-page/userPage.component";
import {FriendsPageComponent} from "./friends-page/friendsPage.component";
import {FriendsNewsPageComponent} from "./friends-news-page/friendsNewsPage.component";
import {ChatsComponent} from "./chats/chats.component";
import {MessageComponent} from "./message/message.component";

const routes: Routes = [
  { path: '', redirectTo: '/login', pathMatch: 'full' },
  { path: 'login', component: WelcomePageComponent },
  { path: 'register', component: RegisterPageComponent },
  { path: 'user', component: UserPageComponent},
  { path: 'friends', component: FriendsPageComponent},
  { path: 'news', component: FriendsNewsPageComponent},
  { path: 'chats', component: ChatsComponent},
  { path: 'message', component: MessageComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes, { useHash: true, preloadingStrategy: PreloadAllModules }), HttpClientModule],
  exports: [RouterModule],
})

export class AppRoutingModule { }
