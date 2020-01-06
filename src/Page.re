[@react.component]
let make = (~children, ~extraHead=React.null) => {
  <>
    <Next.Head>
      <link
        href="https://cdn.jsdelivr.net/npm/@ibm/plex@4.0.2/css/ibm-plex.min.css"
        rel="stylesheet"
      />
      <link href="/static/reset.css" rel="stylesheet" />
      extraHead
    </Next.Head>
    <div> children </div>
  </>;
};
