open TestFramework;

let transform = Lib.Migrate.transform([|"--demo"|]);

let root = GetProjectRoot.get();

describe("should transform correctly", ({test, _}) => {
  test("Generic test", ({expect, _}) => {
    transform(root ++ "/test/cases/App.re");
    expect.file(root ++ "/output/test/cases/App.re").toMatchSnapshot();
  });
  test("It should codemod style calls inside JSX", ({expect, _}) => {
    transform(root ++ "/test/cases/InJSX.re");
    expect.file(root ++ "/output/test/cases/InJSX.re").toMatchSnapshot();
  });
  test("It should codemod style calls inside a function body", ({expect, _}) => {
    transform(root ++ "/test/cases/StyleInsideFunctionBody.re");
    expect.file(root ++ "/output/test/cases/StyleInsideFunctionBody.re").toMatchSnapshot();
  });
});
