import { Entity } from "./Entity.js";
import { Player } from "./Player.js";
import { Star } from "./Star.js";
import { Health } from "./Health.js";

export class Fire extends Entity {
    constructor() {
        super();
        this.move_x = 0;
        this.move_y = 0;
    }

    draw = (ctx) => {
        this.spriteManager.drawSprite(ctx, `fire_${this.cadr}`, this.pos_x, this.pos_y);
    };

    update = () => {
        if (this.cadr < 4) {
            this.cadr++;
        } else {
            this.cadr = 1;
        }
        this.gameManager.soundManager.play("map/music/fire.mp3", { volume: 0.5 });
        this.physicManager.update(this);
    };

    onTouchEntity = (obj, newX, newY) => {
        if (obj instanceof Player) {
            this.kill();
            this.gameManager.soundManager.play("map/music/hit.mp3", { volume: 0.5 });
            this.gameManager.player_life--;

            if (this.gameManager.player_life <= 0) {
                obj.cadr = 'dead';
                obj.kill();
            }
        }
        if (obj instanceof Star || obj instanceof Health) {
            this.pos_x = newX;
            this.pos_y = newY;
        }
    };

    onTouchMap = (idx) => {
        this.kill();
    };

    kill = () => {
        this.gameManager.kill(this);
    };
}
