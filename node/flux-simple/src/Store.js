import Emitter from "./EventEmitter"
export default class Store extends Emitter {
    constructor(dispatcher) {
        super();
        this.count = 0;
        dispatcher.on("countUp", this.onCountUp.bind(this));
    }

    getCount() {
        return this.count;
    }

    onCountUp(count) {
        this.count = count;
        this.emit("CHANGE");
    }
}
