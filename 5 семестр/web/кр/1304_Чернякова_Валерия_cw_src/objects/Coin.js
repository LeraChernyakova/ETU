import { Entity } from "./Entity.js";

export class Coin extends Entity {
    constructor() {
        super();
        this.cadr = 1;
    }

    draw = (ctx) => {
        this.spriteManager.drawSprite(ctx, `Coin_${this.cadr}`, this.pos_x, this.pos_y);
    };

    update = () => {
        if (this.cadr < 4) {
            this.cadr++;
        } else {
            this.cadr = 1;
        }
    };

    kill = () => {
        this.gameManager.kill(this);
    };
}
