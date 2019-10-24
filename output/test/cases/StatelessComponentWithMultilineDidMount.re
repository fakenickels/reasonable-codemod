[@react.component]
let make = (~prop1, ~prop2=?, ~prop3=1, ()) => {
  let derived = prop3 + 2;
  ReactCompat.useMount(() => {
    Js.log(1);
    Js.log(2);
  });

  <div> {derived->Js.String.make->ReasonReact.string} </div>;
};
