import {GameManager} from "../managers/gameManager.js";
import {SpriteManager} from "../managers/spriteManager.js";
import {MapManager} from "../managers/mapManager.js";
import {EventsManager} from "../managers/eventsManager.js";
import {PhysicManager} from "../managers/physicManager.js";
import {SoundManager} from "../managers/soundManager.js";

const canvas = document.getElementById("canvasId");
const ctx = canvas.getContext("2d");

localStorage["ninja.coin"] = 0;
localStorage["ninja.finalScore"] = 0;

const spriteManager = new SpriteManager();
const mapManager = new MapManager();
const eventsManager = new EventsManager()
const physicManager = new PhysicManager();
const soundManager = new SoundManager();
const gameManager = new GameManager(ctx, canvas);

gameManager.setManager(spriteManager, mapManager, eventsManager, physicManager, soundManager);
gameManager.loadAll("./map/level1.json", 1);
gameManager.draw(ctx);
gameManager.play();
