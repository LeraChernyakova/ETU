import {Component, OnInit} from '@angular/core';
import {UserInfoService} from "../service/userInfo.service";
import {ChatService} from "../service/chat.service";
import {Router} from "@angular/router";
import {MessageComponent} from "../message/message.component";
import {AddFriendDialogComponent} from "../add-friend-dialog/addFriendDialog.component";
import {MatDialog} from "@angular/material/dialog";
import {AddChatDialogComponent} from "../add-chat-dialog/addChatDialog.component";

@Component({
  selector: 'app-chats',
  templateUrl: './chats.component.html',
  styleUrls: ['./chats.component.css'],
})

export class ChatsComponent implements OnInit {
  user: any;
  chats: any;

  constructor(
    private userInfo: UserInfoService,
    private chatService: ChatService,
    private router: Router,
    private dialog: MatDialog
  ) {
    this.user = this.userInfo.user
  }

  ngOnInit(): void {
    this.loadChats();
    this.chatService.getChatAddStream().subscribe({
      next: value => {
        this.loadChats();
      },
      error: console.error
    });
    this.userInfo.getPhotoStream().subscribe({
      next: value => {
        this.loadChats();
      },
      error: console.error
    });
    this.userInfo.getUserInfoStream().subscribe({
      next: value => {
        this.loadChats();
      },
      error: console.error
    });
    this.chatService.getMessageStream().subscribe({
      next: value => {
        this.loadChats();
      },
      error: console.error
    });
  }

  loadChats() {
    this.chatService.getChats().subscribe(chats => {this.chats = chats;})
  }

  openCommunication(id: any, FIO: any) {
    this.chatService.messageTo = id;
    this.chatService.userCommunication = FIO ;
    this.router.navigate(['/message']);
  }

  openAddChatDialog() {
    const dialogRef = this.dialog.open(
      AddChatDialogComponent,
      {
        width: '500px',
        height: '600px'
      });
  }
}
