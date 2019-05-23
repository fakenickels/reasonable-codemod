open TestFramework;

let readFile = filename => {
  let lines = ref("");
  let chan = open_in(filename);
  try (
    {
      while (true) {
        lines := lines.contents ++ input_line(chan);
      };
      lines.contents;
    }
  ) {
  | End_of_file =>
    close_in(chan);
    lines.contents;
  };
};

let transform = Lib.Migrate.transform([|"--demo"|]);

describe("should transform correctly", ({test}) => {
  test("App", ({expect}) => {
    transform("test/cases/App");
    expect.string(readFile("output/test/cases/App.re")).toMatchSnapshot();
  });
  test("MultiModule", ({expect}) => {
    transform("test/cases/MultiModule");
    expect.string(readFile("output/test/cases/MultiModule.re")).toMatchSnapshot();
    expect.string(readFile("output/test/cases/MultiModule.rei")).toMatchSnapshot();
  });
  test("ReducerComponent", ({expect}) => {
    transform("test/cases/ReducerComponent");
    expect.string(readFile("output/test/cases/ReducerComponent.re")).toMatchSnapshot();
    expect.string(readFile("output/test/cases/ReducerComponent.rei")).toMatchSnapshot();
  });
  test("ReducerComponentWithChildren", ({expect}) => {
    transform("test/cases/ReducerComponentWithChildren");
    expect.string(readFile("output/test/cases/ReducerComponentWithChildren.re")).toMatchSnapshot();
    expect.string(readFile("output/test/cases/ReducerComponentWithChildren.rei")).toMatchSnapshot();
  });
  test("ReducerComponentWithNamedChildren", ({expect}) => {
    transform("test/cases/ReducerComponentWithNamedChildren");
    expect.string(readFile("output/test/cases/ReducerComponentWithNamedChildren.re")).toMatchSnapshot();
    expect.string(readFile("output/test/cases/ReducerComponentWithNamedChildren.rei")).toMatchSnapshot();
  });
  test("StatelessComponent", ({expect}) => {
    transform("test/cases/StatelessComponent");
    expect.string(readFile("output/test/cases/StatelessComponent.re")).toMatchSnapshot();
    expect.string(readFile("output/test/cases/StatelessComponent.rei")).toMatchSnapshot();
  });
  test("StatelessComponentWithChildren", ({expect}) => {
    transform("test/cases/StatelessComponentWithChildren");
    expect.string(readFile("output/test/cases/StatelessComponentWithChildren.re")).toMatchSnapshot();
    expect.string(readFile("output/test/cases/StatelessComponentWithChildren.rei")).toMatchSnapshot();
  });
  test("StatelessComponentWithoutLifecycle", ({expect}) => {
    transform("test/cases/StatelessComponentWithoutLifecycle");
    expect.string(readFile("output/test/cases/StatelessComponentWithoutLifecycle.re")).toMatchSnapshot();
    expect.string(readFile("output/test/cases/StatelessComponentWithoutLifecycle.rei")).toMatchSnapshot();
  });
  test("StatelessComponentWithoutLifecycleWithChildren", ({expect}) => {
    transform("test/cases/StatelessComponentWithoutLifecycleWithChildren");
    expect.string(readFile("output/test/cases/StatelessComponentWithoutLifecycleWithChildren.re")).toMatchSnapshot();
    expect.string(readFile("output/test/cases/StatelessComponentWithoutLifecycleWithChildren.rei")).toMatchSnapshot();
  });
});
