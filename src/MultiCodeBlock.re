let reason = code => {
  let ast = Refmt.parseRE(code) |> Result.get_ok;
  Refmt.(printML(ast), printRE(ast));
};
let ocaml = code => {
  let ast = Refmt.parseML(code) |> Result.get_ok;
  (code, Refmt.printRE(ast));
};

module Language = {
  let parse = s => {
    switch (s) {
    | "language-ocaml" => `Ocaml
    | "language-reason" => `Reason
    | "language-haskell" => `Haskell
    | "language-swift" => `Swift
    | "language-nix" => `Nix
    | _ => failwith("Unhandled language in MultiCodeBlock")
    };
  };

  let print = x => {
    switch (x) {
    | `Ocaml => "OCaml"
    | `Reason => "ReasonML"
    | `Haskell => "Haskell"
    | `Swift => "Swift"
    | `Nix => "Nix"
    };
  };
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
    let lang = Language.parse(t.props.children.props.className);
    let f =
      switch (lang) {
      | `Ocaml => Some(ocaml)
      | `Reason => Some(reason)
      | _ => None
      };
    switch (f) {
    | None => [|(lang, Obj.magic(t))|]
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
      let tOcaml: React.element =
        clone'(t, {"children": ocamlChild}) |> Obj.magic;
      let tReason: React.element =
        clone'(t, {"children": reasonChild}) |> Obj.magic;
      [|(`Ocaml, tOcaml), (`Reason, tReason)|];
    };
  };

  let manipulate = children => {
    let c: array(t) = Obj.magic(children);
    Js.Array.concatMany(Array.map(fixup, c), [||]);
  };
};

module TabSelect = {
  module Item = {
    module Style = {
      open Css;
      open Style;

      let button = checked =>
        merge([
          P.base,
          style([
            fontSize(Sizes.Mobile.body),
            position(`relative),
            borderTopLeftRadius(`px(16)),
            borderTopRightRadius(`px(16)),
            border(`zero, `none, `transparent),
            padding3(~top=`rem(0.25), ~h=`rem(0.5), ~bottom=`zero),
            unsafe("-webkit-tap-highlight-color", "rgba(1,4,62,0.06)"),
            media(
              MediaQuery.tablet,
              [
                fontSize(Sizes.body),
                padding3(~top=`rem(0.25), ~h=`rem(1.), ~bottom=`zero),
              ],
            ),
            ...if (checked) {
                 [backgroundColor(Colors.navy(0.03)), zIndex(10)];
               } else {
                 [
                   color(Colors.navy(0.25)),
                   cursor(`pointer),
                   backgroundColor(`transparent),
                 ];
               },
          ]),
        ]);
    };

    [@react.component]
    let make = (~name, ~checked, ~onClick) => {
      <label
        className={Css.style(
          if (checked) {
            [Css.zIndex(10)];
          } else {
            [];
          },
        )}>
        <input
          className=Css.(style([display(`none)]))
          type_="radio"
          name
          checked
        />
        <button className={Style.button(checked)} onClick>
          {React.string(name)}
        </button>
      </label>;
    };
  };

  module Style = {
    open Css;
    open Style;

    let tabs =
      style([
        marginBottom(`px(-13)),
        marginLeft(`px(-8)),
        media(MediaQuery.halfTablet, [marginLeft(`px(-16))]),
      ]);
  };

  [@react.component]
  let make = (~names, ~onSelected) => {
    let (selected, setSelected) = React.useState(_ => 0);
    let onClick = (i, _) => {
      setSelected(_ => i);
      onSelected(i);
    };

    <div className={Css.merge([Style.tabs, "tab-select"])}>
      {names
       |> Array.mapi((i, name) => {
            <Item name checked={i == selected} onClick={onClick(i)} />
          })
       |> React.array}
    </div>;
  };
};

let () =
  Css.(global(".tab-select ~ pre > code", [borderTopLeftRadius(`zero)]));

[@react.component]
let make = (~children) => {
  let (selected, setSelected) = React.useState(_ => 0);

  let codes = Manipulation.manipulate(children);

  let names = codes |> Array.map(((lang, _)) => Language.print(lang));

  <div>
    <TabSelect names onSelected={i => setSelected(_ => i)} />
    {codes[selected] |> snd}
  </div>;
};
