import { Component, OnInit } from '@angular/core';
import {Router} from '@angular/router';
import {AuthorizationService} from "../service/authorization.service.";
import {UserInfoService} from "../service/userInfo.service";
import {FormBuilder, FormGroup, Validators} from "@angular/forms";
import {Alert} from "../service/alert.service";

@Component({
  selector: 'app-start-page',
  templateUrl: './welcomePage.component.html',
  styleUrls: ['./welcomePage.component.css'],
})

export class WelcomePageComponent implements OnInit {
  user: any = {};
  public loginForm!: FormGroup;
  public submitted = false;
  hide: boolean = true;

  constructor(
    private authorization: AuthorizationService,
    private userInfo: UserInfoService,
    private router: Router,
    private formBuilder: FormBuilder,
    private alert: Alert
  ) {
  }

  ngOnInit(): void {
    this.loginForm = this.formBuilder.group({
      email: ["", [Validators.email, Validators.required]],
      password: ["", [Validators.required]]
    })
  }

  onSubmit() {
    this.submitted = true;
    if (this.loginForm.valid) {
      this.user.mail = this.loginForm.value.email;
      this.user.password = this.loginForm.value.password;
      this.authorization.entrance(this.user).subscribe(
        (res) => {
          if (res.user.status === 'Заблокирован') {
            this.alert.error('Вход невозможен! Ваш аккаунт заблокирован.');
            this.loginForm.reset();
          }
          else {
            console.log('Login successful', res);
            this.userInfo.token = res.token;
            this.userInfo.user = res.user;
            this.loginForm.reset();
            this.router.navigate(['/user']);
          }
        },
        (error) => {
          this.alert.error(error.error.message);
          this.loginForm.reset();
        }
      );
    }
  }
}
