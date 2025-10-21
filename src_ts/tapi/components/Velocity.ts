import { builtin } from "../decorator";

@builtin(PositionEntity, "transform.JSVelocity")
export class Velocity {
  x: number = 0;
  y: number = 0;

  constructor(x: number = 0, y: number = 0) {
    this.x = x;
    this.y = y;
  }
}
