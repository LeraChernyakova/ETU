import { Entity } from "./Entity.js";
import { Eye } from "./Eye.js";
import { Dragon } from "./Dragon.js";
import { Health } from "./Health.js";
import { Key } from "./Key.js";
import { Coin } from "./Coin.js";
import { Door } from "./Door.js";
import { Chest } from "./Chest.js";
import { Plant } from "./Plant.js";
import { Rock } from "./Rock.js";
import { Slime } from "./Slime.js";
import { Boss } from "./Boss.js";

export class Star extends Entity {
    constructor() {
        super();
        this.move_x = 0;
        this.move_y = 0;
    }

    draw = (ctx) => {
        this.spriteManager.drawSprite(ctx, `star_${this.cadr}`, this.pos_x, this.pos_y);
    };

    update = () => {
        this.cadr = (this.cadr < 2) ? this.cadr + 1 : 1;
        switch (this.dir) {
            case 'a':
                this.move_x = -1;
                break;
            case 'd':
                this.move_x = 1;
                break;
            case 'w':
                this.move_y = -1;
                break;
            case 's':
                this.move_y = 1;
                break;
        }
        this.gameManager.soundManager.play("map/music/star.mp3", { volume: 0.5 });
        this.physicManager.update(this);
    };

    onTouchEntity = (obj, newX, newY) => {
        if (obj instanceof Eye || obj instanceof Dragon || obj instanceof Slime) {
            this.gameManager.soundManager.play("map/music/kill.mp3", { volume: 0.5 });
            obj.kill();
            this.kill();
        }
        if (obj instanceof Coin || obj instanceof Health || obj instanceof Key || obj instanceof Chest || obj instanceof Door) {
            this.pos_x = newX;
            this.pos_y = newY;
        }
        if (obj instanceof Plant || obj instanceof Rock) {
            this.kill();
        }
        if (obj instanceof Boss) {
            this.kill();
            this.gameManager.soundManager.play("map/music/kill.mp3", { volume: 0.5 });
            this.gameManager.boss_life--;
            if (this.gameManager.boss_life <= 0) {
                obj.kill();
                this.gameManager.finishGame();
            }
        }
    };

    onTouchMap = (idx) => {
        this.kill();
    };

    kill = () => {
        this.gameManager.kill(this);
    };
}
