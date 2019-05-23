type action;
type state;
[@react.component]
let make:
  (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, ~children: React.element, unit) =>
  React.element;
