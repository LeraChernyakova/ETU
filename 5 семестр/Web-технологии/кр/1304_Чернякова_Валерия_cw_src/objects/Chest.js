import { Entity } from "./Entity.js";

export class Chest extends Entity {
    constructor() {
        super();
        this.cadr = 'close';
    }

    draw = (ctx) => {
        this.spriteManager.drawSprite(ctx, `chest_${this.cadr}`, this.pos_x, this.pos_y);
    };
}
