open Css;

let render =
  List.iter(((color', suffixes)) => {
    let class_ =
      String.concat(",", suffixes |> List.map(s => ".token." ++ s));
    global(class_, [color(color')]);
  });

module Color = Style.Colors.Code;

let draw = () => {
  // line numbers
  global("code", [unsafe("counter-reset", "line")]);

  global(
    ".token-line",
    [
      unsafe("counter-increment", "line"),
      before([
        unsafe("content", "counter(line)"),
        userSelect(`none),
        width(`auto),
        textAlign(`right),
        display(`inlineBlock),
        color(Style.Colors.navy(0.25)),
        marginRight(`rem(0.5)),
        media(Style.MediaQuery.tablet, [marginRight(`rem(1.))]),
        media(Style.MediaQuery.largeWithMargins, [marginRight(`rem(1.5))]),
      ]),
    ],
  );

  global(".token-line:last-of-type", [display(`none)]);

  global(
    ".token-line:first-child:nth-last-child(n + 9), .token-line:first-child:nth-last-child(n + 9) ~ .token-line",
    [before([width(`em(1.0))])],
  );

  // colors
  render([
    (Color.comment, ["comment", "prolog", "doctype", "cdata"]),
    (Color.punctuation, ["punctuation"]),
    (
      Color.property,
      [
        "property",
        "tag",
        "boolean",
        "number",
        "constant",
        "symbol",
        "deleted",
      ],
    ),
    (
      Color.selector,
      ["selector", "attr-name", "string", "char", "builtin", "inserted"],
    ),
    (Color.operator, ["operator"]),
    (Color.string, ["entity", "url", "string"]),
    (Color.keyword, ["atrule", "attr-value", "keyword"]),
    (Color.function_, ["function"]),
    (Color.variable, ["regex", "important", "variable"]),
  ]);
};
