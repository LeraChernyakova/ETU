import { Entity } from "./Entity.js";

export class Rock extends Entity {
    constructor() {
        super();
    }

    draw = (ctx) => {
        this.spriteManager.drawSprite(ctx, "rock", this.pos_x, this.pos_y);
    };

    kill = () => {
        this.gameManager.kill(this);
    };
}
