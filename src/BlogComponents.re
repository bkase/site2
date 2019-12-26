module type Component = {
  let className: string;
  let element: React.element;
};

module Wrap = (C: Component) => {
  let className = C.className;
  let make = props => {
    ReasonReact.cloneElement(C.element, ~props, [||]);
  };
};

open Css;

let headerStyle =
  style([
    display(`flex),
    marginTop(rem(2.)),
    marginBottom(`rem(0.5))
  ]);

module H1 =
  Wrap({
    let className =
      merge([
        headerStyle,
        style([alignItems(`baseline), fontWeight(`light)]),
      ]);
    let element = <h1 className />;
  });

module H2 =
  Wrap({
    let className =
      merge([
        headerStyle,
        style([alignItems(`baseline), fontWeight(`light)]),
      ]);
    let element = <h2 className />;
  });

