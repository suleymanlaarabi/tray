import { component } from "./tapi/decorator";

const player = ecs_new("Player");
const entity = ecs_new();

ecs_add_pair(entity, ChildOf, player);

@component
class Velocity {
  x: number = 0;
  y: number = 0;
  constructor(x: number = 0, y: number = 0) {
    this.x = x;
    this.y = y;
  }
}

ecs_set(player, new Velocity(10, 10));

ecs_system("", function PosVelSystem() {});
