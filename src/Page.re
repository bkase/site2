[@react.component]
let make =
    (
      ~title,
      ~description="Typed functional programming for life.",
      ~children,
      ~extraHead=React.null,
    ) => {
  <>
    <Next.Head>
      <link rel="icon" href="/static/icon/favicon-32.png" sizes="32x32" />
      <link rel="icon" href="/static/icon/favicon-128.png" sizes="128x128" />
      <link rel="icon" href="/static/icon/favicon-152.png" sizes="152x152" />
      <link rel="icon" href="/static/icon/favicon-167.png" sizes="167x167" />
      <link rel="icon" href="/static/icon/favicon-180.png" sizes="180x180" />
      <link rel="icon" href="/static/icon/favicon-192.png" sizes="192x192" />
      <link rel="icon" href="/static/icon/favicon-196.png" sizes="196x196" />
      <link
        rel="shortcut icon"
        sizes="196x196"
        href="/static/icon/favicon-196.png"
      />
      <link
        rel="apple-touch-icon"
        href="/static/icon/favicon-152.png"
        sizes="152x152"
      />
      <link
        rel="apple-touch-icon"
        href="/static/icon/favicon-167.png"
        sizes="167x167"
      />
      <link
        rel="apple-touch-icon"
        href="/static/icon/favicon-180.png"
        sizes="180x180"
      />
      <link
        href="https://cdn.jsdelivr.net/npm/@ibm/plex@4.0.2/css/ibm-plex.min.css"
        rel="stylesheet"
      />
      <link href="/static/reset.css" rel="stylesheet" />
      <meta property="og:title" content=title />
      <meta property="og:description" content=description />
      <meta property="og:type" content="website"/>
      extraHead
    </Next.Head>
    <div> children </div>
  </>;
};
