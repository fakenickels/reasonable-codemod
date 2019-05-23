ReactDOMRe.renderToElementWithId(
  <div>
    <ReducerComponentWithChildren prop1="ok">
      <ReducerComponent prop1="ok" />
      <StatelessComponent prop1="ok" />
      <MultiModules.StatelessComponent prop1="ok" />
      <MultiModules.StatelessComponentWithChildren prop1="ok">
        <StatelessComponent prop1="ok" />
      </MultiModules.StatelessComponentWithChildren>
    </ReducerComponentWithChildren>
  </div>,
  "demo",
);
