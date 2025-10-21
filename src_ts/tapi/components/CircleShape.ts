import { builtin } from "../decorator";

@builtin(CircleShapeEntity, "rayflecs.JSCircleShape")
export class CircleShape {
  radius: number = 0;
  constructor(radius = 0) {
    this.radius = radius;
  }
}
