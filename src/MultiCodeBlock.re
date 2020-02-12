let reason = code => {
  let ast = Refmt.parseRE(code) |> Result.get_ok;
  Refmt.(printML(ast), printRE(ast));
};
let ocaml = code => {
  let ast = Refmt.parseML(code) |> Result.get_ok;
  (code, Refmt.printRE(ast));
};

module Manipulation = {
  type a = {
    className: string,
    children: string,
  };
  type b = {props: a};
  type c = {children: b};
  type t = {props: c};

  let clone: 'a => 'a =
    t => Obj.magic(ReasonReact.cloneElement(Obj.magic(t), [||]));

  let clone': ('a, 'props) => 'a =
    (t, props) =>
      Obj.magic(ReasonReact.cloneElement(Obj.magic(t), ~props, [||]));

  let fixup = (t: t) => {
    let f =
      if (t.props.children.props.className == "language-ocaml") {
        Some(ocaml);
      } else if (t.props.children.props.className == "language-reason") {
        Some(reason);
      } else {
        None;
      };
    switch (f) {
    | None => [|t|]
    | Some(f) =>
      let (ocamlCode, reasonCode) = f(t.props.children.props.children);
      let ocamlChild =
        clone'(
          t.props.children,
          {"className": "language-ocaml", "children": ocamlCode},
        );
      let reasonChild =
        clone'(
          t.props.children,
          {"className": "language-reason", "children": reasonCode},
        );
      let tOcaml = clone'(t, {"children": ocamlChild});
      let tReason = clone'(t, {"children": reasonChild});
      [|tOcaml, tReason|];
    };
  };

  let manipulate: React.element => React.element =
    children => {
      let c: array(t) = Obj.magic(children);
      let fixed: array(t) = Js.Array.concatMany(Array.map(fixup, c), [||]);
      Obj.magic(fixed);
    };
};

[@react.component]
let make = (~children) => {
  <div>
     {Manipulation.manipulate(children)} </div>;
    /*<div>
        {AnnotatedCode.expand(entries)
         |> Array.map(((lang, source)) =>
              <BlogComponents.Code.R className={"language-" ++ lang}>
                {React.string(source)}
              </BlogComponents.Code.R>
            )
         |> React.array}
      </div>;*/
};
