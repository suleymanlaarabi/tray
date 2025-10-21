import { builtin } from "../decorator";

@builtin(RectangleShapeEntity, "rayflecs.JSRectangleShape")
export class RectangleShape {
  width: number = 0;
  height: number = 0;
  constructor(width = 0, height = 0) {
    this.width = width;
    this.height = height;
  }
}
