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
      <meta property="og:title" content=title />
      <meta property="og:description" content=description />
      <meta property="og:type" content="website" />
      <style
        dangerouslySetInnerHTML={
          "__html": {j|
/* Remove default padding */
ul,
ol {
  padding: 0;
}

/* Remove default margin */
body,
h1,
h2,
h3,
h4,
p,
ul,
ol,
li,
figure,
figcaption,
blockquote,
dl,
dd {
  margin: 0;
}

/* Set core body defaults */
body {
  min-height: 100vh;
  scroll-behavior: smooth;
}

@font-face {
  font-family: "Arame";
  src: url("/static/fonts/arame/arameregular.woff2") format("woff2"),
       url("/static/fonts/arame/arameregular.woff") format("woff"),
       url("/static/fonts/arame/arameregular.ttf") format("truetype");
  font-weight: "normal";
  font-style: "normal";
  font-display: block;
}

@font-face {
  font-family: "PragmataPro";
  src: local("PragmataPro"),
       url("/static/fonts/essential-pragmatapro/essentialpro.woff2") format("woff2"),
       url("/static/fonts/essential-pragmatapro/essentialpro.woff") format("woff");
  font-weight: "normal";
  font-style: "normal";
  font-display: swap;
}
|j},
        }
      />
      extraHead
    </Next.Head>
    <div> children </div>
  </>;
};
