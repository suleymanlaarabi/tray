function getPath(constructor: Constructor): string {
  return constructor.prototype.path || constructor.name;
}

export class QueryBuilder<T extends Constructor[] = []> {
  private query: string = "";
  name: string | null = null;

  with<New extends Constructor>(obj: New): QueryBuilder<[...T, New]> {
    if (this.query != "") {
      this.query += ", ";
    }
    this.query += getPath(obj);
    return this as unknown as QueryBuilder<[...T, New]>;
  }

  without(obj: Constructor): QueryBuilder<T> {
    if (this.query != "") {
      this.query += ", ";
    }
    this.query += `!${getPath(obj)}`;
    return this;
  }

  build(): string {
    return this.query;
  }

  system(
    on: Entity,
    call: (
      count: number,
      ...args: { [K in keyof T]: InstanceType<T[K]>[] }
    ) => void,
  ) {
    const entity = ecs_system(
      this.build(),
      call as (count: number, ...args: unknown[]) => void,
      on,
    );

    if (this.name) {
      ecs_set_name(entity, this.name);
    }

    return entity;
  }
}

export function query(name?: string) {
  const builder = new QueryBuilder();
  if (name) {
    builder.name = name;
  }
  return builder;
}
