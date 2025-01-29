export class SpriteManager {
    constructor() {
        this.image = new Image();
        this.sprites = [];
        this.imgLoaded = false;
        this.jsonLoaded = false;
        this.mapManager = null;
    }

    setManager = (mapManager) => {
        this.mapManager = mapManager;
    }

    loadAtlas = (atlasJson, atlasImg) => {
        const request = new XMLHttpRequest();

        request.addEventListener('load', () => {
            if (request.readyState === 4 && request.status === 200) {
                this.parseAtlas(request.responseText);
            }
        });

        request.open("GET", atlasJson, true);
        request.send();

        this.loadImg(atlasImg);
    }

    loadImg = (imgName) => {
        this.image.addEventListener('load', () => {
            this.imgLoaded = true;
        });

        this.image.src = imgName;
    }

    parseAtlas = (atlasJSON) => {
        const atlas = JSON.parse(atlasJSON);
        for (const name in atlas.frames) {
            const frame = atlas.frames[name].frame;
            this.sprites.push({ name, x: frame.x, y: frame.y, w: frame.w, h: frame.h });
        }
        this.jsonLoaded = true;
    }

    drawSprite = (ctx, name, x, y) => {
        if (!this.imgLoaded || !this.jsonLoaded) {
            setTimeout(() => {
                this.drawSprite(ctx, name, x, y);
            }, 100);
        }
        else {
            const sprite = this.getSprite(name);
            ctx.drawImage(this.image, sprite.x, sprite.y, sprite.w, sprite.h, x, y, sprite.w, sprite.h);
        }
    }

    getSprite = (name) => {
        return this.sprites.find(s => s.name === name) || null;
    }
}
