const player = ecs_new("Player");
const entity = ecs_new();

ecs_add_pair(entity, ChildOf, player);
