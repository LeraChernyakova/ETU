import { Injectable } from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})

export class AuthorizationService {
  constructor(
    private http: HttpClient
  ) {}

  entrance(currentUser: any): Observable<any> {
    const headers = new HttpHeaders({
      'Content-Type': 'application/x-www-form-urlencoded'
    });
    const userData = new URLSearchParams();
    userData.set('mail', currentUser.mail);
    userData.set('password', currentUser.password);
    return this.http.post(
      `api/authorization/login`,
      userData.toString(),
      { headers: headers }
    );
  }

  createAccount(user: any): Observable<any> {
    const headers = new HttpHeaders({
      'Content-Type': 'application/x-www-form-urlencoded'
    });
    const userInfo = new URLSearchParams();
    userInfo.set('mail', user.mail);
    userInfo.set('password', user.password);
    userInfo.set('FIO', user.FIO);
    userInfo.set('birth', user.birth);
    return this.http.post(
      `api/createAccount`, userInfo.toString(), { headers: headers }
    );
  }
}
