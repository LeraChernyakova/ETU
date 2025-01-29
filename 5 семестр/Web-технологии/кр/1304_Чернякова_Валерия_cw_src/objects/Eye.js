import { Entity } from "./Entity.js";
import { Player } from "./Player.js";
import { Key } from "./Key.js";
import { Coin } from "./Coin.js";

export class Eye extends Entity {
    constructor() {
        super();
        this.move_x = 0;
        this.move_y = 0;
        this.speed = 6;
        this.dir = {
            '1': 'a',
            '2': 'd'
        };
        this.followPlayer = false;
    }

    draw = (ctx) => {
        const eyeNumber = this.name[this.name.length - 1];
        this.spriteManager.drawSprite(ctx, `eye_${this.dir[eyeNumber]}`, this.pos_x, this.pos_y);
    };

    update = () => {
        const eyeNumber = this.name[this.name.length - 1];
        this.checkPlayer();

        if (!this.followPlayer) {
            switch (this.dir[eyeNumber]) {
                case 'a':
                    this.move_x = -1;
                    this.move_y = 0;
                    break;
                case 'd':
                    this.move_x = 1;
                    this.move_y = 0;
                    break;
            }
        }

        this.physicManager.update(this);
    };

    checkPlayer = () => {
        const eyeNumber = this.name[this.name.length - 1];
        const distance = Math.sqrt(
            Math.pow(this.pos_x - this.gameManager.player.pos_x, 2) +
            Math.pow(this.pos_y - this.gameManager.player.pos_y, 2)
        );

        if (distance < 150) {
            this.speed = 8;
            this.followPlayer = true;

            const directionX = this.gameManager.player.pos_x - this.pos_x;
            const directionY = this.gameManager.player.pos_y - this.pos_y;

            const length = Math.sqrt(directionX ** 2 + directionY ** 2);
            const normalizedDirectionX = directionX / length;
            const normalizedDirectionY = directionY / length;

            this.move_x = normalizedDirectionX;
            this.move_y = normalizedDirectionY;

            if (this.move_x < 0) {
                this.dir[eyeNumber] = 'a';
            }
            if (this.move_x > 0) {
                this.dir[eyeNumber] = 'd';
            }
            if (this.move_y < 0) {
                this.dir[eyeNumber] = 'w';
            }
            if (this.move_y > 0) {
                this.dir[eyeNumber] = 's';
            }
        }
    };

    onTouchEntity = (obj, newX, newY) => {
        if (obj instanceof Player) {
            this.gameManager.soundManager.play("map/music/hit.mp3", { volume: 0.5 });
            this.gameManager.player_life--;

            if (this.gameManager.player_life <= 0) {
                obj.cadr = 'dead';
                obj.kill();
            }
        }

        if (obj instanceof Key || obj instanceof Coin) {
            this.pos_x = newX;
            this.pos_y = newY;
        }
    };

    onTouchMap = (idx, newX, newY) => {
        const eyeNumber = this.name[this.name.length - 1];

        if (this.followPlayer && idx === 245) {
            this.pos_x = newX;
            this.pos_y = newY;
        }

        if (!this.followPlayer) {
            switch (this.dir[eyeNumber]) {
                case 'a':
                    this.dir[eyeNumber] = 'd';
                    break;
                case 'd':
                    this.dir[eyeNumber] = 'a';
                    break;
            }
        }
    };

    kill = () => {
        this.gameManager.final_score += 3;
        this.gameManager.kill(this);
    };
}
