import {Component, OnInit} from '@angular/core';
import {UserInfoService} from "../service/userInfo.service";
import {ChatService} from "../service/chat.service";
import {FormBuilder, FormGroup, Validators} from "@angular/forms";
import {Alert} from "../service/alert.service";

@Component({
  selector: 'app-message',
  templateUrl: './message.component.html',
  styleUrls: ['./message.component.css'],
})

export class MessageComponent implements OnInit {
  user: any;
  message: any;
  userCommunicationFIO: any;
  public submitted = false;
  public sendMessageForm!: FormGroup;

  constructor(
    private userInfo: UserInfoService,
    private chatService: ChatService,
    private formBuilder: FormBuilder,
    private alert: Alert
  ) {
    this.user = this.userInfo.user;
    this.userCommunicationFIO = this.chatService.userCommunication;
  }

  ngOnInit(): void {
    this.loadMessage();
    this.sendMessageForm = this.formBuilder.group({
      smsText: ["", [Validators.required]]
    });
    this.chatService.getMessageStream().subscribe({
      next: value => {
        this.loadMessage();
      },
      error: console.error
    });
    this.userInfo.getUserInfoStream().subscribe({
      next: value => {
        this.loadMessage();
      },
      error: console.error
    })
  }

  loadMessage() {
    this.chatService.getMessage().subscribe(message => {this.message = message});
  }

  sendMessage() {
    this.submitted = true;
    if (this.sendMessageForm.valid) {
      const smsText = (document.getElementById('smsText') as HTMLInputElement).value;
      this.chatService.sendMessage(smsText).subscribe(
        (res) => {
          this.sendMessageForm.reset();
        },
        (error) => {
          this.alert.error(error.error.message);
          this.sendMessageForm.reset();
        }
      )
    }
  }
}
