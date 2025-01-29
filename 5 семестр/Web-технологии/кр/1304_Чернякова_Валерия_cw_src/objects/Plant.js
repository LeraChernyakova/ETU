import { Entity } from "./Entity.js";

export class Plant extends Entity {
    constructor() {
        super();
    }

    draw = (ctx) => {
        this.spriteManager.drawSprite(ctx, "plant", this.pos_x, this.pos_y);
    };

    kill = () => {
        this.gameManager.kill(this);
    };
}
