import {Component, OnInit} from '@angular/core';
import {NewsService} from "../service/news.service";
import {UserInfoService} from "../service/userInfo.service";
import {FriendsService} from "../service/friends.service";

@Component({
  selector: 'app-friends-news-page',
  templateUrl: './friendsNewsPage.component.html',
  styleUrls: ['./friendsNewsPage.component.css'],
})

export class FriendsNewsPageComponent implements OnInit {
  user: any;
  news: any;

  constructor(
    private newsService: NewsService,
    private userInfo: UserInfoService,
    private friendsService: FriendsService
  ) {
    this.user = this.userInfo.user
  }

  ngOnInit(): void {
    this.loadNews();
    this.newsService.getNewsStream().subscribe({
      next: value => {
        this.loadNews()
      },
      error: console.error
    });
    this.userInfo.getUserInfoStream().subscribe({
      next: value => {
        this.loadNews()
      },
      error: console.error
    });
    this.friendsService.getFriendsStream().subscribe({
      next: value => {
        this.loadNews();
      },
      error: console.error
    })
  }

  loadNews() {
    this.newsService.getFriendsNews().subscribe(news => this.news = news);
  }
}
