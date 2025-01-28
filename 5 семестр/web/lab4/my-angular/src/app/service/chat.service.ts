import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {Observable} from 'rxjs';
import {UserInfoService} from "./userInfo.service";
import {Socket} from "ngx-socket-io";

@Injectable({
  providedIn: 'root'
})

export class ChatService {
  id: any;
  _messageTo: any;
  _userCommunication: any;
  constructor(
    private userInfo: UserInfoService,
    private readonly http: HttpClient,
    private readonly socket: Socket
  ) {
    this.id = this.userInfo.user._id;
  }

  get messageTo() {
    return this._messageTo;
  }

  set messageTo(id: any) {
    this._messageTo = id;
  }

  get userCommunication() {
    return this._userCommunication;
  }

  set userCommunication(id: any) {
    this._userCommunication= id;
  }

  getChats(): Observable<any> {
    return this.http.get<any>(`api/user/chats/${this.id}`);
  }

  getMessage(): Observable<any> {
    return this.http.get<any>(`api/messages/${this.id}/${this.messageTo}`);
  }

  getAllUsers(): Observable<any> {
    return this.http.get<any>(`api/chat/allUsers/${this.id}`);
  }

  addChat(user: any): Observable<any> {
    const headers = new HttpHeaders({
      'Content-Type': 'application/x-www-form-urlencoded'
    });
    const newChat = new URLSearchParams();
    newChat.set('newChat', user);
    return this.http.post(
      `api/addChat/${this.id}`,
      newChat.toString(),
      { headers: headers });
  }

  sendMessage(message: string): Observable<any> {
    const headers = new HttpHeaders({
      'Content-Type': 'application/x-www-form-urlencoded'
    });
    const sendMessage = new URLSearchParams();
    sendMessage.set('message', message);
    return this.http.post(
      `api/add/message/${this.id}/${this.messageTo}`,
      sendMessage.toString(),
      { headers: headers });
  }

  public getChatAddStream(): Observable<any> {
    return this.socket.fromEvent<any>('chat');
  }

  public getMessageStream(): Observable<any> {
    return this.socket.fromEvent<any>('message');
  }
}
