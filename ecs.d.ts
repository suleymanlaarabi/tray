declare function ecs_new(name?: string): bigint;
declare function ecs_add(entity: bigint, id: bigint);
declare function ecs_add_pair(entity: bigint, relation: bigint, target: bigint);
declare function ecs_delete(entity: number): bigint;

declare const ChildOf: bigint;

declare function print(...args: any[]): void;
