import { Entity } from "./Entity.js";
import { Player } from "./Player.js";
import { Key } from "./Key.js";
import { Coin } from "./Coin.js";
import { Door } from "./Door.js";

export class Dragon extends Entity {
    constructor() {
        super();
        this.move_x = 0;
        this.move_y = 0;
        this.speed = 6;
        this.dir = {
            '1': 'w',
            '2': 's'
        };
        this.followPlayer = false;
    }

    draw = (ctx) => {
        const dragonNumber = this.name[this.name.length - 1];
        this.spriteManager.drawSprite(ctx, `dragon_${this.dir[dragonNumber]}`, this.pos_x, this.pos_y);
    };

    update = () => {
        const dragonNumber = this.name[this.name.length - 1];

        this.checkPlayer();

        if (!this.followPlayer) {
            switch (this.dir[dragonNumber]) {
                case 'w':
                    this.move_x = 0;
                    this.move_y = -1;
                    break;
                case 's':
                    this.move_x = 0;
                    this.move_y = 1;
                    break;
            }
        }

        this.physicManager.update(this);
    };

    checkPlayer = () => {
        const dragonNumber = this.name[this.name.length - 1];
        const distance = Math.sqrt(
            Math.pow(this.pos_x - this.gameManager.player.pos_x, 2) +
            Math.pow(this.pos_y - this.gameManager.player.pos_y, 2)
        );
        if (distance < 100) {
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
                this.dir[dragonNumber] = 'a';
            }
            if (this.move_x > 0) {
                this.dir[dragonNumber] = 'd';
            }
            if (this.move_y < 0) {
                this.dir[dragonNumber] = 'w';
            }
            if (this.move_y > 0) {
                this.dir[dragonNumber] = 's';
            }
        }
    };

    onTouchEntity = (obj, newX, newY) => {
        const dragonNumber = this.name[this.name.length - 1];
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
        if (obj instanceof Door) {
            this.dir[dragonNumber] = 's';
        }
    };

    onTouchMap = (idx, newX, newY) => {
        const dragonNumber = this.name[this.name.length - 1];

        if (this.followPlayer && idx === 245) {
            this.pos_x = newX;
            this.pos_y = newY;
        }

        if (!this.followPlayer) {
            switch (this.dir[dragonNumber]) {
                case 's':
                    this.dir[dragonNumber] = 'w';
                    break;
                case 'w':
                    this.dir[dragonNumber] = 's';
                    break;
            }
        }
    };

    kill = () => {
        this.gameManager.final_score += 3;
        this.gameManager.kill(this);
    };
}
