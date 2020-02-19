let reason = code => {
  let ast = Refmt.parseRE(code) |> Result.get_ok;
  Refmt.(printML(ast), printRE(ast));
};
let ocaml = code => {
  let ast =
    switch (Refmt.parseML(code)) {
    | Error(`RefmtParseError(e)) =>
      Js.log3("Failed to parse", code, e);
      Js.Exn.raiseError("Failed to parse ML code");
    | Ok(ast) => ast
    };
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
    | "language-typescript" => `Typescript
    | "language-rust" => `Rust
    | "language-kotlin" => `Kotlin
    | x => failwith("Unhandled language in MultiCodeBlock: " ++ x)
    };
  };

  let print = x => {
    switch (x) {
    | `Ocaml => "OCaml"
    | `Reason => "ReasonML"
    | `Haskell => "Haskell"
    | `Swift => "Swift"
    | `Nix => "Nix"
    | `Kotlin => "Kotlin"
    | `Typescript => "TypeScript"
    | `Rust => "Rust"
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

    let () = global(".tab-box::-webkit-scrollbar", [display(`none)]);

    let tabs =
      style([
        unsafe("width", "intrinsic"),
        unsafe("width", "max-content"),
        media(MediaQuery.halfTablet, [marginLeft(`px(-16))]),
      ]);

    let tabsBox =
      style([
        marginLeft(`rem(-1.)),
        paddingLeft(`rem(0.5)),
        paddingBottom(`px(10)),
        paddingTop(`px(10)),
        marginBottom(`px(-10)),
        marginTop(`px(-10)),
        overflowX(`auto),
        unsafe("scrollbar-width", "none"),
        media(
          MediaQuery.tablet,
          [marginLeft(`rem(-1.5)), paddingLeft(`rem(1.5))],
        ),
      ]);
  };

  [@react.component]
  let make = (~names, ~onSelected) => {
    let (selected, setSelected) = React.useState(_ => 0);
    let onClick = (i, _) => {
      setSelected(_ => i);
      onSelected(i);
    };

    <div className={Css.merge([Style.tabsBox, "tab-box"])}>
      <div className={Css.merge([Style.tabs, "tab-select"])}>
        {names
         |> Array.mapi((i, name) => {
              <Item name checked={i == selected} onClick={onClick(i)} />
            })
         |> React.array}
      </div>
    </div>;
  };
};

let () =
  Css.(global(".tab-box ~ div > pre > code", [borderTopLeftRadius(`zero)]));

[@react.component]
let make = (~children) => {
  let (selected, setSelected) = React.useState(_ => 0);

  let codes = Manipulation.manipulate(children);

  let names = codes |> Array.map(((lang, _)) => Language.print(lang));

  <div className=Css.(style([display(`flex), flexDirection(`column)]))>
    <TabSelect names onSelected={i => setSelected(_ => i)} />
    <div className=Css.(style([marginTop(`px(-13))]))>
      {codes[selected] |> snd}
    </div>
  </div>;
};
