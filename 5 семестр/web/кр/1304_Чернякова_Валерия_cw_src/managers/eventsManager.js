export class EventsManager {
    constructor() {
        this.bind = {
            87: 'up',
            65: 'left',
            83: 'down',
            68: 'right',
            32: 'star',
            69: 'cut',
            81: 'pickaxe'
        };

        this.action = {};

        this.setup = (canvas) => {
            canvas.addEventListener('mousedown', this.onMouseDown);
            canvas.addEventListener('mouseup', this.onMouseUp);

            document.body.addEventListener("keydown", this.onKeyDown);
            document.body.addEventListener("keyup", this.onKeyUp);
        };

        this.onMouseDown = (event) => {};

        this.onMouseUp = (event) => {};

        this.onKeyDown = (event) => {
            const action = this.bind[event.keyCode];
            if (action) {
                this.action[action] = true;
            }
        };

        this.onKeyUp = (event) => {
            const action = this.bind[event.keyCode];
            if (action) {
                this.action[action] = false;
            }
        };
    }
}
