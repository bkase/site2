[@react.component]
let make = (~children) => {
  <>
    <Next.Head>
      <link
        href="https://cdn.jsdelivr.net/npm/@ibm/plex@4.0.2/css/ibm-plex.min.css"
        rel="stylesheet"
      />
    </Next.Head>
    <div> children </div>
  </>;
};

