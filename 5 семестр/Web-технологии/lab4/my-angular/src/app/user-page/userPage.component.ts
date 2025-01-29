import {Component, ElementRef, OnInit, ViewChild} from '@angular/core';
import {UserInfoService} from "../service/userInfo.service";
import {NewsService} from "../service/news.service";
import {FormBuilder, FormGroup, Validators} from "@angular/forms";
import {Alert} from "../service/alert.service";

@Component({
  selector: 'app-user-page',
  templateUrl: './userPage.component.html',
  styleUrls: ['./userPage.component.css'],
})

export class UserPageComponent implements OnInit {
  user: any;
  news: any;
  @ViewChild('fileInput') fileInput!: ElementRef;
  public submitted = false;
  public addNewsForm!: FormGroup;

  constructor(
    private userInfo: UserInfoService,
    private newsService: NewsService,
    private formBuilder: FormBuilder,
    private alert: Alert
  ) {}

  ngOnInit(): void {
      this.loadUser();
      this.loadNews();
      this.addNewsForm = this.formBuilder.group({
        newsText: ["", [Validators.required]]
      });
      this.userInfo.getPhotoStream().subscribe({
        next: value => {
          this.loadUser();
        },
        error: console.error
      });
    this.userInfo.getUserInfoStream().subscribe({
      next: value => {
        this.loadUser();
      },
      error: console.error
    });
      this.newsService.getNewsStream().subscribe({
        next: value => {
          this.loadNews()
        },
        error: console.error
      })
  };

  loadUser() {
    this.userInfo.getUser(this.userInfo.user._id).subscribe(user => this.user = user);
  }

  loadNews() {
    this.newsService.getNews().subscribe(news => this.news = news);
  }

  editPhoto() {
    const fileInput = this.fileInput.nativeElement;
    fileInput.click();
  }

  onFileSelected(event: Event) {
    console.log('there');
    const inputElement = event.target as HTMLInputElement;
    if (inputElement.files && inputElement.files[0]) {
      const selectedFile = inputElement.files[0];
      if (selectedFile.type.startsWith('image/')) {
        this.userInfo.changePhoto(selectedFile).subscribe(
          (res) => {
            this.alert.success(res.message)
          },
          (error) => {
            this.alert.error(error.error.message);
          }
        )
      }
      else {
        this.alert.warning('Выбранный файл не является изображением.');
      }
      inputElement.value = '';
    }
  }

  deletePhoto() {
    this.alert.delete('Вы точно хотите удалить фотографию?').then((result) => {
      if (result) {
        this.userInfo.deletePhoto().subscribe(
          (res) => {
            this.alert.success(res.message)
          },
          (error) => {
            this.alert.error(error.error.message);
          }
        )
      }
    });
  }

  addNews() {
    this.submitted = true;
    if (this.addNewsForm.valid) {
      const newsText = (document.getElementById('newsText') as HTMLInputElement).value;
      this.newsService.addNews(newsText).subscribe(
        (res) => {
          this.alert.success(res.message);
          this.addNewsForm.reset();
        },
        (error) => {
          this.alert.error(error.error.message);
          this.addNewsForm.reset();
        }
      )
    }
  }
}
