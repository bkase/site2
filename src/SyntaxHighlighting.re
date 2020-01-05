open Css;

let render = List.iter (((color', suffixes)) => {
    let class_ = String.concat(",", suffixes |> List.map (s => ".token." ++ s));
    global(class_, [
      color(color')
    ]);
  });

module Color = Style.Colors.Code;

let draw = () =>
  render([
    (Color.comment, ["comment", "prolog", "doctype", "cdata"]),
    (Color.punctuation, ["punctuation"]),
    (Color.property, ["property", "tag", "boolean", "number", "constant", "symbol", "deleted"]),
    (Color.selector, ["selector", "attr-name", "string", "char", "builtin", "inserted"]),
    (Color.operator, ["operator"]),
    (Color.string, ["entity", "url", "string"]),
    (Color.keyword, ["atrule", "attr-value", "keyword"]),
    (Color.function_, ["function"]),
    (Color.variable, ["regex", "important", "variable"]),
  ]);

