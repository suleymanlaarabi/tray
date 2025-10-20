type Constructor = { new (): unknown };

export function classDeftoCDef(target: Constructor): ComponentDef {
  const result = new target() as Record<string, number>;
  const def: ComponentDef = {};
  Object.keys(result).forEach((key) => {
    def[key] = typeof result[key] === "number" ? 0 : 1;
  });

  return def;
}

export function component(target: Constructor) {
  const def = classDeftoCDef(target);
  target.prototype.info = {
    def,
    entity: ecs_component(target.name, def),
  };
}
