import { Entity } from "./Entity.js";
import { Player } from "./Player.js";

export class Slime extends Entity {
    constructor() {
        super();
        this.move_x = 0;
        this.move_y = 0;
        this.speed = 6;
        this.dir = {
            '1': 'd',
            '2': 'a'
        };
        this.followPlayer = false;
    }

    draw = (ctx) => {
        const slimeNumber = this.name[this.name.length - 1];
        this.spriteManager.drawSprite(ctx, `slime_${this.dir[slimeNumber]}`, this.pos_x, this.pos_y);
    };

    update = () => {
        const slimeNumber = this.name[this.name.length - 1];

        this.checkPlayer();

        if (!this.followPlayer) {
            switch (this.dir[slimeNumber]) {
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
        const slimeNumber = this.name[this.name.length - 1];
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
                this.dir[slimeNumber] = 'a';
            }
            if (this.move_x > 0) {
                this.dir[slimeNumber] = 'd';
            }
            if (this.move_y < 0) {
                this.dir[slimeNumber] = 'w';
            }
            if (this.move_y > 0) {
                this.dir[slimeNumber] = 's';
            }
        }
    };

    onTouchEntity = (obj, newX, newY) => {
        if (obj instanceof Player) {
            this.gameManager.soundManager.play("map/music/hit.mp3", { volume: 0.5 });
            this.gameManager.player_life--;
            if (this.gameManager.player_life === 0) {
                obj.cadr = 'dead';
                obj.kill();
            }
        }
    };

    onTouchMap = (idx, newX, newY) => {
        const slimeNumber = this.name[this.name.length - 1];

        if (this.followPlayer && idx === 245) {
            this.pos_x = newX;
            this.pos_y = newY;
        }

        if (!this.followPlayer) {
            switch (this.dir[slimeNumber]) {
                case 'a':
                    this.dir[slimeNumber] = 'd';
                    break;
                case 'd':
                    this.dir[slimeNumber] = 'a';
                    break;
            }
        }
    };

    kill = () => {
        this.gameManager.final_score += 3;
        this.gameManager.kill(this);
    };
}
