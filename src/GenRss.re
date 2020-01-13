module Xml = {
  type t =
    | Node(string, list((string, string)), list(t))
    | Terminal(string, list((string, string)), string)
    | Empty(string, list((string, string)));

  let prefix = {|<?xml version="1.0" encoding="UTF-8" ?>|};

  let node = (title, ~attrs=[], children) => Node(title, attrs, children);
  let nodet = (title, ~attrs=[], s) => Terminal(title, attrs, s);
  let nodee = (title, ~attrs) => Empty(title, attrs);
  let rss =
    node(
      "rss",
      ~attrs=[
        ("version", "2.0"),
        ("xmlns:atom", "http://www.w3.org/2005/Atom"),
      ],
    );
  let atomLink = nodee("atom:link");
  let channel = node("channel");
  let title = nodet("title");
  let description = nodet("description");
  let link = nodet("link");
  let lastBuildDate = nodet("lastBuildDate");
  let pubDate = nodet("pubDate");
  let ttl = nodet("ttl");
  let item = node("item");
  let guid = nodet("guid");

  let render = t => {
    let rec go = t => {
      let renderAttrs = attrs =>
        switch (attrs) {
        | [] => ""
        | _ =>
          " "
          ++ (
            List.map(((k, v)) => k ++ "=\"" ++ v ++ "\"", attrs)
            |> String.concat(" ")
          )
        };
      let before = (title, attrs) =>
        "<" ++ title ++ renderAttrs(attrs) ++ ">";
      let after = title => "</" ++ title ++ ">";

      switch (t) {
      | Node(title, attrs, children) =>
        before(title, attrs)
        ++ "\n"
        ++ (List.map(go, children) |> String.concat("\n"))
        ++ "\n"
        ++ after(title)
      | Terminal(title, attrs, s) =>
        before(title, attrs) ++ s ++ after(title)
      | Empty(title, attrs) => "<" ++ title ++ renderAttrs(attrs) ++ " />"
      };
    };

    prefix ++ go(t);
  };
};

type input = {
  date: Js.Date.t,
  title: string,
  description: string,
  slug: string,
};
let draw =
  (. input: input) => {
    Xml.(
      rss([
        channel([
          atomLink(
            ~attrs=[
              ("href", "https://bkase.dev/posts/rss.xml"),
              ("rel", "self"),
              ("type", "application/rss+xml"),
            ],
          ),
          title(input.title),
          description(input.description),
          link("https://bkase.dev"),
          lastBuildDate(Js.Date.make() |> Js.Date.toUTCString),
          pubDate(input.date |> Js.Date.toUTCString),
          ttl("720"),
          item([
            title(input.title),
            description(input.description),
            link("https://bkase.dev/posts/" ++ input.slug),
            pubDate(input.date |> Js.Date.toUTCString),
            guid(~attrs=[("isPermaLink", "false")], "xxx"),
          ]),
        ]),
      ])
      |> render
    );
  };
