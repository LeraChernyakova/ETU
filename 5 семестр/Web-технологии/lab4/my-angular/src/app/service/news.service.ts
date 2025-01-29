import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {Observable} from 'rxjs';
import {Socket} from "ngx-socket-io";
import {UserInfoService} from "./userInfo.service";

@Injectable({
  providedIn: 'root'
})

export class NewsService {
  id: any;
  constructor(
    private userInfo: UserInfoService,
    private readonly http: HttpClient,
    private readonly socket: Socket
  ) {
    this.id = this.userInfo.user._id;
  }

  getNews(): Observable<any> {
    return this.http.get<any>(`api/user/news/${this.id}`);
  }

  addNews(news: string): Observable<any> {
    const headers = new HttpHeaders({
      'Content-Type': 'application/x-www-form-urlencoded'
    });
    const addNews = new URLSearchParams();
    addNews.set('news', news);
    return this.http.post(
      `api/add/news/${this.id}`,
      addNews.toString(),
      { headers: headers });
  }

  getFriendsNews(): Observable<any> {
    return this.http.get<any>(
      `api/user/friends/news/${this.id}`,
      {withCredentials: true}
    );
  }

  getNewsStream() {
    return this.socket.fromEvent<any>('news');
  }
}
