type Constructor = { new (): unknown };

export function classDeftoCDef(target: Constructor): ComponentDef {
  const result = new target() as Record<string, number>;
  const def: ComponentDef = {};
  Object.keys(result).forEach((key) => {
    def[key] = typeof result[key] === "number" ? 0 : 1;
  });

  return def;
}

export function component(desc?: { name?: string; description?: string }) {
  return (target: Constructor) => {
    const def = classDeftoCDef(target);
    let name = target.name;
    if (desc) {
      if (desc.name) {
        target.prototype.path = desc.name;
        name = desc.name;
      }
    }
    target.prototype.entity = ecs_component(name, def);
    if (desc?.description) {
      ecs_set_description(target.prototype.entity, desc.description);
    }
  };
}

export function builtin(entity: Entity, path: string) {
  return (target: Constructor) => {
    target.prototype.entity = entity;
    target.prototype.path = path;
  };
}
