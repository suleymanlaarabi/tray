import { builtin } from "../decorator";

@builtin(PositionEntity, "transform.JSPosition")
export class Position {
  x: number = 0;
  y: number = 0;

  constructor(x: number = 0, y: number = 0) {
    this.x = x;
    this.y = y;
  }
}
