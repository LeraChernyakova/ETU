import { Component, OnInit } from '@angular/core';
import { MatDialogRef } from '@angular/material/dialog';
import {UserInfoService} from "../service/userInfo.service";
import {Socket} from "socket.io-client";
import { fromEvent } from 'rxjs';
import {FriendsService} from "../service/friends.service";
import {Alert} from "../service/alert.service";
import {ChatService} from "../service/chat.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-chat-friend-dialog',
  templateUrl: './addChatDialog.component.html',
  styleUrls: ['./addChatDialog.component.css']
})

export class AddChatDialogComponent implements OnInit {
  users: any;
  constructor(
    private chatService: ChatService,
    public dialogRef: MatDialogRef<AddChatDialogComponent>,
    private alert: Alert,
    private router: Router
  ) { }

  ngOnInit(): void {
    this.loadAllUsers();
  }

  loadAllUsers() {
    this.chatService.getAllUsers().subscribe(users => {this.users = users});
  }

  addChat(userId: any) {
    this.chatService.addChat(userId).subscribe(
      (res) => {
        this.chatService.messageTo = res.id;
        this.chatService.userCommunication = res.FIO;
        this.closeDialog();
        this.router.navigate(['/message']);
      },
      (error) => {
        this.alert.error(error.error.message);
      }
    )
  }

  closeDialog(){
    this.dialogRef.close();
  }
}
