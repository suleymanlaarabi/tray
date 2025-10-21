import {
  Color,
  Position,
  RectangleShape,
  Velocity,
  query,
  component,
} from "./tapi/index";

@component({
  description: "Why Not",
})
class MoveNotAllowed {}

const World = ecs_new("World");

const Ceiling = ecs_new({
  name: "Ceiling",
  parent: World,
});

for (let i = 0; i < 10; i++) {
  ecs_set(
    ecs_new({
      name: `Ceiling(${i})`,
      parent: Ceiling,
    }),
    new Position(i * 100, 400),
    new RectangleShape(100, 50),
    new Color(255, 0, 0),
  );
}

const Floor = ecs_new({
  name: "Floor",
  parent: World,
});

for (let i = 0; i < 10; i++) {
  ecs_set(
    ecs_new({
      name: `Floor(${i})`,
      parent: Floor,
    }),
    new Position(i * 100, 0),
    new RectangleShape(100, 50),
    new Color(255, 0, 0),
  );
}

query("PosVel")
  .with(Velocity)
  .with(Position)
  .without(MoveNotAllowed)
  .system(OnUpdate, (count, velocities, positions) => {
    for (let i = 0; i < count; i++) {
      positions[i].x += velocities[i].x;
      positions[i].y += velocities[i].y;
    }
  });
