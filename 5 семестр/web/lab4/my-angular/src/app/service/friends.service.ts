import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {Observable} from 'rxjs';
import {Socket} from 'ngx-socket-io';
import {UserInfoService} from "./userInfo.service";

@Injectable({
  providedIn: 'root'
})

export class FriendsService {
  id: any
  constructor(
    private userInfo: UserInfoService,
    private readonly http: HttpClient,
    private readonly socket: Socket
  ) {
    this.id = this.userInfo.user._id;
  }

  getFriends(): Observable<any> {
    return this.http.get<any>(`api/user/friends/${this.id}`);
  }

  getAllUsers(): Observable<any> {
    return this.http.get<any>(`api/allUsers/${this.id}`);
  }

  addFriend(friend: string): Observable<any> {
    const headers = new HttpHeaders({
      'Content-Type': 'application/x-www-form-urlencoded'
    });
    const newFriend = new URLSearchParams();
    newFriend.set('newFriend', friend);
    return this.http.post(
      `api/addFriend/${this.id}`,
      newFriend.toString(),
      { headers: headers });
  }

  deleteFriend(whom: string): Observable<any> {
    return this.http.delete(`api/deleteFriend/${this.id}/${whom}`);
  }

  public getFriendsStream(): Observable<any> {
    return this.socket.fromEvent<any>('friend');
  }
}
