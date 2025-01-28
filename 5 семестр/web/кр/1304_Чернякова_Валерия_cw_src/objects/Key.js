import { Entity } from "./Entity.js";

export class Key extends Entity {
    constructor() {
        super();
    }

    draw = (ctx) => {
        this.spriteManager.drawSprite(ctx, "Key", this.pos_x, this.pos_y);
    };

    kill = () => {
        this.gameManager.kill(this);
    };
}
