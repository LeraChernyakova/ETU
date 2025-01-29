import {Component, OnInit} from '@angular/core';
import {FriendsService} from "../service/friends.service";
import {MatDialog} from "@angular/material/dialog";
import {AddFriendDialogComponent} from "../add-friend-dialog/addFriendDialog.component";
import {Alert} from "../service/alert.service";
import {UserInfoService} from "../service/userInfo.service";

@Component({
  selector: 'app-friends-page',
  templateUrl: './friendsPage.component.html',
  styleUrls: ['./friendsPage.component.css'],
})

export class FriendsPageComponent implements OnInit {
  friends: any;
  user: any;

  constructor(
    private userInfo: UserInfoService,
    private friendsService: FriendsService,
    private dialog: MatDialog,
    private alert: Alert
  ) {
    this.user = this.userInfo.user
  }

  ngOnInit(): void {
    this.loadFriends();
    this.userInfo.getPhotoStream().subscribe({
      next: value => {
        this.loadFriends();
      },
      error: console.error
    });
    this.userInfo.getUserInfoStream().subscribe({
      next: value => {
        this.loadFriends();
      },
      error: console.error
    })
    this.friendsService.getFriendsStream().subscribe({
      next: value => {
        this.loadFriends();
      },
      error: console.error
    })
  }

  loadFriends() {
    this.friendsService.getFriends().subscribe(friends => this.friends = friends);
  }

  deleteFriend(whom: any) {
    this.alert.delete('Вы точно хотите удалить пользователя из друзей?').then((result) => {
      if (result) {
        this.friendsService.deleteFriend(whom).subscribe(
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

  openAddFriendDialog() {
    const dialogRef = this.dialog.open(
      AddFriendDialogComponent,
      {
        width: '500px',
        height: '600px'
      });
  }
}
