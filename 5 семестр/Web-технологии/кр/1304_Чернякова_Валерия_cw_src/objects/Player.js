import { Entity } from "./Entity.js";
import { Coin } from "./Coin.js";
import { Star } from "./Star.js";
import { Cut } from "./Cut.js";
import { Health } from "./Health.js";
import { Key } from "./Key.js";
import { Pickaxe } from "./Pickaxe.js";
import { Chest } from "./Chest.js";
import { Door } from "./Door.js";

export class Player extends Entity {
    constructor() {
        super();
        this.move_x = 0;
        this.move_y = 0;
        this.speed = 7;
        this.cadr = 's';
        this.starState = true;
        this.cutState = true;
        this.pickaxeState = true;
    }

    draw = (ctx) => {
        let name = `player_${this.cadr}`;
        if (this.move_x === -1){
            this.cadr = 'a';
            name = `player_${this.cadr}`;
        }
        if (this.move_x === 1){
            this.cadr = 'd';
            name = `player_${this.cadr}`;
        }
        if (this.move_y === -1){
            this.cadr = 'w';
            name = `player_${this.cadr}`;
        }
        if (this.move_y === 1){
            this.cadr = 's';
            name = `player_${this.cadr}`;
        }
        this.spriteManager.drawSprite(ctx, name, this.pos_x, this.pos_y);
    };

    update = () => {
        this.physicManager.update(this);
    };

    onTouchEntity = (obj, newX, newY) => {
        if (obj instanceof Coin) {
            this.gameManager.soundManager.play("map/music/coin.mp3", {volume: 0.5});
            this.pos_y = newY;
            this.pos_x = newX;
            this.gameManager.coin++;
            this.gameManager.final_score++;
            obj.kill();
        }
        if (obj instanceof Key){
            this.gameManager.soundManager.play("map/music/open.mp3", {volume: 0.5});
            this.pos_y = newY;
            this.pos_x = newX;
            this.gameManager.chest_key++;
            obj.kill();
        }
        if (obj instanceof Health) {
            this.gameManager.soundManager.play("map/music/health.mp3", {volume: 0.5});
            this.pos_y = newY;
            this.pos_x = newX;
            if (this.gameManager.player_life < 5)
                this.gameManager.player_life++;
            obj.kill();
        }
        if (obj instanceof Chest) {
            if (this.gameManager.chest_key === 1) {
                this.gameManager.soundManager.play("map/music/open.mp3", {volume: 0.5});
                obj.cadr = 'open';
                this.gameManager.door_key = 1;
            }
        }
        if (obj instanceof Door) {
            if (this.gameManager.door_key === 1) {
                this.gameManager.soundManager.play("map/music/door.mp3", {volume: 0.5});
                obj.cadr = 'open';
                this.gameManager.newLevel();
            }
        }
    };

    star = () => {
        if (this.starState) {
            let s = new Star();
            s.size_x = 16;
            s.size_y = 16;
            s.name = "star";
            s.move_x = this.move_x;
            s.move_y = this.move_y;
            s.cadr = 1;
            s.dir = this.cadr;
            s.speed = 15;
            s.spriteManager = this.spriteManager;
            s.physicManager = this.physicManager;
            s.gameManager = this.gameManager;
            switch (this.cadr) {
                case 'a':
                    s.pos_x = this.pos_x - this.size_x;
                    s.pos_y = this.pos_y;
                    break;
                case 'd':
                    s.pos_x = this.pos_x + this.size_x;
                    s.pos_y = this.pos_y;
                    break;
                case 'w':
                    s.pos_x = this.pos_x;
                    s.pos_y = this.pos_y - this.size_y;
                    break;
                case 's':
                    s.pos_x = this.pos_x;
                    s.pos_y = this.pos_y + this.size_y;
                    break;
                default:
                    return;
            }
            this.gameManager.entities.push(s);
            this.starState = false;
            setTimeout(() => {
                this.starState = true
            }, 500);
        }
    };

    cut = () => {
        if (this.cutState) {
            let c = new Cut();
            c.size_x = 16;
            c.size_y = 16;
            c.name = "cut";
            c.move_x = this.move_x;
            c.move_y = this.move_y;
            c.speed = 1;
            c.cadr = 1;
            c.dir = this.cadr;
            c.spriteManager = this.spriteManager;
            c.physicManager = this.physicManager;
            c.gameManager = this.gameManager;
            switch (this.cadr) {
                case 'a':
                    c.pos_x = this.pos_x - this.size_x;
                    c.pos_y = this.pos_y;
                    break;
                case 'd':
                    c.pos_x = this.pos_x + this.size_x;
                    c.pos_y = this.pos_y;
                    break;
                case 'w':
                    c.pos_x = this.pos_x;
                    c.pos_y = this.pos_y - this.size_y;
                    break;
                case 's':
                    c.pos_x = this.pos_x;
                    c.pos_y = this.pos_y + this.size_y;
                    break;
                default:
                    return;
            }
            this.gameManager.entities.push(c);
            this.cutState = false;
            setTimeout(() => {
                this.cutState = true
            }, 100);
        }
    };

    pickaxe = () => {
        if (this.pickaxeState) {
            let p = new Pickaxe();
            p.size_x = 16;
            p.size_y = 16;
            p.name = "pickaxe";
            p.move_x = this.move_x;
            p.move_y = this.move_y;
            p.speed = 1;
            p.cadr = 1;
            p.dir = this.cadr;
            p.spriteManager = this.spriteManager;
            p.physicManager = this.physicManager;
            p.gameManager = this.gameManager;
            switch (this.cadr) {
                case 'a':
                    p.pos_x = this.pos_x - this.size_x;
                    p.pos_y = this.pos_y;
                    break;
                case 'd':
                    p.pos_x = this.pos_x + this.size_x;
                    p.pos_y = this.pos_y;
                    break;
                case 'w':
                    p.pos_x = this.pos_x;
                    p.pos_y = this.pos_y - this.size_y;
                    break;
                case 's':
                    p.pos_x = this.pos_x;
                    p.pos_y = this.pos_y + this.size_y;
                    break;
                default:
                    return;
            }
            this.gameManager.entities.push(p);
            this.pickaxeState = false;
            setTimeout(() => {
                this.pickaxeState = true
            }, 100);
        }

    };

    kill = () => {
        this.gameManager.gameOver();
    };
}
