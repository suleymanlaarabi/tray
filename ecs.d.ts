
// 0: number
// 1: string
type ComponentValueType = number

declare type ComponentDef = Record<string, ComponentValueType>;

declare type Entity = bigint & { private readonly __entity: unique symbol };

type EntityDesc = Partial<{
  name: string,
  parent: Entity
}>

declare function ecs_new(desc?: string | EntityDesc): Entity;
declare function ecs_add(entity: Entity, id: Entity);
declare function ecs_add_pair(entity: Entity, relation: Entity, target: Entity);
declare function ecs_set_name(entity: Entity, name: string);
declare function ecs_set_description(entity: Entity, description: string)
declare function ecs_delete(entity: number): Entity;
declare function ecs_system(query: string, each: (count: number, ...args: unknown[]) => void, runOn: Entity): Entity;
declare function ecs_component(name: string, def: CStructDef);

declare function any();

type Constructor = { new (): unknown };

declare function ecs_set(entity: Entity, ...args: object[]);

declare function ecs_get<T extends Constructor>(entity: Entity, component: T): InstanceType<T>;

declare const ChildOf: Entity;
declare const OnUpdate: Entity;
declare const OnStart: Entity;

declare const PositionEntity: Entity;
declare const VelocityEntity: Entity;
declare const ColorEntity: Entity;
declare const CircleShapeEntity: Entity;
declare const RectangleShapeEntity: Entity;

declare function print(...args: any[]): void;
