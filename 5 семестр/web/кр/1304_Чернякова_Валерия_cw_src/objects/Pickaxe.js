import { Entity } from "./Entity.js";
import { Rock } from "./Rock.js";

export class Pickaxe extends Entity {
    constructor() {
        super();
        this.move_x = 0;
        this.move_y = 0;
    }

    draw = (ctx) => {
        this.spriteManager.drawSprite(ctx, `pickaxe_${this.cadr}`, this.pos_x, this.pos_y);
    };

    update = () => {
        if (this.cadr < 5) {
            this.cadr++;
        } else {
            this.gameManager.soundManager.play("map/music/pickaxe.mp3", { volume: 0.5 });
            this.cadr = 1;
            switch (this.dir) {
                case 'a':
                    this.move_x = -1;
                    this.move_y = 0;
                    break;
                case 'd':
                    this.move_x = 1;
                    this.move_y = 0;
                    break;
                case 'w':
                    this.move_y = 1;
                    this.move_x = 0;
                    break;
                case 's':
                    this.move_y = -1;
                    this.move_x = 0;
                    break;
            }
            this.kill();
        }
        this.physicManager.update(this);
    };

    onTouchEntity = (obj) => {
        if (obj instanceof Rock) {
            obj.kill();
            this.kill();
        }
    };

    kill = () => {
        this.gameManager.kill(this);
    };
}
