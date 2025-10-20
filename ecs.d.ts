
// 0: number
// 1: string
type ComponentValueType = number

declare type ComponentDef = Record<string, ComponentValueType>;

declare type Entity = bigint & { private readonly __entity: unique symbol };

declare function ecs_new(name?: string): Entity;
declare function ecs_add(entity: Entity, id: Entity);
declare function ecs_add_pair(entity: Entity, relation: Entity, target: Entity);
declare function ecs_set_name(entity: Entity, name: string);
declare function ecs_delete(entity: number): Entity;
declare function ecs_system(query: string, each: (entities: Entity[]) => void): Entity;
declare function ecs_component(name: string, def: CStructDef);

type Constructor = { new (): unknown };

declare function ecs_set(entity: Entity, component: Entity, value: unknown);
declare function ecs_set<T extends object>(entity: Entity, component: T extends Constructor ? never : T);

declare function ecs_get<T extends Constructor>(entity: Entity, component: T): InstanceType<T>;

declare const ChildOf: Entity;

declare function print(...args: any[]): void;
