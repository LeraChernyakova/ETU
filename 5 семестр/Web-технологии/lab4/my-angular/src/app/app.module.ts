import { NgModule } from '@angular/core';
import { HttpClientModule } from '@angular/common/http';
import { BrowserModule } from '@angular/platform-browser';
import {FormsModule, ReactiveFormsModule} from '@angular/forms';
import { AppComponent } from './app.component';
import { RouterModule, Routes } from '@angular/router';
import { AppRoutingModule } from './app-routing.module';
import {CommonModule, NgOptimizedImage} from '@angular/common';
import { WelcomePageComponent } from "./welcome-page/welcomePage.component";
import { RegisterPageComponent } from './register-page/registerPage.component';
import {UserPageComponent} from "./user-page/userPage.component";
import {FriendsPageComponent} from "./friends-page/friendsPage.component";
import {FriendsNewsPageComponent} from "./friends-news-page/friendsNewsPage.component";
import {ChatsComponent} from "./chats/chats.component";
import { AutocompleteOffDirective } from './autocomplete-off.directive';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { MatButtonModule } from '@angular/material/button';
import { MatInputModule } from '@angular/material/input';
import { MatFormFieldModule } from '@angular/material/form-field';
import {MatCardModule} from "@angular/material/card";
import {MatToolbarModule} from "@angular/material/toolbar";
import {MatTableModule} from "@angular/material/table";
import {AddFriendDialogComponent} from "./add-friend-dialog/addFriendDialog.component";
import { MatDialogModule } from '@angular/material/dialog';
import {MatIconModule} from "@angular/material/icon";
import {SocketIoConfig, SocketIoModule} from "ngx-socket-io";
import {MessageComponent} from "./message/message.component";
import {AddChatDialogComponent} from "./add-chat-dialog/addChatDialog.component";
import { MatDatepickerModule } from '@angular/material/datepicker';
import { MatNativeDateModule } from '@angular/material/core';


const config: SocketIoConfig = {url: 'http://localhost:3000', options: {}};

const routes: Routes = [
  { path: 'register', component: RegisterPageComponent },
];

@NgModule({
  declarations: [
    AppComponent,
    RegisterPageComponent,
    WelcomePageComponent,
    UserPageComponent,
    FriendsPageComponent,
    FriendsNewsPageComponent,
    ChatsComponent,
    AutocompleteOffDirective,
    AddFriendDialogComponent,
    MessageComponent,
    AddChatDialogComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    RouterModule.forRoot(routes),
    AppRoutingModule,
    CommonModule,
    HttpClientModule,
    NgOptimizedImage,
    ReactiveFormsModule,
    BrowserAnimationsModule,
    MatButtonModule,
    MatFormFieldModule,
    MatInputModule,
    MatCardModule,
    MatToolbarModule,
    MatTableModule,
    MatDialogModule,
    MatIconModule,
    SocketIoModule.forRoot(config),
    MatDatepickerModule,
    MatNativeDateModule
  ],
  exports: [RouterModule],
  bootstrap: [AppComponent]
})

export class AppModule { }
