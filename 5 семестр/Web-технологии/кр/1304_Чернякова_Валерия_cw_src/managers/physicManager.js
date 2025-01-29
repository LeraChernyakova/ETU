export class PhysicManager {
    allowed = {
        1: [156, 177, 178, 179, 200],
        2: [
            609, 631, 661, 662, 675, 653, 684, 612, 676,
            613, 614, 615, 634, 635, 636, 637, 656, 684,
            657, 658, 659, 678, 679, 680, 681
        ]
    };

    setManager = (gameManager, mapManager) => {
        this.gameManager = gameManager;
        this.mapManager = mapManager;
    };

    update = (obj) => {
        if (obj.move_x === 0 && obj.move_y === 0)
            return "stop";

        const newX = obj.pos_x + Math.floor(obj.move_x * obj.speed);
        const newY = obj.pos_y + Math.floor(obj.move_y * obj.speed);

        const ts = this.mapManager.getTilesetIdx(newX + obj.size_x / 2, newY + obj.size_y / 2);
        const e = this.entityAtXY(obj, newX, newY);

        if (e !== null && obj.onTouchEntity) {
            obj.onTouchEntity(e, newX, newY);
        }

        if (!this.allowed[this.gameManager.LVL].includes(ts) && obj.onTouchMap) {
            obj.onTouchMap(ts, newX, newY);
        }

        if (this.allowed[this.gameManager.LVL].includes(ts) && (e === null || (e instanceof Coin) || (e instanceof Star))) {
            obj.pos_x = newX;
            obj.pos_y = newY;
        } else {
            return "break";
        }
        return "move";
    };

    entityAtXY = (obj, x, y) => {
        for (let i = 0; i < this.gameManager.entities.length; i++) {
            const e = this.gameManager.entities[i];
            if (e.name !== obj.name) {
                if (
                    x + obj.size_x < e.pos_x ||
                    y + obj.size_y < e.pos_y ||
                    x > e.pos_x + e.size_x ||
                    y > e.pos_y + e.size_y
                ) {
                    continue;
                }
                return e;
            }
        }
        return null;
    };
}
