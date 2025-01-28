import { Entity } from "./Entity.js";

export class Door extends Entity {
    constructor() {
        super();
        this.cadr = 'close';
    }

    draw = (ctx) => {
        this.spriteManager.drawSprite(ctx, `door_${this.cadr}`, this.pos_x, this.pos_y);
    };
}
