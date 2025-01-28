import { Entity } from "./Entity.js";
import { Fire } from "./Fire.js";

export class Boss extends Entity {
    constructor() {
        super();
        this.move_x = 0;
        this.move_y = 0;
        this.fireState = true;
    }

    draw = (ctx) => {
        this.spriteManager.drawSprite(ctx, `boss`, this.pos_x, this.pos_y);
    };

    update = () => {
        this.checkPlayer();
        this.physicManager.update(this);
    };

    checkPlayer = () => {
        const distance = Math.sqrt(
            Math.pow(this.pos_x - this.gameManager.player.pos_x, 2) +
            Math.pow(this.pos_y - this.gameManager.player.pos_y, 2)
        );
        if (distance < 300) {
            if (this.fireState) {
                const directionX = this.gameManager.player.pos_x - this.pos_x;
                const directionY = this.gameManager.player.pos_y - this.pos_y;

                const length = Math.sqrt(directionX ** 2 + directionY ** 2);
                const normalizedDirectionX = directionX / length;
                const normalizedDirectionY = directionY / length;

                let f = new Fire();
                f.size_x = 16;
                f.size_y = 16;
                f.move_x = normalizedDirectionX;
                f.move_y = normalizedDirectionY;
                f.cadr = 1;
                f.speed = 15;
                f.spriteManager = this.spriteManager;
                f.physicManager = this.physicManager;
                f.gameManager = this.gameManager;
                f.pos_x = this.pos_x - this.size_x;
                f.pos_y = this.pos_y;
                this.gameManager.entities.push(f);
                this.fireState = false;
                setTimeout(() => {
                    this.fireState = true;
                }, 2000);
            }
        }
    };

    kill = () => {
        this.gameManager.kill(this);
    };
}
