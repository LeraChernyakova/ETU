export class MapManager {
    mapData = null;
    tLayer = [];
    xCount = 0;
    yCount = 0;
    tSize = { x: 16, y: 16 };
    mapSize = { x: 32, y: 32 };
    tilesets = [];
    imgLoadCount = 0;
    imgLoaded = false;
    jsonLoaded = false;
    view = { x: 0, y: 0, w: 512, h: 512 };

    setManager = (spriteManager, gameManager, physicManager) => {
        this.spriteManager = spriteManager;
        this.gameManager = gameManager;
        this.physicManager = physicManager;
    };

    loadMap = (path) => {
        const request = new XMLHttpRequest();
        request.onreadystatechange = () => {
            if (request.readyState === 4 && request.status === 200) {
                this.parseMap(request.responseText);
            }
        };
        request.open("GET", path, true);
        request.send();
    };

    parseMap = (tilesJSON) => {
        this.mapData = JSON.parse(tilesJSON);
        this.xCount = this.mapData.width;
        this.yCount = this.mapData.height;
        this.tSize.x = this.mapData.tilewidth;
        this.tSize.y = this.mapData.tileheight;
        this.mapSize.x = this.xCount * this.tSize.x;
        this.mapSize.y = this.yCount * this.tSize.y;

        this.mapData.tilesets.forEach((t) => {
            const img = new Image();
            img.onload = () => {
                this.imgLoadCount++;
                if (this.imgLoadCount === this.mapData.tilesets.length) {
                    this.imgLoaded = true;
                }
            };
            img.src = t.image;

            const ts = {
                firstgid: t.firstgid,
                image: img,
                name: t.name,
                Count: Math.floor(t.imagewidth / this.tSize.x),
                yCount: Math.floor(t.imageheight / this.tSize.y),
            };
            this.tilesets.push(ts);
        });

        this.jsonLoaded = true;
    };

    getTileset = (tileIndex) => {
        for (let i = this.tilesets.length - 1; i >= 0; i--) {
            if (this.tilesets[i].firstgid <= tileIndex) {
                return this.tilesets[i];
            }
        }
        return null;
    };

    getTile = (tileIndex) => {
        const tile = {
            img: null,
            px: 0,
            py: 0,
        };
        const tileset = this.getTileset(tileIndex);
        tile.img = tileset.image;
        const id = tileIndex - tileset.firstgid;
        const x = id % tileset.Count;
        const y = Math.floor(id / tileset.Count);
        tile.px = x * this.tSize.x;
        tile.py = y * this.tSize.y;
        return tile;
    };

    draw = (ctx) => {
        if (!this.imgLoaded || !this.jsonLoaded) {
            setTimeout(() => this.draw(ctx), 100);
        } else {
            if (this.tLayer.length === 0) {
                for (let id = 0; id < this.mapData.layers.length; id++) {
                    const layer = this.mapData.layers[id];
                    if (layer.type === "tilelayer") {
                        this.tLayer.push(layer);
                    }
                }
            }
            for (let i = 0; i < this.tLayer.length; i++) {
                for (let j = 0; j < this.tLayer[i].data.length; j++) {
                    if (this.tLayer[i].data[j] !== 0) {
                        const tile = this.getTile(this.tLayer[i].data[j]);
                        let pX = (j % this.xCount) * this.tSize.x;
                        let pY = Math.floor(j / this.xCount) * this.tSize.y;
                        ctx.drawImage(
                            tile.img,
                            tile.px,
                            tile.py,
                            this.tSize.x,
                            this.tSize.y,
                            pX,
                            pY,
                            this.tSize.x,
                            this.tSize.y
                        );
                    }
                }
            }
        }
    };

    parseEntities = () => {
        if (!this.imgLoaded || !this.jsonLoaded) {
            setTimeout(() => this.parseEntities(), 100);
        } else {
            for (let j = 0; j < this.mapData.layers.length; j++) {
                if (this.mapData.layers[j].type === 'objectgroup') {
                    const entities = this.mapData.layers[j];
                    for (let i = 0; i < entities.objects.length; i++) {
                        const e = entities.objects[i];
                        try {
                            const obj = new this.gameManager.factory[e.type]();

                            obj.name = e.name;
                            obj.pos_x = e.x;
                            obj.pos_y = e.y - e.height;
                            obj.size_x = e.width;
                            obj.size_y = e.height;
                            obj.start_x = e.x;
                            obj.start_y = e.y;
                            obj.spriteManager = this.spriteManager;
                            obj.physicManager = this.physicManager;
                            obj.gameManager = this.gameManager;

                            this.gameManager.entities.push(obj);
                            if (obj.name === "Player")
                                this.gameManager.initPlayer(obj);
                        } catch (ex) {
                            console.log("ERROR while creating:[" + e.gid + "]" + e.type + "," + ex);
                        }
                    }
                }
            }
        }
    };

    getTilesetIdx = (x, y) => {
        const wX = x;
        const wY = y;
        const idx = Math.floor(wY / this.tSize.y) * this.xCount + Math.floor(wX / this.tSize.x);
        return this.tLayer[0].data[idx];
    };

    centerAt = (x, y) => {
        if (x < this.view.w / 2)
            this.view.x = 0;
        else if (x > this.mapSize.x - this.view.w / 2)
            this.view.x = this.mapSize.x - this.view.w;
        else
            this.view.x = x - (this.view.w / 2);

        if (y < this.view.h / 2)
            this.view.y = 0;
        else if (y > this.mapSize.y - this.view.h / 2)
            this.view.y = this.mapSize.y - this.view.h;
        else
            this.view.y = y - (this.view.h / 2);
    };
}
