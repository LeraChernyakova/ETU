import { Player } from "../objects/Player.js";
import { Coin } from "../objects/Coin.js";
import { Eye } from "../objects/Eye.js";
import { Health } from "../objects/Health.js";
import { Key } from "../objects/Key.js";
import { Plant } from "../objects/Plant.js";
import { Dragon } from "../objects/Dragon.js";
import { Chest } from "../objects/Chest.js";
import { Door } from "../objects/Door.js";
import { Rock } from "../objects/Rock.js";
import { Star } from "../objects/Star.js";
import { Cut } from "../objects/Cut.js";
import { Pickaxe } from "../objects/Pickaxe.js";
import { Slime } from "../objects/Slime.js";
import { Boss } from "../objects/Boss.js";
import { Fire } from "../objects/Fire.js";

export class GameManager {
    constructor(ctx, canvas) {
        this.factory = {};
        this.entities = [];
        this.player = null;
        this.laterKill = [];
        this.LVL = 0;
        this.ctx = ctx;
        this.canvas = canvas;
        this.chest_key = 0;
        this.player_life = 5;
        this.door_key = 0;
        this.coin = parseInt(localStorage["ninja.coin"]);
        this.boss_life = 5;
        this.final_score = parseInt(localStorage["ninja.finalScore"]);
        this.gameOverFlag = false;
        this.music = [
            "map/music/fon.mp3", "map/music/gameOverFon.mp3", "map/music/coin.mp3", "map/music/health.mp3",
            "map/music/hit.mp3", "map/music/kill.mp3", "map/music/open.mp3", "map/music/star.mp3",
            "map/music/door.mp3", "map/music/cut.mp3", "map/music/dead.mp3", "map/music/pickaxe.mp3",
            "map/music/cave.mp3", "map/music/fire.mp3"
        ];
    }

    setManager = (spriteManager, mapManager, eventsManager, physicManager, soundManager) => {
        this.spriteManager = spriteManager;
        this.mapManager = mapManager;
        this.eventsManager = eventsManager;
        this.physicManager = physicManager;
        this.soundManager = soundManager;

        this.mapManager.setManager(this.spriteManager, this, this.physicManager);
        this.spriteManager.setManager(this.mapManager);
        this.physicManager.setManager(this, this.mapManager);
        this.soundManager.setManager(this);
    };

    initPlayer = (obj) => {
        this.player = obj;
    };

    kill = (obj) => {
        this.laterKill.push(obj);
    };

    update = () => {
        if (this.player === null || this.gameOverFlag)
            return;

        this.updateInfo();

        this.player.move_x = 0;
        this.player.move_y = 0;

        if (this.eventsManager.action["up"]) {
            this.player.move_y = -1;
            this.player.move_x = 0;
        }
        if (this.eventsManager.action["down"]) {
            this.player.move_y = 1;
            this.player.move_x = 0;
        }
        if (this.eventsManager.action["left"]) {
            this.player.move_x = -1;
            this.player.move_y = 0;
        }
        if (this.eventsManager.action["right"]) {
            this.player.move_x = 1;
            this.player.move_y = 0;
        }
        if (this.eventsManager.action["star"]) {
            this.player.star();
        }
        if (this.eventsManager.action["cut"]) {
            this.player.cut();
        }
        if (this.eventsManager.action["pickaxe"]) {
            this.player.pickaxe();
        }

        this.entities.forEach((e) => {
            try {
                e.update();
            } catch (ex) {}
        });

        this.laterKill.forEach((killObj) => {
            const idx = this.entities.indexOf(killObj);
            if (idx > -1) {
                this.entities.splice(idx, 1);
            }
        });

        if (this.laterKill.length > 0) {
            this.laterKill.length = 0;
        }

        this.mapManager.draw(this.ctx);
        this.mapManager.centerAt(this.player.pos_x, this.player.pos_y);
        this.draw(this.ctx);
    };

    updateInfo = () => {
        document.getElementById("levelId").innerHTML = 'Уровень: ' + this.LVL;
        document.getElementById("healthId").innerHTML = 'Здоровье: ' + this.player_life;
        localStorage["ninja.life"] = this.player_life;
        document.getElementById("coinId").innerHTML = 'Монеты: ' + this.coin;
        localStorage["ninja.coin"] = this.coin;
        if (this.LVL === 1) {
            document.getElementById("chestId").innerHTML = 'Ключ от сундука: ' + this.chest_key;
            document.getElementById("doorId").innerHTML = 'Ключ от подземелья:' + this.door_key;
        } else {
            document.getElementById("bossId").innerHTML = 'Босс:' + this.boss_life;
        }
    };

    gameOver = () => {
        this.updateInfo();
        this.soundManager.stopFon();
        this.soundManager.play("map/music/gameOverFon.mp3", { volume: 0.2 });
        const dialogBox = document.getElementById('dialogBox');
        const dialogText = document.getElementById('dialogText');
        dialogText.innerText = 'Вы проиграли!';
        dialogBox.style.display = 'block';
        this.gameOverFlag = true;
    };

    finishGame = () => {
        this.final_score += 5;
        this.final_score += this.player_life;
        this.updateInfo();
        let username = localStorage.getItem('ninja.username');
        let allScores = localStorage.getItem('ninja.allScores');
        let scoreTable;
        if (!allScores) {
            scoreTable = {};
        } else {
            scoreTable = JSON.parse(localStorage.getItem('ninja.allScores'));
        }
        if (!scoreTable[username] || Number(scoreTable[username]) < Number(this.final_score)) {
            scoreTable[username] = this.final_score;
            localStorage.setItem('ninja.score', this.final_score.toString());
        } else {
            localStorage.setItem('ninja.score', scoreTable[username]);
        }
        localStorage.setItem('ninja.allScores', JSON.stringify(scoreTable));
        window.location.href = '../records.html';
    };

    draw = (ctx) => {
        this.entities.forEach((e) => {
            e.draw(ctx);
        });
    };

    loadAll = (levelMap, lvl) => {
        console.log(this.final_score);
        this.LVL = lvl;
        this.setPlayer();
        this.mapManager.loadMap(levelMap);
        this.spriteManager.loadAtlas("../map/sprites.json", "../map/sprites.png");
        this.soundManager.loadArray(this.music);

        this.factory['Player'] = Player;
        this.factory['Coin'] = Coin;
        this.factory['Eye'] = Eye;
        this.factory['Health'] = Health;
        this.factory['Key'] = Key;
        this.factory['Plant'] = Plant;
        this.factory['Dragon'] = Dragon;
        this.factory['Chest'] = Chest;
        this.factory['Door'] = Door;
        this.factory['Rock'] = Rock;
        this.factory['Star'] = Star;
        this.factory['Cut'] = Cut;
        this.factory['Pickaxe'] = Pickaxe;
        this.factory['Slime'] = Slime;
        this.factory['Boss'] = Boss;
        this.factory['Fire'] = Fire;

        this.mapManager.parseEntities();
        this.mapManager.draw(this.ctx);
        this.eventsManager.setup(this.canvas);
        if (this.LVL === 1) {
            this.soundManager.play("map/music/fon.mp3", { volume: 1 });
        } else {
            this.soundManager.play("map/music/cave.mp3", { volume: 1 });
        }
    };

    play = () => {
        this.interval = setInterval(() => this.updateWorld(), 100);
    };

    updateWorld = () => {
        this.update();
    };

    setPlayer = () => {
        let elem = document.getElementById('playerId');
        elem.textContent = "Игрок: " + localStorage.getItem('ninja.username');
    };

    newLevel = () => {
        localStorage["ninja.finalScore"] = this.final_score;
        window.location.href = '../level2.html';
    };
}
