import { builtin } from "../decorator";

@builtin(ColorEntity, "rayflecs.JSColor")
export class Color {
  r: number = 0;
  g: number = 0;
  b: number = 0;
  a: number = 255;
  constructor(r = 0, g = 0, b = 0, a = 255) {
    this.r = r;
    this.g = g;
    this.b = b;
    this.a = a;
  }
}
