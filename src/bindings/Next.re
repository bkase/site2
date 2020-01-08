module Link = {
  [@bs.module "next/link"] [@react.component]
  external make:
    (
      ~href: string=?,
      ~_as: string=?,
      ~prefetch: option(bool)=?,
      ~replace: option(bool)=?,
      ~shallow: option(bool)=?,
      ~passHref: option(bool)=?,
      ~children: React.element
    ) =>
    React.element =
    "default";
};

module Head = {
  [@bs.module "next/head"] [@react.component]
  external make: (~children: React.element) => React.element = "default";
};

module Router = {
  type t('a) = {
    query: Js.Dict.t('a),
    route: string,
  };

  [@bs.module "next/router"] [@bs.val]
  external useRouter: unit => t('a) = "useRouter";
};

module Config = {
  [@bs.val] [@bs.scope "process.env"] external node_env: string = "NODE_ENV";
  [@bs.val] [@bs.scope "process.env"]
  external contentful_token: string = "CONTENTFUL_TOKEN";
  [@bs.val] [@bs.scope "process.env"]
  external contentful_image_token: string = "CONTENTFUL_IMAGE_TOKEN";
  [@bs.val] [@bs.scope "process.env"]
  external contentful_space: string = "CONTENTFUL_SPACE";
};

module MDXProvider = {
  [@bs.module "@mdx-js/react"] [@react.component]
  external make:
    (~components: Js.t(_)=?, ~scope: Js.t(_)=?, ~children: React.element) =>
    React.element =
    "MDXProvider";
};

type getInitialPropsArgs = {
  pathname: string,
  query: Js.Dict.t(string),
  asPath: string,
};

let injectGetInitialProps:
  (
    Js.t('props) => React.element,
    getInitialPropsArgs => Js.Promise.t(Js.t('props))
  ) =>
  unit =
  (element, getInitialProps) => {
    Obj.magic(element)##getInitialProps #= getInitialProps;
  };
