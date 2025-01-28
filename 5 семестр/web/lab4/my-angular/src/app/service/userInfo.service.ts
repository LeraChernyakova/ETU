import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Observable} from 'rxjs';
import {Socket} from "ngx-socket-io";

@Injectable({
  providedIn: 'root'
})

export class UserInfoService {
  private _token: any;
  private _user: any;

  constructor(
    private http: HttpClient,
    private readonly socket: Socket
  ){}

  get user() {
    return this._user;
  }
  set user(user: any) {
    this._user = user;
  }

  set token(token: string) {
    sessionStorage.setItem('token', token);
  }

  get token() {
    this._token =  sessionStorage.getItem('token');
    return this._token;
  }

  getUser(id: string): Observable<any> {
    return this.http.get<any>(`api/user/${id}`);
  }

  changePhoto(file: File): Observable<any> {
    const photoData = new FormData();
    photoData.append('photo', file)
    return this.http.post(`api/changePhoto/${this.user._id}`, photoData);
  }

  deletePhoto(): Observable<any> {
    return this.http.delete(`api/deletePhoto/${this.user._id}`);
  }

  getPhotoStream() {
    return this.socket.fromEvent<any>('photo');
  }

  getUserInfoStream() {
    return this.socket.fromEvent<any>('infoUpdate');
  }
}
