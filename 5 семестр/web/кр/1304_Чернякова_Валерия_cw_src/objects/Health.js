import { Entity } from "./Entity.js";

export class Health extends Entity {
    constructor() {
        super();
    }

    draw = (ctx) => {
        this.spriteManager.drawSprite(ctx, `Health`, this.pos_x, this.pos_y);
    };

    kill = () => {
        this.gameManager.kill(this);
    };
}
